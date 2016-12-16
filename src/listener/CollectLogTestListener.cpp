#include "msgtest/listener/CollectLogTestListener.h"

MSGTEST_NS_START

    void g_collect_msg_log_func(ActorId from, ActorId to, MsgId msgId, void* payload, size_t len) {
        std::cout << "Actor from: " << from;
        std::cout << " ----> " << to;
        std::cout << " msgid: " << msgId;
        std::cout << " payload: " << payload;
        std::cout << " len: " << len << std::endl;
    }

    void CollectLogTestListener::OnTestStart(const ::testing::TestInfo &) {

    }

    void CollectLogTestListener::OnTestEnd(const ::testing::TestInfo &) {

    }

MSGTEST_NS_END