################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../net-connection/NetConnection.cpp 

O_SRCS += \
../net-connection/NetConnection.o 

OBJS += \
./net-connection/NetConnection.o 

CPP_DEPS += \
./net-connection/NetConnection.d 


# Each subdirectory must supply rules for building sources it contributes
net-connection/%.o: ../net-connection/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


