#ifndef MSGTEST_MSGINTERACTION_H
#define MSGTEST_MSGINTERACTION_H
#include <msgtest/Macros.h>
#include <msgtest/msgtest_ns.h>
MSGTEST_NS_START

#define msg_interaction(...)                                          \
    {                                                                 \
        TestPhase::phase_ = TestPhase::SetupMockPhase;                \
        __VA_ARGS__                                                   \
        MsgMocker::setupDefaultMock();                                \
    }                                                                 \
    {                                                                 \
        TestPhase::phase_ = TestPhase::ExecuteMsgInteractionPhase;    \
        __VA_ARGS__                                                   \
        MsgMocker::verifyMockSpec();                                  \
    }

MSGTEST_NS_END
#endif //MSGTEST_MSGINTERACTION_H
