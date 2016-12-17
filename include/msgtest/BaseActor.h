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
MSGTEST_NS_START

struct ActorMixinRole {
    virtual ActorId id() const = 0;
};

////////////////////////////////////////////////////////////////////////////////
struct ExpectedMsgSpecHolder : ActorMixinRole {
    using Constraint = mockcpp::Constraint;

    void holdMsgSpec(MsgId expectedMsgId, Constraint* payloadConstraint, Constraint* lenConstraint, const std::string& msgType) {
        expectedMsgId_ = expectedMsgId;
        payloadConstraint_ = payloadConstraint;
        lenConstraint_ = lenConstraint;
        msgType_ = msgType;
    }

    MsgId expectedMsgId_;
    Constraint* payloadConstraint_;
    Constraint* lenConstraint_;
    std::string msgType_;
};

struct ExpectedMsgSpecActivator : ActorMixinRole {
    void setupExpectedFromMsgSpec(ExpectedMsgSpecHolder &from) {
        std::cout << "expected msg: " << from.msgType_ << std::endl;
        MsgMocker::setupMsgMockSpec(from.id()
                                    , id()
                                    , from.expectedMsgId_
                                    , from.payloadConstraint_
                                    , from.lenConstraint_);
    }

    void setupExpectedToMsgSpec(ExpectedMsgSpecHolder &to) {
        std::cout << "expected msg: " << to.msgType_ << std::endl;
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

    void holdTempMsg(MsgId msgId, const void *payload, size_t len, const std::string& payloadType) {
        msgId_ = msgId;
        payload_ = payload;
        len_ = len;
        payloadType_ = payloadType;
    }

    MsgId msgId_;
    const void* payload_;
    size_t len_;
    std::string payloadType_;
};

struct MsgSender : ActorMixinRole {
    void sendMsg(MsgTempHolder& to) {
        std::cout << to.payloadType_ << std::endl;
        MsgScheduler::scheduleMsg(id(), to.id(), to.msgId_, to.payload_, to.len_);
    }

    void receiveMsg(MsgTempHolder& from) {
        std::cout << from.payloadType_ << std::endl;
        MsgScheduler::scheduleMsg(from.id(), id(), from.msgId_, from.payload_, from.len_);
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
