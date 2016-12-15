#ifndef MSGTEST_BASEACTOR_H
#define MSGTEST_BASEACTOR_H

#include <iostream>
#include <cassert>
#include <functional>
#include <msgtest/Typedefs.h>
#include <msgtest/msgtest_ns.h>
#include <msgtest/MsgScheduler.h>
#include <msgtest/MsgMocker.h>
#include <mockcpp/Constraint.h>
USING_MOCKCPP_NS
MSGTEST_NS_START

struct ActorMixinRole {
    virtual ActorId id() const = 0;
};

////////////////////////////////////////////////////////////////////////////////
struct ExpectedMsgSpecHolder : ActorMixinRole {
    void holdMsgSpec(MsgId expectedMsgId, Constraint* payloadConstraint, Constraint* lenConstraint) {
        expectedMsgId_ = expectedMsgId;
        payloadConstraint_ = payloadConstraint;
        lenConstraint_ = lenConstraint;
    }

    MsgId expectedMsgId_;
    Constraint* payloadConstraint_;
    Constraint* lenConstraint_;
};

struct ExpectedMsgSpecActivator : ActorMixinRole {
    void setupExpectedFromMsgSpec(ExpectedMsgSpecHolder &from) {
        MsgMocker::setupMsgMockSpec(from.id()
                                    , id()
                                    , from.expectedMsgId_
                                    , from.payloadConstraint_
                                    , from.lenConstraint_);
    }

    void setupExpectedToMsgSpec(ExpectedMsgSpecHolder &to) {
        MsgMocker::setupMsgMockSpec(id()
                                    , to.id()
                                    , to.expectedMsgId_
                                    , to.payloadConstraint_
                                    , to.lenConstraint_);
    }
};

////////////////////////////////////////////////////////////////////////////////
struct MsgTempHolder : ActorMixinRole {
    MsgTempHolder() : msgId_(0), payload_(nullptr), len_(0) {/**/}

    void holdTempMsg(MsgId msgId, void *payload, size_t len) {
          msgId_ = msgId;
        payload_ = payload;
            len_ = len;
    }

    MsgId msgId_;
    void* payload_;
    size_t len_;
};

struct MsgSender : ActorMixinRole {
    void sendMsg(MsgTempHolder& m) {
        MsgScheduler::scheduleMsg(id(), m.id(), m.msgId_, m.payload_, m.len_);
    }

    void receiveMsg(MsgTempHolder& m) {
        MsgScheduler::scheduleMsg(m.id(), id(), m.msgId_, m.payload_, m.len_);
    }
};

////////////////////////////////////////////////////////////////////////////////
struct BaseActor : MsgTempHolder
                 , MsgSender
                 , ExpectedMsgSpecHolder
                 , ExpectedMsgSpecActivator {
    BaseActor(ActorId actorId) : actorId_(actorId) {/**/}

    virtual ActorId id() const { return actorId_; }

private:
    ActorId actorId_;
};

MSGTEST_NS_END
#endif //MSGTEST_BASEACTOR_H
