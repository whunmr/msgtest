#include <msgtest/MsgInteraction.h>
#include <msgtest/DSLActor.h>
#include <mockcpp/mockcpp.hpp>
USING_MOCKCPP_NS

MSGTEST_NS_START

    void MsgInteraction::setup_mocks___and___execute() {
        TestPhase::phase_ = TestPhase::SetupMockPhase;
        exec();

        MOCKER(g_msgtest_trace_msg_probe_func).stubs().with(any(), any(), any(), any(), any());

        TestPhase::phase_ = TestPhase::ExecuteMsgInteractionPhase;
        exec();

        GlobalMockObject::verify();
    }


MSGTEST_NS_END
