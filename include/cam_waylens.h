#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp> 

using namespace std;
class WaylensCam{
private:
    bool imageSizeInited;
    cv::Size newSize;
    cv::VideoCapture vcap;
public:
    WaylensCam();
    ~WaylensCam();
    bool OpenCam(string videoSreamAddress);
    bool LoadCamImage(cv::Mat & image);
};