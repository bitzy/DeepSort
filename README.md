# DeepSort
The c++ version of https://github.com/nwojke/deep_sort. 

# dependency
- opencv3
- tensorflow 1.4
- cuda 8.0
- cudnn 6.0

develop tool: Nsight Eclipse Edition Version:9.1

# PREPARE DATA & RUN
Defore you run, you need:
1. download YOLOV2's related model files https://pjreddie.com. Copy the **cfg**, **data** directory and **yolo.weights** to the  **RUNNINGDATA/darknet_data**.
2. download the CNN checkpoint file **resources/networks/mars-small128.ckpt-68577** and put to **RUNNINGDATA/tensor_networks**.
```
cd Debug
make
cd .. #into the project root directory
./Debug/VideoTracking
```

## OPTION in main.cpp
There are there options in main.cpp which you cann't define simutanously.
They are `RUNGT` `RUNMOTTENSOR` and `RUNLOCALVIDEO`.
- `RUNGT`: you need download MOT dataset and define the specific directory by `MOTDIR` in the main.cpp. FUNCTION: tracking mot dataset using mot groundtruth.
- `RUNMOTTENSOR`: like `RUNGT`. FUNCTION: tracking mot dataset using mot detection groundtruth but generate feature by tensorflow.
- `RUNLOCALVIDEO`: you need define the local video's path by `VIDEO` in the main.cpp. FUNCTION: tracking local video without any known data.
 

