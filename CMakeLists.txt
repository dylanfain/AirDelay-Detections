cmake_minimum_required(VERSION 3.24)
project(Project_3_AirDelay_Detections)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_3_AirDelay_Detections main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
#set(TGUI_STATIC_LIBRARIES TRUE)

set(SFML_DIR C:/SFML/lib/cmake/SFML)
#set(TGUI_DIR C:/TGUI/lib/cmake/TGUI)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
#find_package(TGUI COMPONENTS backend extlibs loading renderers widgets REQUIRED)

include_directories(c:/SFML/include/SFML)
#include_directories(c:/TGUI/include/)
target_link_libraries(Project_3_AirDelay_Detections sfml-system sfml-window sfml-graphics sfml-audio)
#tgui-backend tgui-extlibs tgui-loading tgui-renderers tgui-widgets