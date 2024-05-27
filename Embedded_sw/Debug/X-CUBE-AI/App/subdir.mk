################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../X-CUBE-AI/App/app_x-cube-ai.c \
../X-CUBE-AI/App/bat_det_net.c \
../X-CUBE-AI/App/bat_det_net_data.c \
../X-CUBE-AI/App/bat_det_net_data_params.c \
../X-CUBE-AI/App/network.c \
../X-CUBE-AI/App/network_data.c \
../X-CUBE-AI/App/network_data_params.c 

OBJS += \
./X-CUBE-AI/App/app_x-cube-ai.o \
./X-CUBE-AI/App/bat_det_net.o \
./X-CUBE-AI/App/bat_det_net_data.o \
./X-CUBE-AI/App/bat_det_net_data_params.o \
./X-CUBE-AI/App/network.o \
./X-CUBE-AI/App/network_data.o \
./X-CUBE-AI/App/network_data_params.o 

C_DEPS += \
./X-CUBE-AI/App/app_x-cube-ai.d \
./X-CUBE-AI/App/bat_det_net.d \
./X-CUBE-AI/App/bat_det_net_data.d \
./X-CUBE-AI/App/bat_det_net_data_params.d \
./X-CUBE-AI/App/network.d \
./X-CUBE-AI/App/network_data.d \
./X-CUBE-AI/App/network_data_params.d 


# Each subdirectory must supply rules for building sources it contributes
X-CUBE-AI/App/%.o X-CUBE-AI/App/%.su X-CUBE-AI/App/%.cyclo: ../X-CUBE-AI/App/%.c X-CUBE-AI/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -I../X-CUBE-AI -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-X-2d-CUBE-2d-AI-2f-App

clean-X-2d-CUBE-2d-AI-2f-App:
	-$(RM) ./X-CUBE-AI/App/app_x-cube-ai.cyclo ./X-CUBE-AI/App/app_x-cube-ai.d ./X-CUBE-AI/App/app_x-cube-ai.o ./X-CUBE-AI/App/app_x-cube-ai.su ./X-CUBE-AI/App/bat_det_net.cyclo ./X-CUBE-AI/App/bat_det_net.d ./X-CUBE-AI/App/bat_det_net.o ./X-CUBE-AI/App/bat_det_net.su ./X-CUBE-AI/App/bat_det_net_data.cyclo ./X-CUBE-AI/App/bat_det_net_data.d ./X-CUBE-AI/App/bat_det_net_data.o ./X-CUBE-AI/App/bat_det_net_data.su ./X-CUBE-AI/App/bat_det_net_data_params.cyclo ./X-CUBE-AI/App/bat_det_net_data_params.d ./X-CUBE-AI/App/bat_det_net_data_params.o ./X-CUBE-AI/App/bat_det_net_data_params.su ./X-CUBE-AI/App/network.cyclo ./X-CUBE-AI/App/network.d ./X-CUBE-AI/App/network.o ./X-CUBE-AI/App/network.su ./X-CUBE-AI/App/network_data.cyclo ./X-CUBE-AI/App/network_data.d ./X-CUBE-AI/App/network_data.o ./X-CUBE-AI/App/network_data.su ./X-CUBE-AI/App/network_data_params.cyclo ./X-CUBE-AI/App/network_data_params.d ./X-CUBE-AI/App/network_data_params.o ./X-CUBE-AI/App/network_data_params.su

.PHONY: clean-X-2d-CUBE-2d-AI-2f-App

