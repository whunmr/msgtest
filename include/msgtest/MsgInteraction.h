#ifndef MSGTEST_MSGINTERACTION_H
#define MSGTEST_MSGINTERACTION_H
#include <msgtest/Macros.h>
#include <msgtest/msgtest_ns.h>
MSGTEST_NS_START

//struct MsgInteraction {
//    virtual void exec() = 0;
//
//    void setup_mocks___and___execute();
//};
//
//#define msg_interaction_ex \
//    static struct MSGTEST_ANONYMOUS_VARIABLE(MsgInteraction) : MsgInteraction { \
//    void exec()
//
//#define ___end \
//    } MSGTEST_ANONYMOUS_VARIABLE(MsgInteractionInstance); \
//    MSGTEST_ANONYMOUS_VARIABLE(MsgInteractionInstance).setup_mocks___and___execute();


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
