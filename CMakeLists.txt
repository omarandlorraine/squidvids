cmake_minimum_required(VERSION 3.16)
project(squidvids LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(squidvids main.cpp)
target_link_libraries(squidvids PRIVATE Qt6::Widgets)
