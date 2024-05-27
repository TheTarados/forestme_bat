################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32wle5ccux.s 

OBJS += \
./Core/Startup/startup_stm32wle5ccux.o 

S_DEPS += \
./Core/Startup/startup_stm32wle5ccux.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -DARM_DSP_CONFIG_TABLES -DARM_FFT_ALLOW_TABLES -DARM_TABLE_REALCOEF_Q15 -DRFFT_Q15_512 -DARM_TABLE_TWIDDLECOEF_Q15_256=1 -DARM_TABLE_BITREVIDX_FXT_256=1 -c -I"/home/base_usr/drive/ForestMEvBat/Embedded_sw/Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32wle5ccux.d ./Core/Startup/startup_stm32wle5ccux.o

.PHONY: clean-Core-2f-Startup

