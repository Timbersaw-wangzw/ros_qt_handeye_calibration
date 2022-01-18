#include "../include/qt_test/handeye_target_widget.hpp"

void CameraTopics::addMsgsFilterType(QString msgs_type)
{
    message_types_.insert(msgs_type);
}

bool CameraTopics::hasTopic(const QString &topic_name)
{
    getFilteredTopics();
    return image_topics_.contains(topic_name);
}

bool CameraTopics::getFilteredTopics()
{
    if (ros::ok() )
    {
        ros::master::V_TopicInfo ros_topic_vec;
        if (ros::master::getTopics(ros_topic_vec))
        {
            image_topics_.clear();
            // Filter out the topic names with specific topic type
            for (const ros::master::TopicInfo& topic_info : ros_topic_vec)
            {
                if (message_types_.contains(QString(topic_info.datatype.c_str())))
                {
                    image_topics_.insert(QString(topic_info.name.c_str()));
                }
            }
        }
    }

}


bool TFFrameName::hasFrame(const std::string &frame_name)
{
    std::vector<std::string> names;
    frame_manager_->update();
    frame_manager_->getTF2BufferPtr()->_getFrameStrings(names);

    auto it = std::find(names.begin(), names.end(), frame_name);
    return it != names.end();
}

bool TFFrameName::getFilterFrameNames()
{
    std::vector<std::string> frame_names;
    current_tf_listener->getFramesList(frame_names);
    if(robot_model_loader_->getModel())
    {
        const std::vector<std::string>& robot_links = robot_model_loader_->getModel()->getLinkModelNames();
        for (const std::string&name: robot_links)
        {
            auto it = std::find(robot_links.begin(), robot_links.end(), name);
            size_t index = name.find("camera");
            if (frame_source_ == ROBOT_FRAME)
                if (it != robot_links.end())
                    frame_names_lists.insert(QString(name.c_str()));
            if (frame_source_ == CAMERA_FRAME)
                frame_names_lists.insert(QString(name.c_str()));
            if (frame_source_ == ENVIRONMENT_FRAME)
                if (it == robot_links.end() && index == std::string::npos)
                    frame_names_lists.insert(QString(name.c_str()));
        }

    }
}

void RosTopicComboBox::addMsgsFilterType(QString msgs_type)
{
    message_types_.insert(msgs_type);
}

bool RosTopicComboBox::hasTopic(const QString &topic_name)
{
    getFilteredTopics();
    return image_topics_.contains(topic_name);
}

bool RosTopicComboBox::getFilteredTopics()
{
    if (ros::ok() )
    {
        ros::master::V_TopicInfo ros_topic_vec;
        if (ros::master::getTopics(ros_topic_vec))
        {
            image_topics_.clear();
            // Filter out the topic names with specific topic type
            for (const ros::master::TopicInfo& topic_info : ros_topic_vec)
            {
                if (message_types_.contains(QString(topic_info.datatype.c_str())))
                {
                    image_topics_.insert(QString(topic_info.name.c_str()));
                }
            }
        }
    }
    clear();
    for (const QString& topic : image_topics_)
    {
      addItem(topic);
    }
}

void RosTopicComboBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        getFilteredTopics();
        showPopup();
        emit clicked();  //触发clicked信号
    }

    QComboBox::mousePressEvent(event);
}


bool TFFrameNameComboBox::hasFrame(const std::string &frame_name)
{
    tf_listener::TfListener current_tf_listener;
    ros::V_string frames; // varying string
    current_tf_listener.getFramesList(frames);
    auto it = std::find(frames.begin(), frames.end(), frame_name);
    return it != frames.end();
}

void TFFrameNameComboBox::getFilterFrameNames()
{
    tf_listener::TfListener current_tf_listener;
    ros::V_string frames; // varying string
    current_tf_listener.getFramesList(frames);
    robot_model_loader::RobotModelLoaderConstPtr robot_model_loader_;
    robot_model_loader_.reset(new robot_model_loader::RobotModelLoader("robot_description"));
    if (robot_model_loader_->getModel())  // Ensure that robot is brought up
     {

       const std::vector<std::string>& robot_links = robot_model_loader_->getModel()->getLinkModelNames();
       for (const std::string& name : frames)
       {
         auto it = std::find(robot_links.begin(), robot_links.end(), name);
         size_t index = name.find("camera");

         if (frame_source_ == ROBOT_FRAME)
           if (it != robot_links.end())
             addItem(QString(name.c_str()));

         // add all frames as potential camera frame
         if (frame_source_ == CAMERA_FRAME)
           addItem(QString(name.c_str()));

         if (frame_source_ == ENVIRONMENT_FRAME)
           if (it == robot_links.end() && index == std::string::npos)
             addItem(QString(name.c_str()));
       }
    }
}

void TFFrameNameComboBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        getFilterFrameNames();
        showPopup();
        emit clicked();  //触发clicked信号
    }

    QComboBox::mousePressEvent(event);
}
