/*
 * batext.h
 *
 *  Created on: 30 Apr 2023
 *      Author: brock
 */

#ifndef INC_BATEXT_H_
#define INC_BATEXT_H_ 0

#include "main.h"
#include "arm_math.h"

#define N_MELVEC 10
#define N_MEL_BIN 20
#define SAMPLE_PER_MELVEC	512
#define HOP_LENGTH	270

#define SAVE_RAW_AUDIO 0
#define CLASSIFY 1

#define UART 	0
#define SD_CARD 1

#define CHOSEN_OUTPUT SD_CARD

#if SAVE_RAW_AUDIO
#define ADC_BUF_SIZE	10000
#else
#define ADC_BUF_SIZE	4000
#endif

#define  TEST_MODEL     0
#define DEBUG_VEC_COMP	0
#define PRINT_VEC		1

void batext_power_on(void);
void batext_power_off(void);
void batext_choose_gain(uint8_t gain);
int batext_is_card_inserted(void);
int batext_SD_write(const void *data, uint32_t size);
void vec_computation(q15_t* in, q7_t* out, uint8_t);




extern ADC_HandleTypeDef hadc;
extern TIM_HandleTypeDef htim1;

#endif /* INC_BATEXT_H_ */
