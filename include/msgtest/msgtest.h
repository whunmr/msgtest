#ifndef MSGTEST_MSGTEST_H_H
#define MSGTEST_MSGTEST_H_H

#include <msgtest/Typedefs.h>
#include <msgtest/StubActor.h>
#include <msgtest/UnderTestActor.h>
#include <msgtest/MsgInteraction.h>
#include <msgtest/MsgSaver.h>
#include <msgtest/MsgTestVerifyMockSpecListener.h>

#define INIT_MSGTEST_WITH_SCHEDULE_MSG_FUNC(msg_schedule_func) \
    MsgScheduler::set_app_schedule_msg_func(msg_schedule_func); \
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners(); \
    listeners.Append(new MsgTestVerifyMockSpecListener);

#endif //MSGTEST_MSGTEST_H_H
