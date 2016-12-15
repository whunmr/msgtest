#include <msgtest/MsgMocker.h>
#include <mockcpp/mockcpp.hpp>
USING_MOCKCPP_NS

MSGTEST_NS_START

    void g_msgtest_trace_msg_probe_func(ActorId from, ActorId to, MsgId msgId, void *payload, size_t len) {
        /**/
    }

    void MsgMocker::setupMsgMockSpec(ActorId from, ActorId to, MsgId msgId
                                    , mockcpp::Constraint *c1
                                    , mockcpp::Constraint *c2) {
        MOCKER(g_msgtest_trace_msg_probe_func)
                .expects(once())
                .with(eq(from), eq(to), eq(msgId), c1, c2);
    }

    void MsgMocker::verifyMockSpec() {
        GlobalMockObject::verify();
    }

MSGTEST_NS_END