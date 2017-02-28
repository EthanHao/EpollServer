project (CLOG)

cmake_minimum_required(VERSION 3.5)

add_subdirectory(src)
add_subdirectory(include)

add_subdirectory(tests)


ENABLE_TESTING()
ADD_TEST(T1 ${PROJECT_BINARY_DIR}/tests/test1)
ADD_TEST(T2 ${PROJECT_BINARY_DIR}/tests/test2)

add_custom_target(build-tests  DEPENDS ${PROJECT_BINARY_DIR}/tests/test1 ${PROJECT_BINARY_DIR}/tests/test2)


#install

install (FILES include/log.h  include/LogFile.h include/Exception.h        
         DESTINATION include)  