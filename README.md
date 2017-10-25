# ORB_SLAM_WITH_WEBCAM

Environment  setup refer to [raulmur](https://github.com/raulmur)/**ORB_SLAM2**

the `Vocabulary/` folder needed you can get from repository [raulmur](https://github.com/raulmur)/**ORB_SLAM2** and put it in the project's root folder.

This package use a web monocular.

Change the value of  `CamURL`   to your own in the main function.

## Build

```
mkdir build
cd build
cmake ..
make
```

## Run

`./start.sh`