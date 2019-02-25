################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/portable/MemMang/heap_1.c 

C_DEPS += \
./Source/portable/MemMang/heap_1.d 

OBJS += \
./Source/portable/MemMang/heap_1.o 


# Each subdirectory must supply rules for building sources it contributes
Source/portable/MemMang/%.o: ../Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Program Files\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\eclipse-workspace\CG2271_Project\Source" -I"C:\eclipse-workspace\CG2271_Project" -I"C:\eclipse-workspace\CG2271_Project\Source\portable\MemMang" -I"C:\eclipse-workspace\CG2271_Project\Source\portable\GCC\ATMega323" -I"C:\eclipse-workspace\CG2271_Project\Source\include" -I"C:\Program Files\Arduino\hardware\arduino\avr\variants\standard" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


