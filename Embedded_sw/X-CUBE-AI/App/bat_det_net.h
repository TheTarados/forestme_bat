/**
  ******************************************************************************
  * @file    bat_det_net.h
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

#ifndef AI_BAT_DET_NET_H
#define AI_BAT_DET_NET_H
#pragma once

#include "bat_det_net_config.h"
#include "ai_platform.h"

/******************************************************************************/
#define AI_BAT_DET_NET_MODEL_NAME          "bat_det_net"
#define AI_BAT_DET_NET_ORIGIN_MODEL_NAME   "quantization_default_8bit_model_h5_to_tflite"

/******************************************************************************/
#define AI_BAT_DET_NET_ACTIVATIONS_ALIGNMENT   (4)
#define AI_BAT_DET_NET_INPUTS_IN_ACTIVATIONS   (4)
#define AI_BAT_DET_NET_OUTPUTS_IN_ACTIVATIONS  (4)

/******************************************************************************/
#define AI_BAT_DET_NET_IN_NUM        (1)

AI_DEPRECATED
#define AI_BAT_DET_NET_IN \
  ai_bat_det_net_inputs_get(AI_HANDLE_NULL, NULL)

#define AI_BAT_DET_NET_IN_SIZE { \
  AI_BAT_DET_NET_IN_1_SIZE, \
}
#define AI_BAT_DET_NET_IN_SIZE_BYTES { \
  AI_BAT_DET_NET_IN_1_SIZE_BYTES, \
}
#define AI_BAT_DET_NET_IN_1_FORMAT      AI_BUFFER_FORMAT_S8
#define AI_BAT_DET_NET_IN_1_HEIGHT      (20)
#define AI_BAT_DET_NET_IN_1_WIDTH       (10)
#define AI_BAT_DET_NET_IN_1_CHANNEL     (1)
#define AI_BAT_DET_NET_IN_1_SIZE        (20 * 10 * 1)
#define AI_BAT_DET_NET_IN_1_SIZE_BYTES  (200)

/******************************************************************************/
#define AI_BAT_DET_NET_OUT_NUM       (1)

AI_DEPRECATED
#define AI_BAT_DET_NET_OUT \
  ai_bat_det_net_outputs_get(AI_HANDLE_NULL, NULL)

#define AI_BAT_DET_NET_OUT_SIZE { \
  AI_BAT_DET_NET_OUT_1_SIZE, \
}
#define AI_BAT_DET_NET_OUT_SIZE_BYTES { \
  AI_BAT_DET_NET_OUT_1_SIZE_BYTES, \
}
#define AI_BAT_DET_NET_OUT_1_FORMAT      AI_BUFFER_FORMAT_U8
#define AI_BAT_DET_NET_OUT_1_CHANNEL     (1)
#define AI_BAT_DET_NET_OUT_1_SIZE        (1)
#define AI_BAT_DET_NET_OUT_1_SIZE_BYTES  (1)

/******************************************************************************/
#define AI_BAT_DET_NET_N_NODES (8)


AI_API_DECLARE_BEGIN

/*!
 * @defgroup bat_det_net
 * @brief Public neural network APIs
 * @details This is the header for the network public APIs declarations
 * for interfacing a generated network model.
 * @details The public neural network APIs hide the structure of the network
 * and offer a set of interfaces to create, initialize, query, configure, 
 * run and destroy a network instance.
 * To handle this, an opaque handler to the network context is provided 
 * on creation.
 * The APIs are meant as stadard interfaces for the calling code; depending on
 * the supported platforms and the models, different implementations could be
 * available.
 */

/******************************************************************************/
/*! Public API Functions Declarations */

/*!
 * @brief Get network library info as a datastruct.
 * @ingroup bat_det_net
 * @param[in] network: the handler to the network context
 * @param[out] report a pointer to the report struct where to
 * store network info. See @ref ai_network_report struct for details
 * @return a boolean reporting the exit status of the API
 */
AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_bat_det_net_get_info(
  ai_handle network, ai_network_report* report);


/*!
 * @brief Get network library report as a datastruct.
 * @ingroup bat_det_net
 * @param[in] network: the handler to the network context
 * @param[out] report a pointer to the report struct where to
 * store network info. See @ref ai_network_report struct for details
 * @return a boolean reporting the exit status of the API
 */
AI_API_ENTRY
ai_bool ai_bat_det_net_get_report(
  ai_handle network, ai_network_report* report);

/*!
 * @brief Get first network error code.
 * @ingroup bat_det_net
 * @details Get an error code related to the 1st error generated during
 * network processing. The error code is structure containing an 
 * error type indicating the type of error with an associated error code
 * Note: after this call the error code is internally reset to AI_ERROR_NONE
 * @param network an opaque handle to the network context
 * @return an error type/code pair indicating both the error type and code
 * see @ref ai_error for struct definition
 */
AI_API_ENTRY
ai_error ai_bat_det_net_get_error(ai_handle network);

/*!
 * @brief Create a neural network.
 * @ingroup bat_det_net
 * @details Instantiate a network and returns an object to handle it;
 * @param network an opaque handle to the network context
 * @param network_config a pointer to the network configuration info coded as a 
 * buffer
 * @return an error code reporting the status of the API on exit
 */
AI_API_ENTRY
ai_error ai_bat_det_net_create(
  ai_handle* network, const ai_buffer* network_config);

/*!
 * @brief Destroy a neural network and frees the allocated memory.
 * @ingroup bat_det_net
 * @details Destroys the network and frees its memory. The network handle is returned;
 * if the handle is not NULL, the unloading has not been successful.
 * @param network an opaque handle to the network context
 * @return an object handle : AI_HANDLE_NULL if network was destroyed
 * correctly. The same input network handle if destroy failed.
 */
AI_API_ENTRY
ai_handle ai_bat_det_net_destroy(ai_handle network);

/*!
 * @brief Initialize the data structures of the network.
 * @ingroup bat_det_net
 * @details This API initialized the network after a successfull
 * @ref ai_bat_det_net_create. Both the activations memory buffer 
 * and params (i.e. weights) need to be provided by caller application
 * 
 * @param network an opaque handle to the network context
 * @param params the parameters of the network (required). 
 * see @ref ai_network_params struct for details
 * @return true if the network was correctly initialized, false otherwise
 * in case of error the error type could be queried by 
 * using @ref ai_bat_det_net_get_error
 */
AI_API_ENTRY
ai_bool ai_bat_det_net_init(
  ai_handle network, const ai_network_params* params);

/*!
 * @brief Create and initialize a neural network (helper function)
 * @ingroup bat_det_net
 * @details Helper function to instantiate and to initialize a network. It returns an object to handle it;
 * @param network an opaque handle to the network context
 * @param activations array of addresses of the activations buffers
 * @param weights array of addresses of the weights buffers
 * @return an error code reporting the status of the API on exit
 */
AI_API_ENTRY
ai_error ai_bat_det_net_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[]);

/*!
 * @brief Get network inputs array pointer as a ai_buffer array pointer.
 * @ingroup bat_det_net
 * @param network an opaque handle to the network context
 * @param n_buffer optional parameter to return the number of outputs
 * @return a ai_buffer pointer to the inputs arrays
 */
AI_API_ENTRY
ai_buffer* ai_bat_det_net_inputs_get(
  ai_handle network, ai_u16 *n_buffer);

/*!
 * @brief Get network outputs array pointer as a ai_buffer array pointer.
 * @ingroup bat_det_net
 * @param network an opaque handle to the network context
 * @param n_buffer optional parameter to return the number of outputs
 * @return a ai_buffer pointer to the outputs arrays
 */
AI_API_ENTRY
ai_buffer* ai_bat_det_net_outputs_get(
  ai_handle network, ai_u16 *n_buffer);

/*!
 * @brief Run the network and return the output
 * @ingroup bat_det_net
 *
 * @details Runs the network on the inputs and returns the corresponding output.
 * The size of the input and output buffers is stored in this
 * header generated by the code generation tool. See AI_BAT_DET_NET_*
 * defines into file @ref bat_det_net.h for all network sizes defines
 *
 * @param network an opaque handle to the network context
 * @param[in] input buffer with the input data
 * @param[out] output buffer with the output data
 * @return the number of input batches processed (default 1) or <= 0 if it fails
 * in case of error the error type could be queried by 
 * using @ref ai_bat_det_net_get_error
 */
AI_API_ENTRY
ai_i32 ai_bat_det_net_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output);

/*!
 * @brief Runs the network on the inputs.
 * @ingroup bat_det_net
 *
 * @details Differently from @ref ai_network_run, no output is returned, e.g. for
 * temporal models with a fixed step size.
 *
 * @param network the network to be run
 * @param[in] input buffer with the input data
 * @return the number of input batches processed (usually 1) or <= 0 if it fails
 * in case of error the error type could be queried by 
 * using @ref ai_bat_det_net_get_error
 */
AI_API_ENTRY
ai_i32 ai_bat_det_net_forward(
  ai_handle network, const ai_buffer* input);

AI_API_DECLARE_END

#endif /* AI_BAT_DET_NET_H */
