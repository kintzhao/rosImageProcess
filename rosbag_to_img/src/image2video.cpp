
#include <ros/ros.h>                     ///< ros error
#include <rosbag/bag.h>                  ///< read from bagfile
#include <sensor_msgs/CompressedImage.h> ///< camera image type
#include <rosbag/view.h>

#include <boost/foreach.hpp>             ///< boost interation

#include <cv_bridge/cv_bridge.h>         ///< opencv bridge
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <sstream>

std::string int2str(int i)
{
    std::string numberstr;
	std::stringstream ss;

	ss<<i;
	ss>>numberstr;
    return numberstr;
}

#define foreach BOOST_FOREACH

int main(int argc, char **argv)
{
    if(argc < 5)
    {
        std::cout<<"please check the param: run  topic_name  baf_dir  bag_name  outdir outname ";
    }

    std::cout<<"Run:";
    for(int i=0; i< argc; i++)
    {
        std::cout<<" "<<argv[i];
    }
    std::cout<<std::endl;
    std::cout<<"please check the path:   bag_path: "<< std::string(argv[2]) + std::string(argv[3])<<std::endl;
    std::cout<<"please check the path:   out_path: "<< std::string(argv[2]) + std::string(argv[4])+"/"+std::string(argv[5])<<std::endl;

    std::string bag_path = std::string(argv[2])+ std::string(argv[3]);
    std::string image_output_dir = std::string(argv[2])+ std::string(argv[4]);
    std::string current_image_path =  image_output_dir +"/"+ std::string(argv[5]);
    std::string video_path =  image_output_dir +"/"+ std::string(argv[3])+".avi";

    //std::string OPENCV_WINDOW = "Image window";
    ///< load bag file
    rosbag::Bag bag;
    bag.open(bag_path, rosbag::bagmode::Read);

    cv::namedWindow(OPENCV_WINDOW, 0);

    ///< topic setup
    std::vector<std::string> topics;
    topics.push_back(std::string(argv[1]));//"/camera/color/image_raw"

    rosbag::View view(bag, rosbag::TopicQuery(topics));
  
    int isColor = 1;
    int fps = 30;
    int frameWidth = 1280;
    int frameHeight = 720;
    cv::VideoWriter  video_writer(video_path, cv::VideoWriter::fourcc('M','J','P','G'), fps, cv::Size(frameWidth, frameHeight), isColor);
    std::cout<<"video frameWidth: "<<frameWidth<<" | frameHeight: "<<frameHeight<<std::endl;
    bool enable_fliped = true;
    int index = 0;
    ///< loop for fetching image topic
    foreach(rosbag::MessageInstance const m, view)
    {
        sensor_msgs::Image::ConstPtr img_ptr = m.instantiate<sensor_msgs::Image>();
        //sensor_msgs::CompressedImage::ConstPtr img_ptr = m.instantiate<sensor_msgs::CompressedImage>();
        if (img_ptr != NULL)
        {
            cv_bridge::CvImagePtr cv_ptr;
            try
            {
                cv_ptr = cv_bridge::toCvCopy(img_ptr, sensor_msgs::image_encodings::BGR8);
            }
            catch (cv_bridge::Exception& e)
            {
                ROS_ERROR("cv_bridge exception: %s", e.what());
            }
	    //std::cout<<"cols rows: "<<cv_ptr->image.cols <<" | "<<cv_ptr->image.rows <<std::endl;
            ///< display cv img
            //std::string current_index;
            //current_index<<index++; to_string(index);
            std::string image_name = current_image_path + int2str(index++)+".png";
            std::cout<<image_name<<std::endl;
 
	    if(enable_fliped)
	    {
	       cv::Mat map_flipped;
    	       cv::flip(cv_ptr->image, map_flipped, -1);
	       //std::cout<<"cols rows: "<<map_flipped.cols <<" | "<<map_flipped.rows <<std::endl;
               video_writer.write(map_flipped);
	    }
	    else
	    {
	        video_writer.write(cv_ptr->image);
            }
		
	    //if(index == 200)
		//break;
            //cv::imwrite( image_name, cv_ptr->image);
            //cv::imshow(OPENCV_WINDOW, cv_ptr->image);
            //cv::waitKey(3);
        }
    }

    ///< close rosbag file
    bag.close();
}
