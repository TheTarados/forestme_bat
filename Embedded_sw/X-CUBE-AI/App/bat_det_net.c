/**
  ******************************************************************************
  * @file    bat_det_net.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue May 14 16:11:23 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "bat_det_net.h"
#include "bat_det_net_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_bat_det_net
 
#undef AI_BAT_DET_NET_MODEL_SIGNATURE
#define AI_BAT_DET_NET_MODEL_SIGNATURE     "908c48a37f600a9d80ad0496e32893d1"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Tue May 14 16:11:23 2024"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_BAT_DET_NET_N_BATCHES
#define AI_BAT_DET_NET_N_BATCHES         (1)

static ai_ptr g_bat_det_net_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_bat_det_net_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  nl_7_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conversion_8_output_array, AI_ARRAY_FORMAT_U8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 1, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 36, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 4, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 144, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 4, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  gemm_5_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 336, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  gemm_5_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 28, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  gemm_6_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 28, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  gemm_6_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 164, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 488, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  gemm_5_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 12, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  gemm_6_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 28, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_input_10_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 200, AI_STATIC)
/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 576, AI_STATIC)
/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  pool_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 144, AI_STATIC)
/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 56, AI_STATIC)
/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  pool_3_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 12, AI_STATIC)
/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  gemm_5_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 28, AI_STATIC)
/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  gemm_6_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1, AI_STATIC)
/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_7_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conversion_8_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_U8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_UINTQ_ZP(0)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_0_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 4,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00451662577688694f, 0.003003212623298168f, 0.005451330449432135f, 0.004499475471675396f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_2_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 4,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003496265970170498f, 0.004549023229628801f, 0.0058537693694233894f, 0.0034830488730221987f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_5_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.015134491957724094f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_6_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.007347928360104561f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(serving_default_input_10_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.40784314274787903f),
    AI_PACK_INTQ_ZP(-99)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.30944108963012695f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(pool_1_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.30944108963012695f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_2_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.3234529495239258f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(pool_3_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.3234529495239258f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_5_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.1296682059764862f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_6_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.28771141171455383f),
    AI_PACK_INTQ_ZP(80)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  nl_7_output, AI_STATIC,
  0, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1, 1),
  1, &nl_7_output_array, &nl_7_output_array_intq)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conversion_8_output, AI_STATIC,
  1, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1, 1),
  1, &conversion_8_output_array, &conversion_8_output_array_intq)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_weights, AI_STATIC,
  2, 0x1,
  AI_SHAPE_INIT(4, 1, 3, 3, 4), AI_STRIDE_INIT(4, 1, 1, 4, 12),
  1, &conv2d_0_weights_array, &conv2d_0_weights_array_intq)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_bias, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &conv2d_0_bias_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_weights, AI_STATIC,
  4, 0x1,
  AI_SHAPE_INIT(4, 4, 3, 3, 4), AI_STRIDE_INIT(4, 1, 4, 16, 48),
  1, &conv2d_2_weights_array, &conv2d_2_weights_array_intq)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_bias, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &conv2d_2_bias_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  gemm_5_weights, AI_STATIC,
  6, 0x1,
  AI_SHAPE_INIT(4, 12, 28, 1, 1), AI_STRIDE_INIT(4, 1, 12, 336, 336),
  1, &gemm_5_weights_array, &gemm_5_weights_array_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  gemm_5_bias, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 1, 1), AI_STRIDE_INIT(4, 4, 4, 112, 112),
  1, &gemm_5_bias_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  gemm_6_weights, AI_STATIC,
  8, 0x1,
  AI_SHAPE_INIT(4, 28, 1, 1, 1), AI_STRIDE_INIT(4, 1, 28, 28, 28),
  1, &gemm_6_weights_array, &gemm_6_weights_array_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  gemm_6_bias, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &gemm_6_bias_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_scratch0, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 164, 1, 1), AI_STRIDE_INIT(4, 1, 1, 164, 164),
  1, &conv2d_0_scratch0_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_scratch0, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 488, 1, 1), AI_STRIDE_INIT(4, 1, 1, 488, 488),
  1, &conv2d_2_scratch0_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  gemm_5_scratch0, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 2, 2, 24, 24),
  1, &gemm_5_scratch0_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  gemm_6_scratch0, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 1, 1), AI_STRIDE_INIT(4, 2, 2, 56, 56),
  1, &gemm_6_scratch0_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_input_10_output, AI_STATIC,
  14, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 10, 20), AI_STRIDE_INIT(4, 1, 1, 1, 10),
  1, &serving_default_input_10_output_array, &serving_default_input_10_output_array_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_output, AI_STATIC,
  15, 0x1,
  AI_SHAPE_INIT(4, 1, 4, 8, 18), AI_STRIDE_INIT(4, 1, 1, 4, 32),
  1, &conv2d_0_output_array, &conv2d_0_output_array_intq)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  pool_1_output, AI_STATIC,
  16, 0x1,
  AI_SHAPE_INIT(4, 1, 4, 4, 9), AI_STRIDE_INIT(4, 1, 1, 4, 16),
  1, &pool_1_output_array, &pool_1_output_array_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_output, AI_STATIC,
  17, 0x1,
  AI_SHAPE_INIT(4, 1, 4, 2, 7), AI_STRIDE_INIT(4, 1, 1, 4, 8),
  1, &conv2d_2_output_array, &conv2d_2_output_array_intq)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  pool_3_output, AI_STATIC,
  18, 0x1,
  AI_SHAPE_INIT(4, 1, 4, 1, 3), AI_STRIDE_INIT(4, 1, 1, 4, 4),
  1, &pool_3_output_array, &pool_3_output_array_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  pool_3_output0, AI_STATIC,
  19, 0x1,
  AI_SHAPE_INIT(4, 1, 12, 1, 1), AI_STRIDE_INIT(4, 1, 1, 12, 12),
  1, &pool_3_output_array, &pool_3_output_array_intq)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  gemm_5_output, AI_STATIC,
  20, 0x1,
  AI_SHAPE_INIT(4, 1, 28, 1, 1), AI_STRIDE_INIT(4, 1, 1, 28, 28),
  1, &gemm_5_output_array, &gemm_5_output_array_intq)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  gemm_6_output, AI_STATIC,
  21, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1, 1),
  1, &gemm_6_output_array, &gemm_6_output_array_intq)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conversion_8_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_8_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conversion_8_layer, 8,
  NL_TYPE, 0x0, NULL,
  nl, node_convert_integer,
  &conversion_8_chain,
  NULL, &conversion_8_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_i8 nl_7_nl_params_data[] = { -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -127, -127, -127, -127, -126, -125, -125, -124, -122, -120, -118, -114, -110, -105, -98, -89, -79, -66, -52, -36, -18, 0, 18, 36, 52, 66, 79, 89, 98, 105, 110, 114, 118, 120, 122, 124, 125, 125, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
AI_ARRAY_OBJ_DECLARE(
    nl_7_nl_params, AI_ARRAY_FORMAT_S8,
    nl_7_nl_params_data, nl_7_nl_params_data, 256, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_7_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_6_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_7_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_7_layer, 7,
  NL_TYPE, 0x0, NULL,
  nl, forward_nl_integer,
  &nl_7_chain,
  NULL, &conversion_8_layer, AI_STATIC, 
  .nl_params = &nl_7_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_6_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_6_weights, &gemm_6_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_6_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_6_layer, 6,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA,
  &gemm_6_chain,
  NULL, &nl_7_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_3_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_5_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_5_weights, &gemm_5_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_5_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_5_layer, 5,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA,
  &gemm_5_chain,
  NULL, &gemm_6_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  pool_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_3_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  pool_3_layer, 3,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp_integer_INT8,
  &pool_3_chain,
  NULL, &gemm_5_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_2_weights, &conv2d_2_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_2_layer, 2,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_sssa8_ch,
  &conv2d_2_chain,
  NULL, &pool_3_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  pool_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_1_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  pool_1_layer, 1,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp_integer_INT8,
  &pool_1_chain,
  NULL, &conv2d_2_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_input_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_0_weights, &conv2d_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_0_layer, 0,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_sssa8_ch,
  &conv2d_0_chain,
  NULL, &pool_1_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 692, 1, 1),
    692, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 940, 1, 1),
    940, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_BAT_DET_NET_IN_NUM, &serving_default_input_10_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_BAT_DET_NET_OUT_NUM, &conversion_8_output),
  &conv2d_0_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 692, 1, 1),
      692, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 940, 1, 1),
      940, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_BAT_DET_NET_IN_NUM, &serving_default_input_10_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_BAT_DET_NET_OUT_NUM, &conversion_8_output),
  &conv2d_0_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool bat_det_net_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_bat_det_net_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_input_10_output_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 0);
    serving_default_input_10_output_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 0);
    
    conv2d_0_scratch0_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 200);
    conv2d_0_scratch0_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 200);
    
    conv2d_0_output_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 364);
    conv2d_0_output_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 364);
    
    pool_1_output_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 0);
    pool_1_output_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 0);
    
    conv2d_2_scratch0_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 144);
    conv2d_2_scratch0_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 144);
    
    conv2d_2_output_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 632);
    conv2d_2_output_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 632);
    
    pool_3_output_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 0);
    pool_3_output_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 0);
    
    gemm_5_scratch0_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 12);
    gemm_5_scratch0_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 12);
    
    gemm_5_output_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 36);
    gemm_5_output_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 36);
    
    gemm_6_scratch0_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 64);
    gemm_6_scratch0_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 64);
    
    gemm_6_output_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 0);
    gemm_6_output_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 0);
    
    nl_7_output_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 4);
    nl_7_output_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 4);
    
    conversion_8_output_array.data = AI_PTR(g_bat_det_net_activations_map[0] + 0);
    conversion_8_output_array.data_start = AI_PTR(g_bat_det_net_activations_map[0] + 0);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool bat_det_net_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_bat_det_net_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    conv2d_0_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_0_weights_array.data = AI_PTR(g_bat_det_net_weights_map[0] + 0);
    conv2d_0_weights_array.data_start = AI_PTR(g_bat_det_net_weights_map[0] + 0);
    
    conv2d_0_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_0_bias_array.data = AI_PTR(g_bat_det_net_weights_map[0] + 36);
    conv2d_0_bias_array.data_start = AI_PTR(g_bat_det_net_weights_map[0] + 36);
    
    conv2d_2_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_weights_array.data = AI_PTR(g_bat_det_net_weights_map[0] + 52);
    conv2d_2_weights_array.data_start = AI_PTR(g_bat_det_net_weights_map[0] + 52);
    
    conv2d_2_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_bias_array.data = AI_PTR(g_bat_det_net_weights_map[0] + 196);
    conv2d_2_bias_array.data_start = AI_PTR(g_bat_det_net_weights_map[0] + 196);
    
    gemm_5_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_5_weights_array.data = AI_PTR(g_bat_det_net_weights_map[0] + 212);
    gemm_5_weights_array.data_start = AI_PTR(g_bat_det_net_weights_map[0] + 212);
    
    gemm_5_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_5_bias_array.data = AI_PTR(g_bat_det_net_weights_map[0] + 548);
    gemm_5_bias_array.data_start = AI_PTR(g_bat_det_net_weights_map[0] + 548);
    
    gemm_6_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_6_weights_array.data = AI_PTR(g_bat_det_net_weights_map[0] + 660);
    gemm_6_weights_array.data_start = AI_PTR(g_bat_det_net_weights_map[0] + 660);
    
    gemm_6_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_6_bias_array.data = AI_PTR(g_bat_det_net_weights_map[0] + 688);
    gemm_6_bias_array.data_start = AI_PTR(g_bat_det_net_weights_map[0] + 688);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_bat_det_net_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_BAT_DET_NET_MODEL_NAME,
      .model_signature   = AI_BAT_DET_NET_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 8228,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_bat_det_net_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_BAT_DET_NET_MODEL_NAME,
      .model_signature   = AI_BAT_DET_NET_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 8228,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_bat_det_net_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_bat_det_net_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_bat_det_net_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_bat_det_net_create(network, AI_BAT_DET_NET_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_bat_det_net_data_params_get(&params) != true) {
        err = ai_bat_det_net_get_error(*network);
        return err;
    }
#if defined(AI_BAT_DET_NET_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_BAT_DET_NET_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_bat_det_net_init(*network, &params) != true) {
        err = ai_bat_det_net_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_bat_det_net_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_bat_det_net_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_bat_det_net_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_bat_det_net_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= bat_det_net_configure_weights(net_ctx, params);
  ok &= bat_det_net_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_bat_det_net_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_bat_det_net_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_BAT_DET_NET_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

