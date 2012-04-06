################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../secondary_tests/dominantDiagonal.c 

OBJS += \
./secondary_tests/dominantDiagonal.o 

C_DEPS += \
./secondary_tests/dominantDiagonal.d 


# Each subdirectory must supply rules for building sources it contributes
secondary_tests/%.o: ../secondary_tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -g3 -Wall -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


