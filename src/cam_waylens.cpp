#include<cam_waylens.h>
#include<opencv2/imgproc/imgproc.hpp>

WaylensCam::WaylensCam()
    :imageSizeInited(false)
{

}
WaylensCam::~WaylensCam()
{
    vcap.release();
}

bool WaylensCam::OpenCam(string videoSreamAddress)
{
    if(!vcap.open(videoSreamAddress))
    {
        cout << "Error opening video stream" << endl;
        return false;
    }
    return true;
}

bool WaylensCam::LoadCamImage(cv::Mat & outputImage)
{
    cv::Mat imageTemp;
    if(!vcap.read(imageTemp))
    {
        cout<<"No Frame"<<endl;
        return false;
    }
    if(!imageSizeInited)
    {
        newSize.width = 640;
        newSize.height = imageTemp.rows*640/imageTemp.cols;
        imageSizeInited = true;
    }
    cv::resize(imageTemp,outputImage,newSize,0,0,cv::INTER_AREA);
    imageTemp.release();
    return true;
}