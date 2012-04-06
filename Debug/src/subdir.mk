################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/auxFunctions.c \
../src/matrix.c \
../src/timeStep.c 

OBJS += \
./src/auxFunctions.o \
./src/matrix.o \
./src/timeStep.o 

C_DEPS += \
./src/auxFunctions.d \
./src/matrix.d \
./src/timeStep.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -g3 -Wall -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


