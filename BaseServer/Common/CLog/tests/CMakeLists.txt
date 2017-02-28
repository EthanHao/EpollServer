SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ADD_EXECUTABLE(test1 newsimpletest.cpp)
TARGET_LINK_LIBRARIES( test1
CLOG
)

ADD_EXECUTABLE(test2 newsimpletest1.cpp)
TARGET_LINK_LIBRARIES( test2
CLOG
pthread
)





