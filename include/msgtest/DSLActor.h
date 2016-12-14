#ifndef MSGTEST_DSLACTOR_H
#define MSGTEST_DSLACTOR_H

#include <cstddef>
#include <msgtest/Typedefs.h>
#include <msgtest/BaseActor.h>
MSGTEST_NS_START

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
        as<MsgTempHolder &>().holdTempMsg(msgid, payload, len);
        return asActor();
    }

    void operator>(MsgTempHolder& msgTempHolder) {
        as<MsgSender&>().sendMsg(msgTempHolder);
    }

    void operator<(MsgTempHolder& msgTempHolder) {
        as<MsgSender&>().receiveMsg(msgTempHolder);
    }

    ////////////////////////////////////////////////////////////////////////////
    T& operator()(MsgId expectedMsgId) {
        as<ExpectedMsgSpecHolder&>().holdMsgSpec(expectedMsgId);
        return asActor();
    }

    void operator<<(ExpectedMsgSpecHolder& h) {
        as<ExpectedMsgSpecActivator&>().setupExpectedFromMsgSpec(h);
    }

    void operator>>(ExpectedMsgSpecHolder& h) {
        as<ExpectedMsgSpecActivator&>().setupExpectedToMsgSpec(h);
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
