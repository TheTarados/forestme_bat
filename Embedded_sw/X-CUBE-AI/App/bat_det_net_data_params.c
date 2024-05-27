/**
  ******************************************************************************
  * @file    bat_det_net_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue May 14 16:11:23 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "bat_det_net_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_bat_det_net_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_bat_det_net_weights_array_u64[87] = {
  0xf4054a5c81e9a590U, 0x61b77f72a22c261cU, 0x81f0b3efd5615ce3U, 0x55a7811e450aebe3U,
  0xfffffffcde0b371bU, 0x7f00000005U, 0x1b47eeeeffffffffU, 0x547f113d5162dfccU,
  0xfc01f9f6141d4d17U, 0x1b0bf644d85ce939U, 0xda8c0ce73f4cd81eU, 0x27c56a3ff197c7f5U,
  0x1c218c2014ae238aU, 0x767f3bc33b3408d3U, 0x91e8a8edc4fbf2b8U, 0x1113f02640133d00U,
  0x805f710c917d3ecU, 0xd90fbbcbc5edaae7U, 0xd348e1e281fee7a7U, 0x491908f6e0402dfaU,
  0x140bb63f0d0dde7fU, 0x1c150efc22c4e9e2U, 0x31a9400bb569dbbeU, 0x7ee362805f690e2U,
  0x12d60d2e9e9U, 0xff00000012U, 0xecfd0ffb00000044U, 0x4ffff000df90eU,
  0xc18f305e905fa01U, 0xf07f40107f916ebU, 0x100f12d9fbdff7efU, 0xf41bfd05f3ff1803U,
  0x5f302000e04d80dU, 0x120e0f0dffff1212U, 0xa15f8f21b0c15U, 0xceaf9050c08040bU,
  0x9080f0219f5ecfbU, 0x8fa080ff11bfe0bU, 0xb1817f91af403fcU, 0xf9eafef9ee0c041aU,
  0x1d160e0afd2ce802U, 0x1c0ff9e916180ef7U, 0x1c0df8fef0fa2210U, 0xf2dcfff91a05040cU,
  0xfffdfafe9c11bb02U, 0xbe5ea040621fdfaU, 0xf8ea1502000dfb01U, 0x80c100806fb1afdU,
  0xeffb17e818f5e4fdU, 0xcff507fa1cfafa17U, 0xf51b0102e005b819U, 0x8100c218ae02f9f1U,
  0x105f814011efffeU, 0xeaef0006f00d05efU, 0xfdeb1715fc190aebU, 0xea0614e9fa1c18f5U,
  0xe8dd1b07061208e1U, 0xf0e1f3d5e01ce9eeU, 0x1800130108fbfb0cU, 0xe0906031415ed09U,
  0xd11b8f14eeedf70bU, 0x9ebf3f60de5fc08U, 0xe823020af41b1ceeU, 0x71218fd1714e009U,
  0xedf901e9f9eefaeeU, 0x3e613170a06eeeaU, 0xf902f20b0ef1fa00U, 0xdefd08e60df7fd12U,
  0xffffffd4f004d01fU, 0xffffff93ffffff91U, 0xffffff7c00000001U, 0xffffffae00000026U,
  0xfffffffd0000002fU, 0xffffffea00000047U, 0x3600000055U, 0x3a00000041U,
  0x6700000061U, 0xffffffac00000029U, 0xfffffffbffffffe8U, 0x40fffffff0U,
  0x24ffffff94U, 0x5fffffff9U, 0xc6f4e9ff00000052U, 0xc540303135c61dd1U,
  0xd6cc0c81923831bcU, 0x9ed0f735e487d754U, 0xd6U,
};


ai_handle g_bat_det_net_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_bat_det_net_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

