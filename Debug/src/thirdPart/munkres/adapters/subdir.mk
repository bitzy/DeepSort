################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/thirdPart/munkres/adapters/adapter.cpp \
../src/thirdPart/munkres/adapters/boostmatrixadapter.cpp 

OBJS += \
./src/thirdPart/munkres/adapters/adapter.o \
./src/thirdPart/munkres/adapters/boostmatrixadapter.o 

CPP_DEPS += \
./src/thirdPart/munkres/adapters/adapter.d \
./src/thirdPart/munkres/adapters/boostmatrixadapter.d 


# Each subdirectory must supply rules for building sources it contributes
src/thirdPart/munkres/adapters/%.o: ../src/thirdPart/munkres/adapters/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -DGPU -DCUDNN -DOPENCV -I/usr/local/opencv3/include/opencv2 -I/usr/local/opencv3/include/opencv -I/usr/local/opencv3/include -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive/Eigen -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/nsync/public -I/home/zy/Downloads/tensorflow-1.4.0/bazel-genfiles -I/home/zy/Downloads/tensorflow-1.4.0 -G -g -O0 -std=c++11 -gencode arch=compute_61,code=sm_61  -odir "src/thirdPart/munkres/adapters" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -DGPU -DCUDNN -DOPENCV -I/usr/local/opencv3/include/opencv2 -I/usr/local/opencv3/include/opencv -I/usr/local/opencv3/include -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive/Eigen -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/nsync/public -I/home/zy/Downloads/tensorflow-1.4.0/bazel-genfiles -I/home/zy/Downloads/tensorflow-1.4.0 -G -g -O0 -std=c++11 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


