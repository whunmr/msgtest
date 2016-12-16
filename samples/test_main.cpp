#include <gtest/gtest.h>
#include <msgtest/msgtest.h>
#include "app.h"

USING_MSGTEST_NS

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    MSGTEST_INIT_WITH_SCHEDULE_MSG_FUNC(g_app_msg_loop);

    return RUN_ALL_TESTS();
}
