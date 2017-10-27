# ORB_SLAM_WITH_WEBCAM

Environment  setup refer to [raulmur](https://github.com/raulmur)/**ORB_SLAM2**

the `Vocabulary/` folder needed you can get from repository [raulmur](https://github.com/raulmur)/**ORB_SLAM2** and put it in the project's root folder.

This package use a web monocular.

Change the value of  `CamURL`   to your own in the main function.

## Install Dependencies

1. install C++11 complier

   ```shell
   $ sudo apt-get install gcc g++ 
   ```

2. install Pangolin

   ```shell
   $ sudo apt-get install libglew-dev 
   $ sudo apt-get install cmake        
   $ sudo apt-get install libboost-dev libboost-thread-dev libboost-filesystem-dev  
   $ sudo apt-get install libpython2.7-dev 
   $ git clone https://github.com/stevenlovegrove/Pangolin.git  
   $ cd Pangolin  
   $ mkdir build  
   $ cd build  
   $ cmake -DCPP11_NO_BOOST=1 ..  
   $ make  
   $ sudo make install
   ```

3. install OpenCV

4. install Eigen3.1.0

   ```shell
   $ sudo apt-get install libeigen3-dev 
   ```

5. install BLAS and LAPCAK

   ```shell
   $ sudo apt-get install libblas-dev  
   $ sudo apt-get install liblapack-dev  
   ```


## Build

```shell
$ cd ORB_SLAM_WITH_WEBCAM2/
$ mkdir build
$ cd build/
$ cmake ..
$ make
```

## Run

```shell
$ cd ../
$ ./start.sh
```

