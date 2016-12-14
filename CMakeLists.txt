cmake_minimum_required(VERSION 3.6)
project(msgtest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(SOURCE_FILES src/msgtestlibsamplefile.cpp)
add_library(msgtest ${SOURCE_FILES})


set(SAMPLE_TEST_FILES samples/sample1.cpp)
add_executable(msgtest_sample_usage ${SAMPLE_TEST_FILES})
target_link_libraries(msgtest_sample_usage ${GTEST_BOTH_LIBRARIES} msgtest)
add_test(AllTestsInMsgtest msgtest_sample_usage)
