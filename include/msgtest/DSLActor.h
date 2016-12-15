#ifndef MSGTEST_DSLACTOR_H
#define MSGTEST_DSLACTOR_H

#include <cstddef>
#include <msgtest/Typedefs.h>
#include <msgtest/BaseActor.h>
#include <mockcpp/mockcpp.hpp>
USING_MOCKCPP_NS

MSGTEST_NS_START

struct TestPhase {
    enum Phase {
        SetupMockPhase,
        ExecuteMsgInteractionPhase
    };

    static Phase phase_;
};

template<typename T>
struct DSLActor {
    T& operator--(int) { return static_cast<T&>(*this); }
    T& operator--()    { return static_cast<T&>(*this); }

    ////////////////////////////////////////////////////////////////////////////
    template<typename PAYLOAD>
    T& operator()(MsgId msgid, PAYLOAD* payload) {
        return operator()(msgid, payload, sizeof(PAYLOAD));
    }

    T& operator()(MsgId msgid, void* payload, size_t len) {
        if (TestPhase::phase_ == TestPhase::ExecuteMsgInteractionPhase)
            as<MsgTempHolder &>().holdTempMsg(msgid, payload, len);

        return asActor();
    }

    void operator>(MsgTempHolder& msgTempHolder) {
        if (TestPhase::phase_ == TestPhase::ExecuteMsgInteractionPhase)
            as<MsgSender&>().sendMsg(msgTempHolder);
    }

    void operator<(MsgTempHolder& msgTempHolder) {
        if (TestPhase::phase_ == TestPhase::ExecuteMsgInteractionPhase)
            as<MsgSender&>().receiveMsg(msgTempHolder);
    }

    ////////////////////////////////////////////////////////////////////////////
    T& operator()(MsgId expectedMsgId) {
        return operator()(expectedMsgId, any(), any());
    }

    T& operator()(MsgId expectedMsgId, Constraint* c1, Constraint* c2) {
        if (TestPhase::phase_ == TestPhase::SetupMockPhase)
            as<ExpectedMsgSpecHolder&>().holdMsgSpec(expectedMsgId, c1, c2);

        return asActor();
    }


    void operator<<(ExpectedMsgSpecHolder& h) {
        if (TestPhase::phase_ == TestPhase::SetupMockPhase)
            as<ExpectedMsgSpecActivator &>().setupExpectedFromMsgSpec(h);
    }

    void operator>>(ExpectedMsgSpecHolder& h) {
        if (TestPhase::phase_ == TestPhase::SetupMockPhase)
            as<ExpectedMsgSpecActivator &>().setupExpectedToMsgSpec(h);
    }

private:
    T& asActor() {
        return static_cast<T&>(*this);
    }

    template<typename RefType>
    RefType as() {
        return static_cast<RefType>(asActor());
    }
};

MSGTEST_NS_END
#endif //MSGTEST_DSLACTOR_H
