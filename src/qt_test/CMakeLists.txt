##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.0)
project(qt_test)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(Eigen3 REQUIRED)
find_package(catkin REQUIRED COMPONENTS
    qt_build
    roscpp
    cv_bridge
    image_transport
    sensor_msgs
    std_msgs
    geometry_msgs
    tf2
    tf2_eigen
    tf2_ros
    moveit_core
    moveit_ros_perception
    moveit_ros_planning
    moveit_ros_planning_interface
    moveit_ros_visualization
    moveit_visual_tools
    rviz
    rviz_visual_tools
    pluginlib
    )
include_directories(
    ${catkin_INCLUDE_DIRS}
    ${Eigen_INCLUDE_DIRS})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 REQUIRED Core Widgets)
set(CMAKE_AUTOMOC ON)
set(QT_LIBRARIES Qt5::Widgets)
find_package(OpenCV REQUIRED)
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything. 
catkin_package(  
INCLUDE_DIRS
    single_handeye_calibration_target/include
    single_handeye_calibration_solver/include
  LIBRARIES
    # No libraries are exported because directly linking to a plugin is "highly discouraged":
    # http://wiki.ros.org/class_loader#Caution_of_Linking_Directly_Against_Plugin_Libraries
  CATKIN_DEPENDS
    roscpp
    sensor_msgs
  DEPENDS
    EIGEN3)
##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically 
# included via the dependency call in package.xml
# rosbuild_prepare_qt4(QtCore QtGui) # Add the appropriate components to the component list here

##############################################################################
# Sections
##############################################################################

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/qt_test/*.hpp *.h)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

include_directories(
                    handeye_calibration_target/include
                    handeye_calibration_solver/include
                    ${catkin_INCLUDE_DIRS}
                    )
include_directories(SYSTEM
                    ${OpenCV_INCLUDE_DIRS}
                    ${EIGEN3_INCLUDE_DIRS}
                    )

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################
add_executable(qt_test ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
target_link_libraries(qt_test ${QT_LIBRARIES} ${catkin_LIBRARIES} ${OpenCV_LIBS})
install(TARGETS qt_test RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
add_subdirectory(single_handeye_calibration_target)
add_subdirectory(single_handeye_calibration_solver)

install(
  FILES
    handeye_calibration_target_plugin_description.xml
    handeye_calibration_solver_plugin_description.xml
  DESTINATION
    ${CATKIN_PACKAGE_SHARE_DESTINATION})

