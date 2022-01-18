/**
 * @file /include/qt_test/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qt_test_QNODE_HPP_
#define qt_test_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QImage>
#include <QThread>
#include <QStringListModel>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <QMetaType>
#include "current_tf_listener.hpp"
#include "handeye_target_widget.hpp"
#include "single_handeye_calibration_target/include/moveit/handeye_calibration_target/handeye_target_base.h"
#include "tf2_ros/transform_broadcaster.h"
#include "pluginlib/class_loader.hpp"
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_test {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
    QNode(int argc, char** argv );
    virtual ~QNode();
    bool init();
    bool init(const std::string &master_url, const std::string &host_url);
    void run();
    void sub_image(QString topic_name);
    /*********************
    ** Logging
    **********************/
    enum LogLevel {
        Debug,
        Info,
        Warn,
        Error,
        Fatal
    };

    QStringListModel* loggingModel() { return &logging_model; }
    void log( const LogLevel &level, const std::string &msg);
    void GetTopicsAndFrames(std::map<std::string,CameraTopics> &ros_topics,
                            std::map<std::string, TFFrameName> &frames_group)
    {
        ros_topics=this->ros_topics;
        frames_group=this->frames_group;
    }
Q_SIGNALS:
    void loggingUpdated();
    void rosShutdown();
    void image_val(QImage);
private:
    int init_argc;
    char** init_argv;
    ros::Publisher chatter_publisher;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;
    QStringListModel logging_model;
    image_transport::Subscriber image_sub;
    tf2_ros::TransformBroadcaster tf_pub_;
    void image_callback(const sensor_msgs::ImageConstPtr &msg);
    void image_topic_callback();
    bool SubTopicsAndFrames();
    QImage Mat2Qimage(const cv::Mat &src);
    // all sensor topics
    std::map<std::string,CameraTopics> ros_topics;
    // all frames
    std::map<std::string, TFFrameName> frames_group;
    //opticial_frame
    std::string optical_frame_;
    //hand eye calibration
    std::unique_ptr<pluginlib::ClassLoader<moveit_handeye_calibration::HandEyeTargetBase>> target_plugins_loader_;
    pluginlib::UniquePtr<moveit_handeye_calibration::HandEyeTargetBase> target_;
    std::vector<moveit_handeye_calibration::HandEyeTargetBase::Parameter> target_plugin_params_;
    void createTargetInstance();
    void loadAvaiableTargetPlugins();
};

}  // namespace qt_test

#endif /* qt_test_QNODE_HPP_ */
