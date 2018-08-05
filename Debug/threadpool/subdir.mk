################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../threadpool/ThreadPool.cpp 

OBJS += \
./threadpool/ThreadPool.o 

CPP_DEPS += \
./threadpool/ThreadPool.d 


# Each subdirectory must supply rules for building sources it contributes
threadpool/%.o: ../threadpool/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


