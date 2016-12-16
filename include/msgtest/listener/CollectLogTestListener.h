#ifndef MSGTEST_TRACELOGTESTLISTENER_H
#define MSGTEST_TRACELOGTESTLISTENER_H
#include <gtest/gtest.h>
#include <msgtest/msgtest_ns.h>
#include <msgtest/Typedefs.h>
MSGTEST_NS_START

extern void g_collect_msg_log_func(ActorId from, ActorId to, MsgId, void*, size_t);

class CollectLogTestListener : public ::testing::EmptyTestEventListener {
    virtual void OnTestStart(const ::testing::TestInfo& /*test_info*/);
    virtual void OnTestEnd(const ::testing::TestInfo& /*test_info*/);
};

MSGTEST_NS_END
#endif //MSGTEST_TRACELOGTESTLISTENER_H
