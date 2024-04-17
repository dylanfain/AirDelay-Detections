cmake_minimum_required(VERSION 3.14)
project(Project_3_AirDelay_Detections)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(Project_3_AirDelay_Detections src/main.cpp
        src/main.cpp)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(c:/SFML/include/SFML)
target_link_libraries(Project_3_AirDelay_Detections sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
