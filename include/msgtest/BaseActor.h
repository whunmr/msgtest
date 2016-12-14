#ifndef MSGTEST_BASEACTOR_H
#define MSGTEST_BASEACTOR_H

#include <iostream>
#include <cassert>
#include <functional>
#include <msgtest/Typedefs.h>
#include <msgtest/msgtest_ns.h>

MSGTEST_NS_START

struct ActorMixinRole {
    virtual ActorId id() const = 0;
};

////////////////////////////////////////////////////////////////////////////////
struct ExpectedMsgSpecHolder : ActorMixinRole {
    void holdMsgSpec(MsgId expectedMsgId) {
        expectedMsgId_ = expectedMsgId;
    }

    MsgId expectedMsgId_;
};

struct ExpectedMsgSpecActivator : ActorMixinRole {
    void setupExpectedFromMsgSpec(ExpectedMsgSpecHolder &m) {
        std::cout << "expect msg from: " << m.id();
        std::cout << " to: " << id();
        std::cout << " msgid: " << m.expectedMsgId_ << std::endl;
        //TODO: setup mock spec by mockcpp
    }

    void setupExpectedToMsgSpec(ExpectedMsgSpecHolder &m) {
        std::cout << "expect msg from: " << id();
        std::cout << " to: " << m.id();
        std::cout << " msgid: " << m.expectedMsgId_ << std::endl;
        //TODO: setup mock spec by mockcpp
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


typedef std::function<void(ActorId, ActorId, MsgId, void*, size_t)> SendMsgFunc;

struct MsgSender : ActorMixinRole {
    void sendMsg(MsgTempHolder& m) {
        assert((send_msg_func_ != nullptr) && "Should call init_send_msg_func before run tests.");
        send_msg_func_(id(), m.id(), m.msgId_, m.payload_, m.len_);
    }

    void receiveMsg(MsgTempHolder& m) {
        assert((send_msg_func_ != nullptr) && "Should call init_send_msg_func before run tests.");
        send_msg_func_(m.id(), id(), m.msgId_, m.payload_, m.len_);
    }

    static void init_send_msg_func(SendMsgFunc f) {
        send_msg_func_ = f;
    }

private:
    static SendMsgFunc send_msg_func_;
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
