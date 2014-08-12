################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ADXL345.cpp \
../BBB_I2C.cpp \
../HMC5883L.cpp \
../MPU6050.cpp \
../TestMPU6050.cpp 

OBJS += \
./ADXL345.o \
./BBB_I2C.o \
./HMC5883L.o \
./MPU6050.o \
./TestMPU6050.o 

CPP_DEPS += \
./ADXL345.d \
./BBB_I2C.d \
./HMC5883L.d \
./MPU6050.d \
./TestMPU6050.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/arm/arm-none-linux-gnueabi -I/usr/local/arm/arm-none-linux-gnueabi/arm-none-linux-gnueabi/sysroot/usr/include -I/usr/local/arm/arm-none-linux-gnueabi/arm-none-linux-gnueabi/sysroot/usr/lib -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


