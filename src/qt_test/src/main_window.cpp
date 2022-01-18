/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/qt_test/main_window.hpp"
#include <QList>
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_test {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , qnode(argc,argv)
{

    ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

    ReadSettings();
    setWindowIcon(QIcon(":/images/icon.png"));
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    /*********************
    ** Logging
    **********************/
    ui.view_logging->setModel(qnode.loggingModel());
    ui.pushButton_sub->setEnabled(false);
    //init overwritte ui
    //ui.treeWidget_TopicLists->setColumnCount(1);
    //ui.treeWidget_TopicLists->setHeaderLabel("Toplic Lists");

    //init ui
//    ui.ImageInfo_comboBox->addMsgsFilterType("sensor_msgs/Image");
//    ui.CameraInfo_comboBox->addMsgsFilterType("sensor_msgs/CameraInfo");

    QObject::connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));
    QObject::connect(&qnode,SIGNAL(image_val(QImage)),this,SLOT(slot_update_image(QImage)));
    //QObject::connect(ui.text_comboBox,SIGNAL(clicked()),this,SLOT(updateContext()));
    /*********************
    ** Auto Start
    **********************/
    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::showNoMasterMessage() {
    QMessageBox msgBox;
    msgBox.setText("Couldn't find the ros master.");
    msgBox.exec();
    close();
}

void MainWindow::showAllCameraTopicsAndFrames()
{
    ui.CameraInfo_comboBox->clear();
    ui.ImageInfo_comboBox->clear();
    ui.Sensor_comboBox->clear();
    ui.Object_comboBox->clear();
    ui.End_effector_comboBox->clear();
    ui.Base_comboBox->clear();
    std::map<std::string,CameraTopics> ros_topics;
    std::map<std::string, TFFrameName> frame_group;
    qnode.GetTopicsAndFrames(ros_topics,frame_group);
    for (auto item:ros_topics)
    {
        size_t index = item.first.find("info");
        QSet<QString> topics;
        item.second.GetRosTopic(topics);
        QSetIterator<QString> it(topics);
        if (index!=std::string::npos)
        {
            while (it.hasNext())
                ui.CameraInfo_comboBox->addItem(it.next());
        }
        else
            while (it.hasNext())
                ui.ImageInfo_comboBox->addItem(it.next());
    }
    for (auto item:frame_group)
    {
        size_t index1 = item.first.find("sensor");
        size_t index2 = item.first.find("object");
        size_t index3 = item.first.find("eef");
        size_t index4 = item.first.find("base");
        QSet<QString> topics;
        item.second.getFrameNames(topics);
        QSetIterator<QString> it(topics);
        if (index1!=std::string::npos)
        {
            while (it.hasNext())
                ui.Sensor_comboBox->addItem(it.next());
        }
        if (index2!=std::string::npos)
        {
            while (it.hasNext())
                ui.Object_comboBox->addItem(it.next());
        }
        if (index3!=std::string::npos)
        {
            while (it.hasNext())
                ui.End_effector_comboBox->addItem(it.next());
        }
        if (index4!=std::string::npos)
        {
            while (it.hasNext())
                ui.Base_comboBox->addItem(it.next());
        }
    }
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check )
{
    qRegisterMetaType<QVector<int>>("QVector<int>");
    if ( ui.checkbox_use_environment->isChecked() )
    {
        if ( !qnode.init() )
        {
            showNoMasterMessage();
        }
        else
        {
            showAllCameraTopicsAndFrames();
            ui.CameraInfo_comboBox->setEnabled(true);
            ui.ImageInfo_comboBox->setEnabled(true);
            ui.Sensor_comboBox->setEnabled(true);
            ui.End_effector_comboBox->setEnabled(true);
            ui.Object_comboBox->setEnabled(true);
            ui.Base_comboBox->setEnabled(true);

            ui.pushButton_sub->setEnabled(true);
            ui.button_connect->setEnabled(false);
        }
    }
    else
    {
        if ( ! qnode.init(ui.line_edit_master->text().toStdString(),
                          ui.line_edit_host->text().toStdString()) )
        {
            showNoMasterMessage();
        }
        else
        {
            ui.CameraInfo_comboBox->setEnabled(true);
            ui.ImageInfo_comboBox->setEnabled(true);
            ui.Sensor_comboBox->setEnabled(true);
            ui.End_effector_comboBox->setEnabled(true);
            ui.Object_comboBox->setEnabled(true);
            ui.Base_comboBox->setEnabled(true);

            ui.pushButton_sub->setEnabled(true);
            ui.button_connect->setEnabled(false);
            ui.line_edit_master->setReadOnly(true);
            ui.line_edit_host->setReadOnly(true);
            ui.line_edit_topic->setReadOnly(true);
        }
    }
}


void MainWindow::on_checkbox_use_environment_stateChanged(int state) {
    bool enabled;
    if ( state == 0 ) {
        enabled = true;
    } else {
        enabled = false;
    }
    ui.line_edit_master->setEnabled(enabled);
    ui.line_edit_host->setEnabled(enabled);
    //ui.line_edit_topic->setEnabled(enabled);
}

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */
void MainWindow::updateLoggingView() {
    ui.view_logging->scrollToBottom();
}

void MainWindow::slot_update_image(QImage image)
{
    ui.label_image_show->setPixmap(QPixmap::fromImage(image));
}

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "qt_test");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://192.168.1.2:11311/")).toString();
    QString host_url = settings.value("host_url", QString("192.168.1.3")).toString();
    //QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
    ui.line_edit_master->setText(master_url);
    ui.line_edit_host->setText(host_url);
    //ui.line_edit_topic->setText(topic_name);
    bool remember = settings.value("remember_settings", false).toBool();
    ui.checkbox_remember_settings->setChecked(remember);
    bool checked = settings.value("use_environment_variables", false).toBool();
    ui.checkbox_use_environment->setChecked(checked);
    if ( checked ) {
        ui.line_edit_master->setEnabled(false);
        ui.line_edit_host->setEnabled(false);
        //ui.line_edit_topic->setEnabled(false);
    }
}

void MainWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", "qt_test");
    settings.setValue("master_url",ui.line_edit_master->text());
    settings.setValue("host_url",ui.line_edit_host->text());
    //settings.setValue("topic_name",ui.line_edit_topic->text());
    settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    WriteSettings();
    QMainWindow::closeEvent(event);
}

}  // namespace qt_test


void qt_test::MainWindow::on_pushButton_sub_clicked()
{
    QString str=ui.ImageInfo_comboBox->currentText();
    qnode.sub_image(str);
}

