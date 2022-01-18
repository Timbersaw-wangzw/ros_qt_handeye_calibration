#ifndef HANDEYE_TARGET_WIDGET_H
#define HANDEYE_TARGET_WIDGET_H
// qt
#include <QListView>
#include <QComboBox>
#include <QString>
#include <QSet>
// ros
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/JointState.h>
#include <rviz/message_filter_display.h>

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <rviz/frame_manager.h>
#include <QMouseEvent>
#include "current_tf_listener.hpp"
class RosTopicComboBox: public QComboBox
{
    Q_OBJECT
public:
    RosTopicComboBox(QWidget * parent = nullptr){}
    ~RosTopicComboBox() = default;

    void addMsgsFilterType(QString msgs_type);

    bool hasTopic(const QString& topic_name);

    bool getFilteredTopics();
signals:
    void clicked();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
    QSet<QString> message_types_;
    QSet<QString> image_topics_;

};



enum FRAME_SOURCE
{
    ROBOT_FRAME = 0,
    CAMERA_FRAME = 1,
    ENVIRONMENT_FRAME = 2
};
class TFFrameNameComboBox:public QComboBox
{
    Q_OBJECT
public:
    TFFrameNameComboBox(QWidget * parent = nullptr){}
    void setSource(FRAME_SOURCE source =ROBOT_FRAME){this->frame_source_=source;}
    bool hasFrame(const std::string& frame_name);
    void getFilterFrameNames();
    ~TFFrameNameComboBox()=default;
signals:
    void clicked();
private:
    virtual void mousePressEvent(QMouseEvent* event);
    FRAME_SOURCE frame_source_;
    QSet<QString> frame_names_lists;
};

class TFFrameName
{
public:
    TFFrameName(FRAME_SOURCE source = ROBOT_FRAME)
    {
        robot_model_loader_.reset(new robot_model_loader::RobotModelLoader("robot_description"));
        frame_manager_.reset(new rviz::FrameManager());
        current_tf_listener.reset(new tf_listener::TfListener());
        frame_source_ = source;

    }
    ~TFFrameName()
    {
        robot_model_loader_.reset();
        frame_manager_.reset();
    }
    bool hasFrame(const std::string& frame_name);
    bool getFilterFrameNames();
    void getFrameNames(QSet<QString>& frame_names_lists){frame_names_lists=this->frame_names_lists;}
protected:
    FRAME_SOURCE frame_source_;
    std::shared_ptr<rviz::FrameManager> frame_manager_;
    robot_model_loader::RobotModelLoaderConstPtr robot_model_loader_;
    std::shared_ptr<tf_listener::TfListener> current_tf_listener;
    QSet<QString> frame_names_lists;
};
class CameraTopics
{
public:
    CameraTopics(QString msgs_type)
    {
        this->message_types_.insert(msgs_type);
    }
    ~CameraTopics(){}
    void GetRosTopic(QSet<QString>& image_topics_){ image_topics_=this->image_topics_;}
    void addMsgsFilterType(QString msgs_type);
    bool hasTopic(const QString& topic_name);
    bool getFilteredTopics();
protected:
    QSet<QString> message_types_;
    QSet<QString> image_topics_;
};
#endif // HANDEYE_TARGET_WIDGET_H
