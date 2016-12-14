#ifndef MSGTEST_BASEACTOR_H
#define MSGTEST_BASEACTOR_H

#include <cassert>
#include <functional>
#include <msgtest/Typedefs.h>
#include <msgtest/msgtest_ns.h>

MSGTEST_NS_START

struct MsgTempHolder {
    MsgTempHolder() : msgid_(0), payload_(nullptr), len_(0) {/**/}

    void save(MsgId msgid, void* payload, size_t len) {
          msgid_ = msgid;
        payload_ = payload;
            len_ = len;
    }

    virtual ActorId id() const = 0;

    MsgId msgid_;
    void* payload_;
    size_t len_;
};

typedef std::function<void(ActorId, ActorId, MsgId, void*, size_t)> SendMsgFunc;

struct MsgSender {
    void sendMsg(MsgTempHolder& m) {
        assert((send_msg_func_ != nullptr) && "Should call init_send_msg_func before run tests.");
        send_msg_func_(id(), m.id(), m.msgid_, m.payload_, m.len_);
    }

    void receiveMsg(MsgTempHolder& m) {
        assert((send_msg_func_ != nullptr) && "Should call init_send_msg_func before run tests.");
        send_msg_func_(m.id(), id(), m.msgid_, m.payload_, m.len_);
    }

    static void init_send_msg_func(SendMsgFunc f) {
        send_msg_func_ = f;
    }

    virtual ActorId id() const = 0;

private:
    static SendMsgFunc send_msg_func_;
};

struct BaseActor : MsgTempHolder, MsgSender {
    BaseActor(ActorId actorId) : actorId_(actorId) {/**/}

    virtual ActorId id() const { return actorId_; }

private:
    ActorId actorId_;
};

MSGTEST_NS_END
#endif //MSGTEST_BASEACTOR_H
