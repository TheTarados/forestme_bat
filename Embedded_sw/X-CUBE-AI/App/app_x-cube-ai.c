
/**
  ******************************************************************************
  * @file    app_x-cube-ai.c
  * @author  X-CUBE-AI C code generator
  * @brief   AI program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *   v2.0 - add multiple IO and/or multiple heap support
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\7.1.0
  */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#if defined ( __ICCARM__ )
#define AI_SRAM   _Pragma("location=\"AI_SRAM\"")
#elif defined ( __CC_ARM ) || ( __GNUC__ )
#define AI_SRAM   __attribute__((section(".AI_SRAM")))
#endif

/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"
#include "bat_det_net.h"
#include "bat_det_net_data.h"

/* USER CODE BEGIN includes */
#include "batext.h"
/* USER CODE END includes */

/* IO buffers ----------------------------------------------------------------*/

#if !defined(AI_BAT_DET_NET_INPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_in_1[AI_BAT_DET_NET_IN_1_SIZE_BYTES];
ai_i8* data_ins[AI_BAT_DET_NET_IN_NUM] = {
data_in_1
};
#else
ai_i8* data_ins[AI_BAT_DET_NET_IN_NUM] = {
NULL
};
#endif

#if !defined(AI_BAT_DET_NET_OUTPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_out_1[AI_BAT_DET_NET_OUT_1_SIZE_BYTES];
ai_i8* data_outs[AI_BAT_DET_NET_OUT_NUM] = {
data_out_1
};
#else
ai_i8* data_outs[AI_BAT_DET_NET_OUT_NUM] = {
NULL
};
#endif

/* Activations buffers -------------------------------------------------------*/

AI_ALIGNED(32)
AI_SRAM
static uint8_t pool0[AI_BAT_DET_NET_DATA_ACTIVATION_1_SIZE];

ai_handle data_activations0[] = {pool0};

/* AI objects ----------------------------------------------------------------*/

static ai_handle bat_det_net = AI_HANDLE_NULL;

static ai_buffer* ai_input;
static ai_buffer* ai_output;

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
	print_now("Error in AI: ");
	if (fct)print_now(fct);

    print_error("\r\ntype=", err.type);
    print_error("code=", err.code);

  do {} while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle *act_addr)
{
  ai_error err;

  /* Create and initialize an instance of the model */
  err = ai_bat_det_net_create_and_init(&bat_det_net, act_addr, NULL);
  if (err.type != AI_ERROR_NONE) {
    ai_log_err(err, "ai_bat_det_net_create_and_init");
    return -1;
  }

  ai_input = ai_bat_det_net_inputs_get(bat_det_net, NULL);
  ai_output = ai_bat_det_net_outputs_get(bat_det_net, NULL);

#if defined(AI_BAT_DET_NET_INPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-inputs" option is used, memory buffer can be
   *  used from the activations buffer. This is not mandatory.
   */
  for (int idx=0; idx < AI_BAT_DET_NET_IN_NUM; idx++) {
	data_ins[idx] = ai_input[idx].data;
  }
#else
  for (int idx=0; idx < AI_BAT_DET_NET_IN_NUM; idx++) {
	  ai_input[idx].data = data_ins[idx];
  }
#endif

#if defined(AI_BAT_DET_NET_OUTPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-outputs" option is used, memory buffer can be
   *  used from the activations buffer. This is no mandatory.
   */
  for (int idx=0; idx < AI_BAT_DET_NET_OUT_NUM; idx++) {
	data_outs[idx] = ai_output[idx].data;
  }
#else
  for (int idx=0; idx < AI_BAT_DET_NET_OUT_NUM; idx++) {
	ai_output[idx].data = data_outs[idx];
  }
#endif

  return 0;
}

static int ai_run(void)
{
  ai_i32 batch;

  batch = ai_bat_det_net_run(bat_det_net, ai_input, ai_output);
  if (batch != 1) {
    ai_log_err(ai_bat_det_net_get_error(bat_det_net),
        "ai_bat_det_net_run");
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */
extern q7_t melspec [N_MEL_BIN*N_MELVEC];


#if TEST_MODEL
int8_t test_input[N_MEL_BIN*N_MELVEC] = { -93, -89, -93,-103, -99,-105, -93, -99,-105, -95, -87, -89,-105,-103,
   -95, -97,-103,-103,-105, -97, -99, -93,-101, -99, -93,-101, -99, -95,
   -97, -95, -99, -97, -95, -99, -97, -99, -97, -97, -99, -99, -99, -99,
   -95, -99, -99, -99, -97, -99, -99, -99, -99, -99, -99, -99, -97, -99,
   -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99,
   -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99,
   -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99,
   -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99,
   -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99,
   -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99,
   -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99,
   -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99,
   -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99,
   -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99,
   -99, -99, -99, -99};
#endif

int acquire_and_process_data(ai_i8* data[])
{
  
#if TEST_MODEL
	for (int i=0; i < N_MEL_BIN*N_MELVEC; i++ ){
		((int8_t **) data)[0][i] = test_input[i];//test_input{i+N_MEL_BIN*j};//
	}
#else
	for (int i=0; i < N_MEL_BIN; i++ ){
		for (int j=0; j < N_MELVEC; j++ ){
			((int8_t **) data)[0][j+N_MELVEC*i] = melspec[i+N_MEL_BIN*j];
		}
	}
#endif


  return 0;
}

extern uint32_t registered_times[1536];
extern uint16_t time_index;
int post_process(ai_i8* data[])
{
  
	//if((int8_t)(data[0][0])>0){
	if((uint8_t)(data[0][0])>76 && time_index<10000){
		//print_now("Think there is a bat right now: ");
		//print_int((uint8_t)(data[0][0]));
		//print_now("\r\n");
		//print_time();
		registered_times[time_index++]=get_time();
		print_int(get_time());

		print_now("    ");
		print_time();
		print_now("\r\n");
	}
  return 0;
}
/* USER CODE END 2 */

/* Entry points --------------------------------------------------------------*/

void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */
  print_now("\r\nAI initialization\r\n");

  ai_boostrap(data_activations0);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */
  int res = -1;

  //print_now("\r\AI - run\r\n");

	if (bat_det_net) {
		/* 1 - acquire and pre-process input data */
		res = acquire_and_process_data(data_ins);
		//print_error("After acquire: ", res);
		/* 2 - process the data - call inference engine */
		if (res == 0)
			res = ai_run();
		//print_error("After run: ", res);
		/* 3- post-process the predictions */
		if (res == 0)
			res = post_process(data_outs);
		//print_error("After process: ", res);
	}
	if (res) {
		print_now("Error\r\n");
		ai_error err = {AI_ERROR_INVALID_STATE, AI_ERROR_CODE_NETWORK};
		ai_log_err(err, "Process has FAILED");
	}
    /* USER CODE END 6 */
}
#ifdef __cplusplus
}
#endif
