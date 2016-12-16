#include "msgtest/listener/AutoRegTestListener.h"

MSGTEST_NS_START

    AutoRegTestListener::AutoRegTestListener() {
        ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
        listeners.Append(this);
    }

    void AutoRegTestListener::deRegister() {
        ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
        listeners.Release(this);
    }

MSGTEST_NS_END