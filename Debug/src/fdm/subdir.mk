################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fdm/timeStep.c 

OBJS += \
./src/fdm/timeStep.o 

C_DEPS += \
./src/fdm/timeStep.d 


# Each subdirectory must supply rules for building sources it contributes
src/fdm/%.o: ../src/fdm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -g3 -Wall -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


