################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/matching/kalmanfilter.cpp \
../src/matching/linear_assignment.cpp \
../src/matching/nn_matching.cpp \
../src/matching/track.cpp \
../src/matching/tracker.cpp 

OBJS += \
./src/matching/kalmanfilter.o \
./src/matching/linear_assignment.o \
./src/matching/nn_matching.o \
./src/matching/track.o \
./src/matching/tracker.o 

CPP_DEPS += \
./src/matching/kalmanfilter.d \
./src/matching/linear_assignment.d \
./src/matching/nn_matching.d \
./src/matching/track.d \
./src/matching/tracker.d 


# Each subdirectory must supply rules for building sources it contributes
src/matching/%.o: ../src/matching/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -DGPU -DCUDNN -DOPENCV -I/usr/local/opencv3/include/opencv2 -I/usr/local/opencv3/include/opencv -I/usr/local/opencv3/include -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive/Eigen -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/nsync/public -I/home/zy/Downloads/tensorflow-1.4.0/bazel-genfiles -I/home/zy/Downloads/tensorflow-1.4.0 -G -g -O0 -std=c++11 -gencode arch=compute_61,code=sm_61  -odir "src/matching" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -DGPU -DCUDNN -DOPENCV -I/usr/local/opencv3/include/opencv2 -I/usr/local/opencv3/include/opencv -I/usr/local/opencv3/include -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive/Eigen -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/nsync/public -I/home/zy/Downloads/tensorflow-1.4.0/bazel-genfiles -I/home/zy/Downloads/tensorflow-1.4.0 -G -g -O0 -std=c++11 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


