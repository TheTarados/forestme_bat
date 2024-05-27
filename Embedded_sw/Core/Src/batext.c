/*
 * batext.c
 *
 *  Created on: Apr 30, 2023
 *      Author: brock
 */

#include "batext.h"
#include "app_fatfs.h"
#include "spectrogram_tables.h"
#include "app_x-cube-ai.h"
#include "usart.h"

void batext_AFE_init(void);
void batext_AFE_deinit(void);
void batext_SD_init(void);
void batext_SD_deinit(void);
int batext_SD_write(const void *data, uint32_t size);





FATFS FatFs; 	//Fatfs handle
FIL fil; 		//File handle
FRESULT fres; //Result after operation
//+sint write_count = 0;

int init_sd_power_on(void){
	if(!batext_is_card_inserted()) {
		print_now("Error while powering on : No card inserted\r\n");
		return 1;
	} else {
		print_now("Success : Card is inserted\r\n");
	}
	batext_SD_init();
	HAL_Delay(1000);
	fres = f_open(&fil, "MYTEST", FA_WRITE | FA_OPEN_APPEND);
	if(fres != FR_OK) {
		print_error("f_open error\n", fres);
		return 1;
	}
	return 0;
}

void batext_power_on(void)
{
	print_now("Begin power on\r\n");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	print_now("BatExt power ON\r\n");
	HAL_Delay(100); // for card insert cap charge
#if SAVE_RAW_AUDIO && CHOSEN_OUTPUT == SD_CARD
	if(init_sd_power_on())return;
	HAL_Delay(1000); // more delays between steps may be required at initialisation otherwise it sometimes fails
#endif

	print_now("Init AFE\r\n");
	batext_AFE_init();
	print_now("Setting AFE\r\n");
	batext_choose_gain(3);

}
void batext_power_off(void)
{
	batext_AFE_deinit();
#if SAVE_RAW_AUDIO && CHOSEN_OUTPUT == SD_CARD
	batext_SD_deinit();
#endif
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	print_now("BatExt power OFF\r\n");
}



/*******************
 *
 * AFE
 *
 *******************/

typedef uint16_t SAMPLE;
#define S_SIZE sizeof(SAMPLE)

static volatile SAMPLE ADCDoubleBuf[2*ADC_BUF_SIZE]; /* ADC group regular conversion data (array of data) */
static volatile SAMPLE* ADCData[2] = {&ADCDoubleBuf[0], &ADCDoubleBuf[ADC_BUF_SIZE]};
static volatile uint8_t ADCDataRdy[2] = {0, 0};


void batext_AFE_init(void)
{
	/*if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK) {
		debug_print("Error while calibrating the ADC\r\n");
		Error_Handler();
	}*/
	if (HAL_TIM_Base_Start(&htim1) != HAL_OK) {
		print_now("Error while enabling timer TIM1\r\n");
		Error_Handler();
	}
	if (HAL_ADC_Start_DMA(&hadc, (uint32_t *)ADCDoubleBuf, 2*ADC_BUF_SIZE) != HAL_OK) {
		print_now("Error while starting the DMA\r\n");
		Error_Handler();
	}
}

void batext_AFE_deinit(void)
{
	if (HAL_ADC_Stop_DMA(&hadc) != HAL_OK) {
		print_now("Error while stopping the DMA\r\n");
		Error_Handler();
	}
	if (HAL_TIM_Base_Stop(&htim1) != HAL_OK) {
		print_now("Error while disabling timer TIM1\r\n");
		Error_Handler();
	}
}

/*
 *	gain : 0 disconnected - 1 33 dB - 2 43 dB - 3 53 dB
 */
void batext_choose_gain(uint8_t gain)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, gain & 0x01);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, (gain & 0x02) >> 1);
}

#if (SAVE_RAW_AUDIO )
static void Save_Callback(int buf_cplt) {
	if (ADCDataRdy[1-buf_cplt]) {
		print_now("Error: ADC Data buffer full\r\n");
		Error_Handler();
	}
	ADCDataRdy[buf_cplt] = 1;

#if (SAVE_RAW_AUDIO && CHOSEN_OUTPUT == UART)
	HAL_UART_Transmit(&hlpuart1, (uint8_t *) ADCData[buf_cplt], ADC_BUF_SIZE*S_SIZE, 0xFFFF);
#else
	batext_SD_write((const void *) ADCData[buf_cplt], ADC_BUF_SIZE*S_SIZE);
#endif


	ADCDataRdy[buf_cplt] = 0;
}

#else
uint8_t vec_counter = 0;

q7_t melspec [N_MEL_BIN*N_MELVEC];
q7_t* melvec[N_MELVEC] = {melspec, melspec + N_MEL_BIN, melspec + 2*N_MEL_BIN, melspec + 3 *N_MEL_BIN, melspec + 4*N_MEL_BIN,
							melspec+5*N_MEL_BIN, melspec + 6*N_MEL_BIN, melspec + 7*N_MEL_BIN, melspec + 8 *N_MEL_BIN, melspec + 9*N_MEL_BIN,};

static const uint8_t log2_q15(q15_t x){
	//Return ceiling of log_2 of x
	static const uint8_t MultiplyDeBruijnBitPosition[32] =
	{
	  1, 10, 2, 11, 14, 22, 3, 30, 12, 15, 17, 19, 23, 26, 4, 31,
	  9, 13, 21, 29, 16, 18, 25, 8, 20, 28, 24, 7, 27, 6, 5, 32
	};
	x |= x >> 1; // first round down to one less than a power of 2
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;

	return MultiplyDeBruijnBitPosition[(uint32_t)(x * 0x07C4ACDDU) >> 27];
}

static const  q15_t bin_search_log(q15_t x) {
	if(x<2000){
	    if(x<290){
	        if(x<37){
	            return x*312;
	        }else{
	            return x*24+10656;
	        }
	    }else{
	        if(x<840){
	            return x*5+16166;
	        }else{
	            return x*2+18686;
	        }
	    }
	}else{
	    if(x<8200){
	        if(x<4050){
	            return x+20686;
	        }else{
	            return (x>>1)+22711;
	        }
	    }else{
	        if(x<14904){
	            return (x>>2)+24761;
	        }else{
	            return (x>>3)+26624;
	        }
	    }
	}
}

void print_array_q15(char* intro, q15_t* array, int length){
	print_now(intro);
	print_now("\r\n");
	for(int i = 0 ; i < length ; i++){
		print_int(array[i]);
		print_now(",");
	}
	print_now("\r\n\n");
}

void print_array_q7(char* intro, q7_t* array, int length){
	print_now(intro);
	print_now("\r\n");
	for(int i = 0 ; i < length ; i++){
		print_int(array[i]);
		print_now(",");
	}
	print_now("\r\n\n");
}

void vec_computation(q15_t* in, q7_t* out, uint8_t shift_val) {

	q15_t buf     [ SAMPLE_PER_MELVEC ];
	q15_t fft_buf     [ 2 * SAMPLE_PER_MELVEC ];
	q63_t temp_vak = 0;

	uint32_t* word_in 		= (uint32_t*)	in;
	uint32_t* word_ham 		= (uint32_t*) 	hamming_window;
	uint32_t* word_buf 		= (uint32_t*) 	buf;
	uint32_t* word_fft_buf 	= (uint32_t*) 	fft_buf;

	//Center data, scale it up and mulltiply with hamming window
	#pragma GCC unroll 8
	for(int i = 0 ; i < SAMPLE_PER_MELVEC/2 ;i++){
		int32_t normalizeds = (__SSUB16(word_in[i], 0x08000800)<<shift_val)&0xFFF0FFF0;
		q31_t facs = word_ham[i];
		q15_t term1 = (((normalizeds >> 16) *  (facs >> 16)))>>15;
		q15_t term2 = (((q15_t) normalizeds * (q15_t) facs))>>15;
		word_buf[i] = __PKHBT(term2 , term1 , 16);
	}

#if DEBUG_VEC_COMP
	print_array_q15("after mult", buf, SAMPLE_PER_MELVEC);
#endif

	//Apply FFT
	arm_rfft_instance_q15 rfft_inst;
	arm_rfft_init_q15(&rfft_inst, SAMPLE_PER_MELVEC, 0, 1);
	arm_rfft_q15( &rfft_inst, buf, fft_buf);
#if DEBUG_VEC_COMP
	print_array_q15("after fft", fft_buf, SAMPLE_PER_MELVEC);
#endif

	//Complex norm + logarithm
	for(int i = MIN_INDEX_MATMUL ; i < MAX_INDEX_MATMUL; i+=4){
		uint32_t shifted =  (word_fft_buf[i]<<1)&0xFFFEFFFE;
		buf[i  ] = bin_search_log(__SMUAD(shifted, shifted)>>16);
		shifted =  (word_fft_buf[i+1]<<1)&0xFFFEFFFE;
		buf[i+1] = bin_search_log(__SMUAD(shifted, shifted)>>16);
		shifted =  (word_fft_buf[i+2]<<1)&0xFFFEFFFE;
		buf[i+2] = bin_search_log(__SMUAD(shifted, shifted)>>16);
		shifted =  (word_fft_buf[i+3]<<1)&0xFFFEFFFE;
		buf[i+3] = bin_search_log(__SMUAD(shifted, shifted)>>16);
	}

#if DEBUG_VEC_COMP
	print_array_q15("after log", buf+MIN_INDEX_MATMUL, MAX_INDEX_MATMUL-MIN_INDEX_MATMUL);
#endif

	//Mel-scaled filtering
	#pragma GCC unroll 21
	for(int i = 0 ; i < N_MEL_BIN; i++){
		arm_dot_prod_q15(buf+s_pos[i],ls[i],l_lens[i], &temp_vak);
		out[i] = (q7_t)(temp_vak>>26);
	}
#if PRINT_VEC || DEBUG_VEC_COMP
	print_array_q7("Melvec", out, N_MEL_BIN);
#endif
}

void treat_spec(q15_t* audio_data){
	//Compute max shift without overflow
	q15_t max_value;
	uint32_t trash;
	arm_max_q15( audio_data, (HOP_LENGTH*(N_MELVEC-1) + SAMPLE_PER_MELVEC), &max_value, &trash);
	max_value =  16-log2_q15(max_value);

	//Compute each vector
#pragma GCC unroll 10
	for (int i = 0 ; i < N_MELVEC ; i++){
		vec_computation(audio_data+HOP_LENGTH*i, melvec[i],max_value);
	}

	//De-noise + linear function for model
#pragma GCC unroll 21
	for (int i = 0 ; i < N_MEL_BIN ; i++){
		int16_t mean = 0;
#pragma GCC unroll 10
		for (int j = 0 ; j < N_MELVEC ; j++) mean += melvec[j][i];
		mean /= N_MELVEC;
#pragma GCC unroll 10
		for (int j = 0 ; j < N_MELVEC ; j++)
			melvec[j][i] = (int8_t)(((int16_t)melvec[j][i]-mean)*2-99);
	}
	
	//Inference
#if CLASSIFY
	MX_X_CUBE_AI_Process();
#endif

}

static void Vec_Callback(int buf_cplt) {
	if (ADCDataRdy[1-buf_cplt]) {
		print_now("Error: ADC Data buffer full\r\n");
		Error_Handler();
	}
	ADCDataRdy[buf_cplt] = 1;
	treat_spec((q15_t*)ADCData[buf_cplt]);
	ADCDataRdy[buf_cplt] = 0;

}

#endif

static void eff_Callback(int i){
#if SAVE_RAW_AUDIO
	Save_Callback(i);
#else
	Vec_Callback(i);
#endif

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	eff_Callback(1);
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	eff_Callback(0);
}

/*******************
 *
 * µSD
 *
 *******************/


int batext_is_card_inserted(void)
{
	return HAL_GPIO_ReadPin(BatExt_CD_GPIO_Port, BatExt_CD_Pin);
}


void batext_SD_init(void)
{
	// Mount
	HAL_Delay(1000); // to let time for SD to settle if just inserted
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
		print_error("f_mount error\n", fres);
		Error_Handler();
	}

	// Statistiques
	DWORD free_clusters, free_sectors, total_sectors;
	FATFS* getFreeFs;
	fres = f_getfree("", &free_clusters, &getFreeFs);
	if (fres != FR_OK) {
		print_error("f_getfree error\n", fres);
		Error_Handler();
	}
	total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
	free_sectors = free_clusters * getFreeFs->csize;
	print_now("SD card stats:\r\n");
	print_error("KiB total drive space:\n", total_sectors / 2);
	print_error("KiB available:\n" , free_sectors / 2);
}


void batext_SD_deinit(void)
{
	f_close(&fil);
	HAL_Delay(1000);

	f_mount(NULL, "", 0);
}


int batext_SD_write(const void *data, uint32_t size)
{
	/*if(write_count == 0){

		fres = f_open(&fil, "MYTEST", FA_WRITE | FA_OPEN_APPEND);

		write_count = (write_count+1)%20;
		if(fres != FR_OK) {
			print_error("f_open error\n", fres);
			return 1;
		}
	}*/

	UINT written;
	fres = f_write(&fil, data, size, &written);
	if(fres != FR_OK) {
		print_error("f_write error, trying to recover\n", fres);
		batext_SD_deinit();
		batext_SD_init();
		HAL_Delay(1000);
		fres = f_open(&fil, "TEST", FA_WRITE | FA_OPEN_APPEND);
		if(fres != FR_OK) {
			print_error("f_open error\n", fres);
		}
		fres = f_write(&fil, data, size, &written); //If we still fail, it seems dead
	}
	if(written != size) {
		print_now("f_write error : did not write all the bytes\r\n");
	}
	/*
	if(write_count == 0){
		f_close(&fil);
	}*/
	return FR_OK;
}
