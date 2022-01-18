/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QFormLayout *formLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLineEdit *line_edit_master;
    QLabel *label_2;
    QLineEdit *line_edit_host;
    QLabel *label_3;
    QLineEdit *line_edit_topic;
    QCheckBox *checkbox_remember_settings;
    QCheckBox *checkbox_use_environment;
    QListView *view_logging;
    QPushButton *button_connect;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_5;
    QComboBox *Base_comboBox;
    QComboBox *Object_comboBox;
    QComboBox *End_effector_comboBox;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *Sensor_comboBox;
    QLabel *label_7;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QGridLayout *gridLayout;
    QLabel *label_9;
    QComboBox *ImageInfo_comboBox;
    QLabel *label_10;
    QLabel *label_image_show;
    QPushButton *pushButton_sub;
    QComboBox *CameraInfo_comboBox;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_2;
    QPushButton *Sample_pushButton;
    QPushButton *pushButton;
    QPushButton *clear_pushButton;
    QTreeWidget *Samples_treeWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_7;
    QLabel *label_8;
    QComboBox *solver_comboBox;
    QPushButton *solve_pushButton;
    QPushButton *quit_button;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QStringLiteral("MainWindowDesign"));
        MainWindowDesign->resize(1035, 1049);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindowDesign);
        action_Preferences->setObjectName(QStringLiteral("action_Preferences"));
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        formLayout_2 = new QFormLayout(centralwidget);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setFrameShape(QFrame::StyledPanel);
        label->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        line_edit_master = new QLineEdit(groupBox);
        line_edit_master->setObjectName(QStringLiteral("line_edit_master"));

        gridLayout_4->addWidget(line_edit_master, 0, 1, 1, 3);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFrameShape(QFrame::StyledPanel);
        label_2->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(label_2, 1, 0, 1, 1);

        line_edit_host = new QLineEdit(groupBox);
        line_edit_host->setObjectName(QStringLiteral("line_edit_host"));

        gridLayout_4->addWidget(line_edit_host, 1, 1, 1, 3);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(label_3, 2, 0, 1, 1);

        line_edit_topic = new QLineEdit(groupBox);
        line_edit_topic->setObjectName(QStringLiteral("line_edit_topic"));
        line_edit_topic->setEnabled(false);

        gridLayout_4->addWidget(line_edit_topic, 2, 1, 1, 3);

        checkbox_remember_settings = new QCheckBox(groupBox);
        checkbox_remember_settings->setObjectName(QStringLiteral("checkbox_remember_settings"));
        checkbox_remember_settings->setLayoutDirection(Qt::RightToLeft);

        gridLayout_4->addWidget(checkbox_remember_settings, 3, 0, 1, 3);

        checkbox_use_environment = new QCheckBox(groupBox);
        checkbox_use_environment->setObjectName(QStringLiteral("checkbox_use_environment"));
        checkbox_use_environment->setLayoutDirection(Qt::RightToLeft);

        gridLayout_4->addWidget(checkbox_use_environment, 3, 3, 1, 1);

        view_logging = new QListView(groupBox);
        view_logging->setObjectName(QStringLiteral("view_logging"));
        view_logging->setMinimumSize(QSize(0, 0));
        view_logging->setMaximumSize(QSize(10000, 25));

        gridLayout_4->addWidget(view_logging, 4, 0, 1, 2);

        button_connect = new QPushButton(groupBox);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        button_connect->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(button_connect->sizePolicy().hasHeightForWidth());
        button_connect->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(button_connect, 4, 2, 1, 2);


        gridLayout_6->addLayout(gridLayout_4, 0, 0, 1, 1);


        formLayout_2->setWidget(0, QFormLayout::LabelRole, groupBox);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        Base_comboBox = new QComboBox(groupBox_3);
        Base_comboBox->setObjectName(QStringLiteral("Base_comboBox"));
        Base_comboBox->setEnabled(false);

        gridLayout_5->addWidget(Base_comboBox, 3, 1, 1, 1);

        Object_comboBox = new QComboBox(groupBox_3);
        Object_comboBox->setObjectName(QStringLiteral("Object_comboBox"));
        Object_comboBox->setEnabled(false);

        gridLayout_5->addWidget(Object_comboBox, 1, 1, 1, 1);

        End_effector_comboBox = new QComboBox(groupBox_3);
        End_effector_comboBox->setObjectName(QStringLiteral("End_effector_comboBox"));
        End_effector_comboBox->setEnabled(false);

        gridLayout_5->addWidget(End_effector_comboBox, 2, 1, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_5->addWidget(label_5, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 2, 0, 1, 1);

        Sensor_comboBox = new QComboBox(groupBox_3);
        Sensor_comboBox->setObjectName(QStringLiteral("Sensor_comboBox"));
        Sensor_comboBox->setEnabled(false);

        gridLayout_5->addWidget(Sensor_comboBox, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 3, 0, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_5, 0, 0, 1, 1);


        formLayout_2->setWidget(0, QFormLayout::FieldRole, groupBox_3);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 0, 0, 1, 1);

        ImageInfo_comboBox = new QComboBox(groupBox_2);
        ImageInfo_comboBox->setObjectName(QStringLiteral("ImageInfo_comboBox"));
        ImageInfo_comboBox->setEnabled(false);

        gridLayout->addWidget(ImageInfo_comboBox, 0, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 1, 0, 1, 1);

        label_image_show = new QLabel(groupBox_2);
        label_image_show->setObjectName(QStringLiteral("label_image_show"));
        label_image_show->setMinimumSize(QSize(640, 480));
        label_image_show->setMaximumSize(QSize(640, 480));
        label_image_show->setStyleSheet(QStringLiteral("border:1px solid black"));

        gridLayout->addWidget(label_image_show, 3, 0, 1, 2);

        pushButton_sub = new QPushButton(groupBox_2);
        pushButton_sub->setObjectName(QStringLiteral("pushButton_sub"));
        pushButton_sub->setMinimumSize(QSize(200, 2));

        gridLayout->addWidget(pushButton_sub, 2, 1, 1, 1);

        CameraInfo_comboBox = new QComboBox(groupBox_2);
        CameraInfo_comboBox->setObjectName(QStringLiteral("CameraInfo_comboBox"));
        CameraInfo_comboBox->setEnabled(false);

        gridLayout->addWidget(CameraInfo_comboBox, 1, 1, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout);


        formLayout_2->setWidget(1, QFormLayout::LabelRole, groupBox_2);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_9 = new QGridLayout(groupBox_4);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_2 = new QPushButton(groupBox_4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 1, 1, 1, 1);

        Sample_pushButton = new QPushButton(groupBox_4);
        Sample_pushButton->setObjectName(QStringLiteral("Sample_pushButton"));

        gridLayout_2->addWidget(Sample_pushButton, 0, 0, 1, 1);

        pushButton = new QPushButton(groupBox_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_2->addWidget(pushButton, 1, 0, 1, 1);

        clear_pushButton = new QPushButton(groupBox_4);
        clear_pushButton->setObjectName(QStringLiteral("clear_pushButton"));

        gridLayout_2->addWidget(clear_pushButton, 0, 1, 1, 1);

        Samples_treeWidget = new QTreeWidget(groupBox_4);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        Samples_treeWidget->setHeaderItem(__qtreewidgetitem);
        Samples_treeWidget->setObjectName(QStringLiteral("Samples_treeWidget"));
        Samples_treeWidget->setMaximumSize(QSize(500, 16777215));

        gridLayout_2->addWidget(Samples_treeWidget, 2, 0, 1, 2);


        gridLayout_9->addLayout(gridLayout_2, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_7->addWidget(label_8, 0, 0, 1, 1);

        solver_comboBox = new QComboBox(groupBox_4);
        solver_comboBox->setObjectName(QStringLiteral("solver_comboBox"));

        gridLayout_7->addWidget(solver_comboBox, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_7);

        solve_pushButton = new QPushButton(groupBox_4);
        solve_pushButton->setObjectName(QStringLiteral("solve_pushButton"));

        verticalLayout->addWidget(solve_pushButton);


        gridLayout_9->addLayout(verticalLayout, 2, 0, 1, 1);

        quit_button = new QPushButton(groupBox_4);
        quit_button->setObjectName(QStringLiteral("quit_button"));
        sizePolicy.setHeightForWidth(quit_button->sizePolicy().hasHeightForWidth());
        quit_button->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(quit_button, 3, 0, 1, 1);


        formLayout_2->setWidget(1, QFormLayout::FieldRole, groupBox_4);

        MainWindowDesign->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowDesign);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1035, 38));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        MainWindowDesign->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowDesign);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindowDesign->setStatusBar(statusbar);
        QWidget::setTabOrder(line_edit_master, line_edit_host);
        QWidget::setTabOrder(line_edit_host, line_edit_topic);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Preferences);
        menu_File->addSeparator();
        menu_File->addAction(actionAbout);
        menu_File->addAction(actionAbout_Qt);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));
        QObject::connect(quit_button, SIGNAL(clicked()), MainWindowDesign, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QApplication::translate("MainWindowDesign", "QRosApp", Q_NULLPTR));
        action_Quit->setText(QApplication::translate("MainWindowDesign", "&Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_Quit->setShortcut(QApplication::translate("MainWindowDesign", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_Preferences->setText(QApplication::translate("MainWindowDesign", "&Preferences", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindowDesign", "&About", Q_NULLPTR));
        actionAbout_Qt->setText(QApplication::translate("MainWindowDesign", "About &Qt", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindowDesign", "RosCore connect", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindowDesign", "Ros Master Url", Q_NULLPTR));
        line_edit_master->setText(QApplication::translate("MainWindowDesign", "http://192.168.1.2:11311/", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindowDesign", "Ros IP", Q_NULLPTR));
        line_edit_host->setText(QApplication::translate("MainWindowDesign", "192.168.1.67", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindowDesign", "Ros Hostname", Q_NULLPTR));
        line_edit_topic->setText(QApplication::translate("MainWindowDesign", "unused", Q_NULLPTR));
        checkbox_remember_settings->setText(QApplication::translate("MainWindowDesign", "Remember settings on startup", Q_NULLPTR));
        checkbox_use_environment->setText(QApplication::translate("MainWindowDesign", "Use environment variables", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_connect->setToolTip(QApplication::translate("MainWindowDesign", "Set the target to the current joint trajectory state.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        button_connect->setStatusTip(QApplication::translate("MainWindowDesign", "Clear all waypoints and set the target to the current joint trajectory state.", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        button_connect->setText(QApplication::translate("MainWindowDesign", "Connect", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindowDesign", "Frame Selection ", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindowDesign", "Object", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindowDesign", "End-effector", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindowDesign", "Robot base", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindowDesign", "Sensor", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindowDesign", "Target Pose Detection", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindowDesign", "Image Topic", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindowDesign", "CamerInfo Topic", Q_NULLPTR));
        label_image_show->setText(QApplication::translate("MainWindowDesign", "NO IMAGE", Q_NULLPTR));
        pushButton_sub->setText(QApplication::translate("MainWindowDesign", "Subscribe", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindowDesign", "Sample Information", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindowDesign", "load sample", Q_NULLPTR));
        Sample_pushButton->setText(QApplication::translate("MainWindowDesign", "take sample", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindowDesign", "save sample", Q_NULLPTR));
        clear_pushButton->setText(QApplication::translate("MainWindowDesign", "clear sample", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindowDesign", "AX=XB solver", Q_NULLPTR));
        solve_pushButton->setText(QApplication::translate("MainWindowDesign", "solve", Q_NULLPTR));
        quit_button->setText(QApplication::translate("MainWindowDesign", "Quit", Q_NULLPTR));
        menu_File->setTitle(QApplication::translate("MainWindowDesign", "&App", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
