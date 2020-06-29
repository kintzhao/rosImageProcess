/*
 * image_listener.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: darrenl
 */
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream>

static const std::string TOPIC_NAME = "/rs/rgb0/image";
static const std::string DEPTH_TOPIC_NAME = "camera/depth/image_raw";

std::string save_path = "/tmp/";
std::string image_name = "image0_";

    int isColor = 1;
    int fps = 30;
    int frameWidth = 1280;
    int frameHeight = 720;
    cv::VideoWriter  video_writer("/tmp/rs_video.avi", cv::VideoWriter::fourcc('M','J','P','G'), fps, cv::Size(frameWidth, frameHeight), isColor);
 


std::string int2str(int i)
{
    std::string numberstr;
	std::stringstream ss;

	ss<<i;
	ss>>numberstr;
    return numberstr;
}


void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    try {
        static int index = 0;
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        //std::string img_path = save_path+image_name+int2str(index++)+".png";

        //cv::imwrite(img_path, cv_ptr->image);
        //cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
        //cv::waitKey(5);
        video_writer.write(cv_ptr->image);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.",
                msg->encoding.c_str());
    }
}

void imageDepthCallback(const sensor_msgs::ImageConstPtr& msg) {
    try {
        // Save image
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "16UC1");
        cv::Mat mat = cv_ptr->image;
        cv::Mat beConvertedMat(mat.rows, mat.cols, CV_8UC4, mat.data); // provide different view of m1 data
        cv::imwrite("rgbd.bmp", beConvertedMat);
        // Show image
        cv::imshow("depthview", cv_bridge::toCvShare(msg, "16UC1")->image);
        cv::waitKey(30);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert from '%s' to '16UC1'.",
                msg->encoding.c_str());
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "image_transport_subscriber");
    ros::NodeHandle nh;
    cv::namedWindow("view");
    //cv::namedWindow("depthview");
    cv::startWindowThread();
    image_transport::ImageTransport it(nh);
    std::string topic_name;
    nh.param("/topic_name", topic_name, std::string("/rs/rgb0/image"));

    image_transport::Subscriber sub = it.subscribe(topic_name, 1, imageCallback);
    //image_transport::Subscriber sub_depth = it.subscribe(DEPTH_TOPIC_NAME, 1, imageDepthCallback);
    ros::spin();
    cv::destroyWindow("view");
    //cv::destroyWindow("depthview");
    ros::shutdown();
    return 0;
}
