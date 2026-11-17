cmake_minimum_required(VERSION 3.10)
project(Lab1_Processes)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(Creator  Creator.cpp)
add_executable(Reporter Reporter.cpp)
add_executable(Main     Main.cpp)

if(WIN32)
    target_link_libraries(Main PRIVATE)
endif()