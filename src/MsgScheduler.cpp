#include <msgtest/MsgScheduler.h>
#include <cassert>
#include <map>
#include <iostream>
#include <msgtest/listener/CollectLogTestListener.h>
#include <msgtest/MsgMocker.h>
#include <cstring>
#include <list>
#include <memory>

MSGTEST_NS_START

    namespace {
        typedef std::map<ActorId, MsgProcFunc> MsgProcMap;

        MsgProcMap &getMsgProc() {
            static MsgProcMap msgProcMap_;
            return msgProcMap_;
        }
    }

    struct MsgInfo {
        MsgInfo(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len)
            : from_(from), to_(to), msgId_(msgId), len_(len), payload_(malloc(len), ::free) {
            memcpy(payload_.get(), payload, len);
        }
        ActorId from_;
        ActorId to_;
        MsgId msgId_;
        size_t len_;
        std::shared_ptr<void> payload_;
    };

    std::list<MsgInfo> msgQ;

    void call_msg_proc(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len) {
        g_msgtest_trace_msg_probe_func(from, to, msgId, payload, len);
        g_collect_msg_log_func(from, to, msgId, payload, len);

        const auto &it = getMsgProc().find(to);
        if (it != getMsgProc().end()) {
            (it->second)(from, msgId, payload, len);
        }
    }

    void msgtest_dispatch_test_msg(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len) {
        MsgInfo msg = MsgInfo(from, to, msgId, payload, len);
        msgQ.push_back(msg);
    }

    void MsgScheduler::procAllBufferedMsg() {
        while (!msgQ.empty()) {
            const MsgInfo& msg = msgQ.front();
            call_msg_proc(msg.from_, msg.to_, msg.msgId_, msg.payload_.get(), msg.len_);
            msgQ.pop_front();
        }
    }

    void MsgScheduler::scheduleMsg(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len) {
        msgtest_dispatch_test_msg(from, to, msgId, payload, len);
        procAllBufferedMsg();
    }

    void MsgScheduler::registerMsgProcFunc(ActorId actorId, MsgProcFunc f) {
        getMsgProc()[actorId] = f;
    }


MSGTEST_NS_END
