################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/drawSolidPoly.cpp \
../src/fileStore.cpp \
../src/test_triangle.cpp \
../src/videoio.cpp 

OBJS += \
./src/drawSolidPoly.o \
./src/fileStore.o \
./src/test_triangle.o \
./src/videoio.o 

CPP_DEPS += \
./src/drawSolidPoly.d \
./src/fileStore.d \
./src/test_triangle.d \
./src/videoio.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -I/usr/include/opencv -I/usr/include/opencv2 -I../inc -O3 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_53,code=sm_53  -odir "src" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -I/usr/include/opencv -I/usr/include/opencv2 -I../inc -O3 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


