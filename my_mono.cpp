/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 

#include<System.h>

using namespace std;

const string CamURL = "http://192.168.110.1:8085/";
const int fps = 30;

double getTimeStamps(int frameNum,int fps);
bool LoadCamImage(const string URL, cv::Mat & image);

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        cerr << endl << "Usage: ./mono_tum path_to_vocabulary path_to_settings path_to_sequence" << endl;
        return 1;
    }

    // Retrieve paths to images
    cv::Mat im;

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);

    // Vector for tracking time statistics
    // vector<float> vTimesTrack;
    // vTimesTrack.resize(nImages);

    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;
    // cout << "Images in the sequence: " << nImages << endl << endl;

    int frameNum = 1;

    // Main loop
    while(LoadCamImage(CamURL, im))
    {
        double tframe = getTimeStamps(frameNum,fps);
        double vTimestamps = getTimeStamps(frameNum+1,fps);
        // Read image from file
        // im = cv::imread(string(argv[3])+"/"+vstrImageFilenames[ni],CV_LOAD_IMAGE_UNCHANGED);
        // double tframe = vTimestamps[ni];

        // if(im.empty())
        // {
        //     cerr << endl << "Failed to load image at: "
        //          << string(argv[3]) << "/" << vstrImageFilenames[ni] << endl;
        //     return 1;
        // }


#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t1 = std::chrono::monotonic_clock::now();
#endif

        // Pass the image to the SLAM system
        SLAM.TrackMonocular(im,tframe);

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t2 = std::chrono::monotonic_clock::now();
#endif

        double ttrack= std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();

        // vTimesTrack[ni]=ttrack;

        // Wait to load the next frame
        double T=0;
        T = vTimestamps-tframe;

        if(ttrack<T)
            usleep((T-ttrack)*1e6);
    }

    // Stop all threads
    SLAM.Shutdown();

    // Tracking time statistics
    // sort(vTimesTrack.begin(),vTimesTrack.end());
    // float totaltime = 0;
    // for(int ni=0; ni<nImages; ni++)
    // {
    //     totaltime+=vTimesTrack[ni];
    // }
    // cout << "-------" << endl << endl;
    // cout << "median tracking time: " << vTimesTrack[nImages/2] << endl;
    // cout << "mean tracking time: " << totaltime/nImages << endl;

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

    return 0;
}

double getTimeStamps(int frameNum,int fps)
{
    double timeStamp = frameNum++*(1000/fps);
    return timeStamp;
}

bool LoadCamImage(const string URL, cv::Mat & image)
{
    cv::VideoCapture vcap;
    string videoSreamAddress = URL;
    if(!vcap.open(videoSreamAddress))
    {
        cout << "Error opening video stream" << endl;
        return false;
    }
    if(!vcap.read(image))
    {
        cout<<"No Frame"<<endl;
        return false;
    }
    return true;
}