#ifndef MSGTEST_MSGTESTLISTENER_H
#define MSGTEST_MSGTESTLISTENER_H

#include <gtest/gtest.h>
#include <msgtest/MsgMocker.h>
#include <msgtest/MsgSaver.h>
MSGTEST_NS_START

class MsgTestVerifyMockSpecListener : public ::testing::EmptyTestEventListener {
    virtual void OnTestEnd(const ::testing::TestInfo& test_info) {
        MsgMocker::verifyMockSpec();
    }
};

MSGTEST_NS_END
#endif //MSGTEST_MSGTESTLISTENER_H
