/**
  ******************************************************************************
  * @file    bat_det_net_data.h
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

#ifndef BAT_DET_NET_DATA_H
#define BAT_DET_NET_DATA_H
#pragma once

#include "bat_det_net_config.h"
#include "bat_det_net_data_params.h"

AI_DEPRECATED
#define AI_BAT_DET_NET_DATA_ACTIVATIONS(ptr_)  \
  ai_bat_det_net_data_activations_buffer_get(AI_HANDLE_PTR(ptr_))

AI_DEPRECATED
#define AI_BAT_DET_NET_DATA_WEIGHTS(ptr_)  \
  ai_bat_det_net_data_weights_buffer_get(AI_HANDLE_PTR(ptr_))


AI_API_DECLARE_BEGIN


extern const ai_u64 s_bat_det_net_weights_array_u64[87];



/*!
 * @brief Get network activations buffer initialized struct.
 * @ingroup bat_det_net_data
 * @param[in] ptr a pointer to the activations array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_bat_det_net_data_activations_buffer_get(const ai_handle ptr);

/*!
 * @brief Get network weights buffer initialized struct.
 * @ingroup bat_det_net_data
 * @param[in] ptr a pointer to the weights array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_bat_det_net_data_weights_buffer_get(const ai_handle ptr);

/*!
 * @brief Get network weights array pointer as a handle ptr.
 * @ingroup bat_det_net_data
 * @return a ai_handle pointer to the weights array
 */
AI_DEPRECATED
AI_API_ENTRY
ai_handle ai_bat_det_net_data_weights_get(void);


/*!
 * @brief Get network params configuration data structure.
 * @ingroup bat_det_net_data
 * @return true if a valid configuration is present, false otherwise
 */
AI_API_ENTRY
ai_bool ai_bat_det_net_data_params_get(ai_network_params* params);


AI_API_DECLARE_END

#endif /* BAT_DET_NET_DATA_H */

