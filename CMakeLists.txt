cmake_minimum_required(VERSION 3.5)
project(BeagleBoneBlack_I2C)

if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

set(ADXL_SRC_FILES
        ADXL345.cpp
        ADXL345.h
        BBB_I2C.cpp
        BBB_I2C.h
        TestADXL345.cpp)

set(MPU6050_SRC_FILES
        BBB_I2C.cpp
        BBB_I2C.h
        MPU6050.cpp
        MPU6050.h
        TestMpu6050.cpp)

set(HMC5883L_SRC_FILES
        BBB_I2C.cpp
        BBB_I2C.h
        HMC5883L.cpp
        HMC5883L.h
        TestHMC5883L.cpp)

set(ALL_DEV_SRC_FILES
        BBB_I2C.cpp
        BBB_I2C.h
        ADXL345.cpp
        ADXL345.h
        HMC5883L.cpp
        HMC5883L.h
        MPU6050.cpp
        MPU6050.h
        AllDevices.cpp)

add_executable(ADXL345 ${ADXL_SRC_FILES})
add_executable(MPU6050 ${MPU6050_SRC_FILES})
add_executable(HMC5883L ${HMC5883L_SRC_FILES})
add_executable(AllDevices ${ALL_DEV_SRC_FILES})
