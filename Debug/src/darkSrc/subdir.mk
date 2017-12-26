################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../src/darkSrc/activation_kernels.cu \
../src/darkSrc/avgpool_layer_kernels.cu \
../src/darkSrc/blas_kernels.cu \
../src/darkSrc/col2im_kernels.cu \
../src/darkSrc/convolutional_kernels.cu \
../src/darkSrc/crop_layer_kernels.cu \
../src/darkSrc/deconvolutional_kernels.cu \
../src/darkSrc/dropout_layer_kernels.cu \
../src/darkSrc/im2col_kernels.cu \
../src/darkSrc/maxpool_layer_kernels.cu \
../src/darkSrc/network_kernels.cu 

C_SRCS += \
../src/darkSrc/activation_layer.c \
../src/darkSrc/activations.c \
../src/darkSrc/avgpool_layer.c \
../src/darkSrc/batchnorm_layer.c \
../src/darkSrc/blas.c \
../src/darkSrc/box.c \
../src/darkSrc/col2im.c \
../src/darkSrc/connected_layer.c \
../src/darkSrc/convolutional_layer.c \
../src/darkSrc/cost_layer.c \
../src/darkSrc/crnn_layer.c \
../src/darkSrc/crop_layer.c \
../src/darkSrc/cuda.c \
../src/darkSrc/data.c \
../src/darkSrc/deconvolutional_layer.c \
../src/darkSrc/demo.c \
../src/darkSrc/detection_layer.c \
../src/darkSrc/dropout_layer.c \
../src/darkSrc/gemm.c \
../src/darkSrc/gettimeofday.c \
../src/darkSrc/gru_layer.c \
../src/darkSrc/im2col.c \
../src/darkSrc/image.c \
../src/darkSrc/layer.c \
../src/darkSrc/list.c \
../src/darkSrc/local_layer.c \
../src/darkSrc/matrix.c \
../src/darkSrc/maxpool_layer.c \
../src/darkSrc/network.c \
../src/darkSrc/normalization_layer.c \
../src/darkSrc/option_list.c \
../src/darkSrc/parser.c \
../src/darkSrc/region_layer.c \
../src/darkSrc/reorg_layer.c \
../src/darkSrc/rnn_layer.c \
../src/darkSrc/route_layer.c \
../src/darkSrc/shortcut_layer.c \
../src/darkSrc/softmax_layer.c \
../src/darkSrc/tree.c \
../src/darkSrc/utils.c 

OBJS += \
./src/darkSrc/activation_kernels.o \
./src/darkSrc/activation_layer.o \
./src/darkSrc/activations.o \
./src/darkSrc/avgpool_layer.o \
./src/darkSrc/avgpool_layer_kernels.o \
./src/darkSrc/batchnorm_layer.o \
./src/darkSrc/blas.o \
./src/darkSrc/blas_kernels.o \
./src/darkSrc/box.o \
./src/darkSrc/col2im.o \
./src/darkSrc/col2im_kernels.o \
./src/darkSrc/connected_layer.o \
./src/darkSrc/convolutional_kernels.o \
./src/darkSrc/convolutional_layer.o \
./src/darkSrc/cost_layer.o \
./src/darkSrc/crnn_layer.o \
./src/darkSrc/crop_layer.o \
./src/darkSrc/crop_layer_kernels.o \
./src/darkSrc/cuda.o \
./src/darkSrc/data.o \
./src/darkSrc/deconvolutional_kernels.o \
./src/darkSrc/deconvolutional_layer.o \
./src/darkSrc/demo.o \
./src/darkSrc/detection_layer.o \
./src/darkSrc/dropout_layer.o \
./src/darkSrc/dropout_layer_kernels.o \
./src/darkSrc/gemm.o \
./src/darkSrc/gettimeofday.o \
./src/darkSrc/gru_layer.o \
./src/darkSrc/im2col.o \
./src/darkSrc/im2col_kernels.o \
./src/darkSrc/image.o \
./src/darkSrc/layer.o \
./src/darkSrc/list.o \
./src/darkSrc/local_layer.o \
./src/darkSrc/matrix.o \
./src/darkSrc/maxpool_layer.o \
./src/darkSrc/maxpool_layer_kernels.o \
./src/darkSrc/network.o \
./src/darkSrc/network_kernels.o \
./src/darkSrc/normalization_layer.o \
./src/darkSrc/option_list.o \
./src/darkSrc/parser.o \
./src/darkSrc/region_layer.o \
./src/darkSrc/reorg_layer.o \
./src/darkSrc/rnn_layer.o \
./src/darkSrc/route_layer.o \
./src/darkSrc/shortcut_layer.o \
./src/darkSrc/softmax_layer.o \
./src/darkSrc/tree.o \
./src/darkSrc/utils.o 

CU_DEPS += \
./src/darkSrc/activation_kernels.d \
./src/darkSrc/avgpool_layer_kernels.d \
./src/darkSrc/blas_kernels.d \
./src/darkSrc/col2im_kernels.d \
./src/darkSrc/convolutional_kernels.d \
./src/darkSrc/crop_layer_kernels.d \
./src/darkSrc/deconvolutional_kernels.d \
./src/darkSrc/dropout_layer_kernels.d \
./src/darkSrc/im2col_kernels.d \
./src/darkSrc/maxpool_layer_kernels.d \
./src/darkSrc/network_kernels.d 

C_DEPS += \
./src/darkSrc/activation_layer.d \
./src/darkSrc/activations.d \
./src/darkSrc/avgpool_layer.d \
./src/darkSrc/batchnorm_layer.d \
./src/darkSrc/blas.d \
./src/darkSrc/box.d \
./src/darkSrc/col2im.d \
./src/darkSrc/connected_layer.d \
./src/darkSrc/convolutional_layer.d \
./src/darkSrc/cost_layer.d \
./src/darkSrc/crnn_layer.d \
./src/darkSrc/crop_layer.d \
./src/darkSrc/cuda.d \
./src/darkSrc/data.d \
./src/darkSrc/deconvolutional_layer.d \
./src/darkSrc/demo.d \
./src/darkSrc/detection_layer.d \
./src/darkSrc/dropout_layer.d \
./src/darkSrc/gemm.d \
./src/darkSrc/gettimeofday.d \
./src/darkSrc/gru_layer.d \
./src/darkSrc/im2col.d \
./src/darkSrc/image.d \
./src/darkSrc/layer.d \
./src/darkSrc/list.d \
./src/darkSrc/local_layer.d \
./src/darkSrc/matrix.d \
./src/darkSrc/maxpool_layer.d \
./src/darkSrc/network.d \
./src/darkSrc/normalization_layer.d \
./src/darkSrc/option_list.d \
./src/darkSrc/parser.d \
./src/darkSrc/region_layer.d \
./src/darkSrc/reorg_layer.d \
./src/darkSrc/rnn_layer.d \
./src/darkSrc/route_layer.d \
./src/darkSrc/shortcut_layer.d \
./src/darkSrc/softmax_layer.d \
./src/darkSrc/tree.d \
./src/darkSrc/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/darkSrc/%.o: ../src/darkSrc/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -DGPU -DCUDNN -DOPENCV -I/usr/local/opencv3/include/opencv2 -I/usr/local/opencv3/include/opencv -I/usr/local/opencv3/include -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive/Eigen -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/nsync/public -I/home/zy/Downloads/tensorflow-1.4.0/bazel-genfiles -I/home/zy/Downloads/tensorflow-1.4.0 -G -g -O0 -std=c++11 -gencode arch=compute_61,code=sm_61  -odir "src/darkSrc" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -DGPU -DCUDNN -DOPENCV -I/usr/local/opencv3/include/opencv2 -I/usr/local/opencv3/include/opencv -I/usr/local/opencv3/include -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive/Eigen -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/nsync/public -I/home/zy/Downloads/tensorflow-1.4.0/bazel-genfiles -I/home/zy/Downloads/tensorflow-1.4.0 -G -g -O0 -std=c++11 --compile --relocatable-device-code=false -gencode arch=compute_61,code=compute_61 -gencode arch=compute_61,code=sm_61  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/darkSrc/%.o: ../src/darkSrc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -DGPU -DCUDNN -DOPENCV -I/usr/local/opencv3/include/opencv2 -I/usr/local/opencv3/include/opencv -I/usr/local/opencv3/include -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive/Eigen -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/nsync/public -I/home/zy/Downloads/tensorflow-1.4.0/bazel-genfiles -I/home/zy/Downloads/tensorflow-1.4.0 -G -g -O0 -std=c++11 -gencode arch=compute_61,code=sm_61  -odir "src/darkSrc" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -DGPU -DCUDNN -DOPENCV -I/usr/local/opencv3/include/opencv2 -I/usr/local/opencv3/include/opencv -I/usr/local/opencv3/include -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive/Eigen -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/eigen_archive -I/home/zy/.cache/bazel/_bazel_zy/69673882bdf22f44b89ee446a9525e4a/external/nsync/public -I/home/zy/Downloads/tensorflow-1.4.0/bazel-genfiles -I/home/zy/Downloads/tensorflow-1.4.0 -G -g -O0 -std=c++11 --compile  -x c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


