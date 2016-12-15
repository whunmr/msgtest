#include <gtest/gtest.h>
#include <msgtest/msgtest.h>
#include "app.h"

USING_MSGTEST_NS

class MockMsgSpecVerifier : public ::testing::EmptyTestEventListener {
    virtual void OnTestEnd(const ::testing::TestInfo& test_info) {
        MsgMocker::verifyMockSpec();
    }
};

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    MsgScheduler::set_app_schedule_msg_func(g_app_msg_loop);

    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new MockMsgSpecVerifier);

    return RUN_ALL_TESTS();
}
