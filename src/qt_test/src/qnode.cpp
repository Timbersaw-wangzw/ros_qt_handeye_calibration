/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/qt_test/qnode.hpp"
#include "../include/qt_test/handeye_target_widget.hpp"
#include "../include/qt_test/current_tf_listener.hpp"
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_test {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
    init_argc(argc),
    init_argv(argv),
    target_plugins_loader_(nullptr),
    target_(nullptr)
    //target_param_layout_(new QFormLayout())
{

}

QNode::~QNode() {
    if(ros::isStarted()) {
        ros::shutdown(); // explicitly needed since we use ros::start();
        ros::waitForShutdown();
    }
    wait();
}

bool QNode::init() {
    ros::init(init_argc,init_argv,"qt_test");
    if ( ! ros::master::check() ) {
        return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    // Add your ros communications here.
    chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);

    image_transport::ImageTransport it_(n);
    image_pub_ = it_.advertise("/single_handeye_calibration/target_detection", 1);
    start();
    SubTopicsAndFrames();
    loadAvaiableTargetPlugins();

    return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
    std::map<std::string,std::string> remappings;
    remappings["__master"] = master_url;
    remappings["__hostname"] = host_url;
    ros::init(remappings,"qt_test");
    if ( ! ros::master::check() ) {
        return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    // Add your ros communications here.
    chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    start();
    SubTopicsAndFrames();
    loadAvaiableTargetPlugins();
    return true;
}

void QNode::run() {
    ros::Rate loop_rate(1);
    bool flag=true;
    while ( ros::ok() )
    {
        if (flag)
        {
            std_msgs::String msg;
            std::stringstream ss;
            ss << "connected !";
            msg.data = ss.str();
            chatter_publisher.publish(msg);
            log(Info,std::string("I sent: ")+msg.data);
        }
        flag=false;
        ros::spinOnce();
        loop_rate.sleep();
    }
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void QNode::sub_image(QString topic_name)
{
    ros::NodeHandle n;
    image_transport::ImageTransport it_(n);
    image_sub_=it_.subscribe(topic_name.toStdString(),1000,&QNode::image_callback,this);
}
void QNode::image_callback(const sensor_msgs::ImageConstPtr &msg)
{
    std::string frame_id = msg->header.frame_id;
    if (!frame_id.empty())
    {
        if (optical_frame_.compare(frame_id))
        {
            optical_frame_ = frame_id;
        }
    }
    if (msg->data.empty())
    {
        ROS_WARN_STREAM("Image msg has empty data.");
        //calibration_display_->setStatus(rviz::StatusProperty::Error, "Target detection", "Image message is empty.");
        return;
    }
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr=cv_bridge::toCvCopy(msg,msg->encoding);
        QImage im=Mat2Qimage(cv_ptr->image);
        sensor_msgs::ImagePtr pub_msg;
        if (target_ && target_->detectTargetPose(cv_ptr->image))
        {
            pub_msg = cv_bridge::CvImage(std_msgs::Header(), "rgb8", cv_ptr->image).toImageMsg();

            geometry_msgs::TransformStamped tf2_msg = target_->getTransformStamped(optical_frame_);
            tf_pub_.sendTransform(tf2_msg);
            if (!target_->areIntrinsicsReasonable())
            {

            }
        }
        else
        {
            pub_msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", cv_ptr->image).toImageMsg();
            //calibration_display_->setStatus(rviz::StatusProperty::Error, "Target detection", "Target detection failed.");
        }
        image_pub_.publish(pub_msg);
        emit image_val(im);
    }
    catch (cv_bridge::Exception& e)
    {
        std::string error_message = "cv_bridge exception: " + std::string(e.what());
        //calibration_display_->setStatusStd(rviz::StatusProperty::Error, "Target detection", error_message);
        ROS_WARN_STREAM(error_message.c_str());
    }
}

bool QNode::SubTopicsAndFrames()
{
    // Get All Camera Topics
    CameraTopics image_topic("sensor_msgs/Image");
    image_topic.getFilteredTopics();
    ros_topics.insert(std::make_pair("image_topic",image_topic));
    CameraTopics camer_info("sensor_msgs/CameraInfo");
    camer_info.getFilteredTopics();
    ros_topics.insert(std::make_pair("camera_info_topic",camer_info));

    TFFrameName camera_frame(CAMERA_FRAME);
    camera_frame.getFilterFrameNames();
    frames_group.insert(std::make_pair("sensor", camera_frame));

    TFFrameName object_frame(ENVIRONMENT_FRAME);
    object_frame.getFilterFrameNames();
    frames_group.insert(std::make_pair("object", object_frame));

    TFFrameName eef_frame(ROBOT_FRAME);
    eef_frame.getFilterFrameNames();
    frames_group.insert(std::make_pair("eef", eef_frame));

    TFFrameName base_frame(ROBOT_FRAME);
    base_frame.getFilterFrameNames();
    frames_group.insert(std::make_pair("base", base_frame));


}
QImage QNode::Mat2Qimage(const cv::Mat &src)
{
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);

    const float scale = 255.0;

    if (src.depth() == CV_8U) {
        if (src.channels() == 1) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    int level = src.at<quint8>(i, j);
                    dest.setPixel(j, i, qRgb(level, level, level));
                }
            }
        } else if (src.channels() == 3) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    cv::Vec3b bgr = src.at<cv::Vec3b>(i, j);
                    dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
                }
            }
        }
    } else if (src.depth() == CV_32F) {
        if (src.channels() == 1) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    int level = scale * src.at<float>(i, j);
                    dest.setPixel(j, i, qRgb(level, level, level));
                }
            }
        } else if (src.channels() == 3) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    cv::Vec3f bgr = scale * src.at<cv::Vec3f>(i, j);
                    dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
                }
            }
        }
    }

    return dest;

}

void QNode::createTargetInstance()
{

}

void QNode::loadAvaiableTargetPlugins()
{
    if (!target_plugins_loader_)
     {
        target_plugins_loader_.reset(new pluginlib::ClassLoader<moveit_handeye_calibration::HandEyeTargetBase>(
            "moveit_calibration_plugins", "moveit_handeye_calibration::HandEyeTargetBase"));
     }
}
void QNode::log( const LogLevel &level, const std::string &msg) {
    logging_model.insertRows(logging_model.rowCount(),1);
    std::stringstream logging_model_msg;
    switch ( level ) {
    case(Debug) : {
        ROS_DEBUG_STREAM(msg);
        logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Info) : {
        ROS_INFO_STREAM(msg);
        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Warn) : {
        ROS_WARN_STREAM(msg);
        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Error) : {
        ROS_ERROR_STREAM(msg);
        logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Fatal) : {
        ROS_FATAL_STREAM(msg);
        logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    }
    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
    Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

}  // namespace qt_test
