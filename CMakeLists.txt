cmake_minimum_required(VERSION 3.24)
project(Project_3_AirDelay_Detections)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_3_AirDelay_Detections src/main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(Project_3_AirDelay_Detections sfml-system sfml-window sfml-graphics sfml-audio)

