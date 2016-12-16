#include <msgtest/MsgMocker.h>
#include <mockcpp/mockcpp.hpp>
USING_MOCKCPP_NS

MSGTEST_NS_START
    void g_msgtest_trace_msg_probe_func(ActorId from, ActorId to, MsgId msgId, void *payload, size_t len) {
        /**/
    }

    ////////////////////////////////////////////////////////////////////////////
    namespace {
        int mock_spec_index_ = 0;
    }

    void MsgMocker::setupMsgMockSpec(ActorId from, ActorId to, MsgId msgId
                                    , mockcpp::Constraint *c1
                                    , mockcpp::Constraint *c2) {

        if (mock_spec_index_ == 0) {
            MOCKER(g_msgtest_trace_msg_probe_func).expects(once())
                    .with(eq(from), eq(to), eq(msgId), c1, c2)
                    .id(std::to_string(mock_spec_index_));
        } else {
            MOCKER(g_msgtest_trace_msg_probe_func).expects(once())
                    .with(eq(from), eq(to), eq(msgId), c1, c2)
                    .after(std::to_string(mock_spec_index_ - 1))
                    .id(std::to_string(mock_spec_index_));
        }

        ++mock_spec_index_;
    }

    void MsgMocker::setupDefaultMock() {
        MOCKER(g_msgtest_trace_msg_probe_func).stubs().with(any(), any(), any(), any(), any());
    }

    void MsgMocker::verifyMockSpec() {
        mock_spec_index_ = 0;
        GlobalMockObject::verify();
    }

MSGTEST_NS_END
