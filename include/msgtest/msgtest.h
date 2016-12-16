#ifndef MSGTEST_MSGTEST_H_H
#define MSGTEST_MSGTEST_H_H

#include <msgtest/Typedefs.h>
#include <msgtest/StubActor.h>
#include <msgtest/UnderTestActor.h>
#include <msgtest/MsgInteraction.h>
#include <msgtest/MsgSaver.h>
#include <msgtest/listener/VerifyMockTestListener.h>
#include <msgtest/listener/CollectLogTestListener.h>

#define INIT_MSGTEST_WITH_SCHEDULE_MSG_FUNC(msg_schedule_func)                                  \
    MsgScheduler::set_app_schedule_msg_func(msg_schedule_func);                                 \
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners(); \
    listeners.Append(new VerifyMockTestListener);                                               \
    listeners.Append(new CollectLogTestListener);

#define MSGTEST_PROBE_MSG_SCHEDULE()                               \
    g_msgtest_trace_msg_probe_func(from, to, msgId, payload, len); \
    g_collect_msg_log_func(from, to, msgId, payload, len);

#endif //MSGTEST_MSGTEST_H_H
