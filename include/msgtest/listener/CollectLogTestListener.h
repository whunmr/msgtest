#ifndef MSGTEST_TRACELOGTESTLISTENER_H
#define MSGTEST_TRACELOGTESTLISTENER_H
#include <functional>
#include <gtest/gtest.h>
#include <msgtest/msgtest_ns.h>
#include <msgtest/Typedefs.h>
MSGTEST_NS_START

extern void g_collect_msg_log_func(ActorId from, ActorId to, MsgId, void*, size_t);

////////////////////////////////////////////////////////////////////////////////
struct LogTranslator {
    virtual std::string actor2String(ActorId actorId) const = 0;
    virtual std::string msg2String(ActorId fromActorId, MsgId msgId) const = 0;
};

struct CollectLogTestListener : public ::testing::EmptyTestEventListener {
    static void setLogTranslator(LogTranslator&);

    virtual void OnTestStart(const ::testing::TestInfo& /*test_info*/);
    virtual void OnTestEnd(const ::testing::TestInfo& /*test_info*/);
};

void msgtest_log(const std::string &log);

MSGTEST_NS_END
#endif //MSGTEST_TRACELOGTESTLISTENER_H
