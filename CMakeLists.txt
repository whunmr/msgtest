cmake_minimum_required(VERSION 3.3)
project(msgtest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(LAB_ROOT ~/lab/)

set(MSGTEST_INCLUDE ${LAB_ROOT}msgtest/include)
include_directories(${MSGTEST_INCLUDE})


include_directories(${LAB_ROOT}repo/mockcpp/include)
#include_directories(${LAB_ROOT}repo/mockcpp/3rdparty)
link_directories(${LAB_ROOT}repo/mockcpp/build/src/)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(SOURCE_FILES src/StubActor.cpp include/msgtest/StubActor.h include/msgtest/msgtest.h include/msgtest/DSLActor.h include/msgtest/Typedefs.h include/msgtest/BaseActor.h include/msgtest/msgtest_ns.h src/MsgScheduler.cpp include/msgtest/MsgScheduler.h src/MsgMocker.cpp include/msgtest/MsgMocker.h src/DSLActor.cpp include/msgtest/MsgInteraction.h include/msgtest/Macros.h src/MsgSaver.cpp include/msgtest/MsgSaver.h include/msgtest/listener/VerifyMockTestListener.h src/listener/CollectLogTestListener.cpp include/msgtest/listener/CollectLogTestListener.h src/msgflow.cpp include/msgtest/msgflow.h src/msgtest.cpp)
add_library(msgtest ${SOURCE_FILES})


set(SAMPLE_TEST_FILES samples/sample_tests.cpp src/StubActor.cpp include/msgtest/StubActor.h samples/common/MsgPayload.h samples/common/MsgId.h samples/test_main.cpp samples/app_ids.h samples/app.cpp samples/app.h)
add_executable(msgtest_sample_usage ${SAMPLE_TEST_FILES})
target_link_libraries(msgtest_sample_usage ${GTEST_LIBRARIES} msgtest pthread mockcpp)


add_test(AllTestsInMsgtest msgtest_sample_usage)

