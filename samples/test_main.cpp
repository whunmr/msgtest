#include <gtest/gtest.h>

#include <msgtest/msgtest.h>
#include "common/Messaging.h"

USING_MSGTEST_NS


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    MsgSender::init_send_msg_func(g_send_msg_func);

    return RUN_ALL_TESTS();
}
