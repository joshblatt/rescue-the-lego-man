################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EUCAL/SERVO/SERVO.c \
../EUCAL/SERVO/SERVO_cfg.c 

OBJS += \
./EUCAL/SERVO/SERVO.o \
./EUCAL/SERVO/SERVO_cfg.o 

C_DEPS += \
./EUCAL/SERVO/SERVO.d \
./EUCAL/SERVO/SERVO_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
EUCAL/SERVO/%.o: ../EUCAL/SERVO/%.c EUCAL/SERVO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

