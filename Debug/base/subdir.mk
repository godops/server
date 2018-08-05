################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../base/IoReader.cpp \
../base/IoWriter.cpp 

OBJS += \
./base/IoReader.o \
./base/IoWriter.o 

CPP_DEPS += \
./base/IoReader.d \
./base/IoWriter.d 


# Each subdirectory must supply rules for building sources it contributes
base/%.o: ../base/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


