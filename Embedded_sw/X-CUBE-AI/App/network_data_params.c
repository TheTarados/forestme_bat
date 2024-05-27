/**
  ******************************************************************************
  * @file    network_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon Dec 11 16:39:48 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "network_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_network_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_network_weights_array_u64[34] = {
  0xc8fb379dc43e7f4fU, 0xa3c18187bbe0bab2U, 0x7f28e1e4370c0252U, 0x27f7810fd3e73a9bU,
  0xfffffef578cac7d5U, 0xd0ffffff48U, 0xcb06f9e4ffffffcfU, 0xda39e0fec5363d14U,
  0xfb29f822551eabf0U, 0x7f084cf5b418030fU, 0x5ee6701a13f976fdU, 0x9ddea02e3bce1a3U,
  0x48e72edf3f3deb7fU, 0x9ab8f2e9c2d114ccU, 0x1107ef087719d314U, 0x81f0ca1df4bd33f7U,
  0xc422e106daee22e9U, 0xd3b4e20de80c0808U, 0xe9ac55e41dd5de48U, 0x94daf613dbd5d4c6U,
  0x180243c6170f31acU, 0x2dde11d61bdb148bU, 0xf810cc810afd08cfU, 0xedefd4ccf308b19fU,
  0x217e7f9fda4U, 0x61efffffdf7U, 0xfce6ef0300000268U, 0xdbc51919f11df401U,
  0x81c761dbb4c93230U, 0xf1b75bfbce944b0aU, 0x4ea452093ec347faU, 0xb8a05e8f69a3df8U,
  0xee9ef4d5ca9ef7efU, 0xfffffc8302da13fbU,
};


ai_handle g_network_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_network_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

