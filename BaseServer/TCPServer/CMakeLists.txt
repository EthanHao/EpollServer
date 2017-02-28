cmake_minimum_required(VERSION 3.5)
#project name
PROJECT(TCPServer)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#head file path
INCLUDE_DIRECTORIES(./include)
INCLUDE_DIRECTORIES(../Common/Clog/include)
#source directory
AUX_SOURCE_DIRECTORY(src CPP_FILES)
#print the direcories
MESSAGE(STATUS "CPP_FILES: " ${CPP_FILES})
MESSAGE(STATUS "Binary dir: " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "Source dir: " ${PROJECT_SOURCE_DIR})
#set extern libraries
#SET(LIBRARIES /usr/lib/x86_64-linux-gnu/libm.so)
#add executable file
ADD_EXECUTABLE(TCPServer ${CPP_FILES})
#add link library
#TARGET_LINK_LIBRARIES(sqrtDemoB m)
TARGET_LINK_LIBRARIES( TCPServer
pthread
)

set (EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" )