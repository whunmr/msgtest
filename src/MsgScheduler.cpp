#include <msgtest/MsgScheduler.h>
#include <cassert>
#include <map>
#include <iostream>
#include <msgtest/listener/CollectLogTestListener.h>
#include <msgtest/MsgMocker.h>

MSGTEST_NS_START

    namespace {
        typedef std::map<ActorId, MsgProcFunc> MsgProcMap;

        MsgProcMap &getMsgProc() {
            static MsgProcMap msgProcMap_;
            return msgProcMap_;
        }
    }

    void msgtest_dispatch_test_msg(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len) {
        g_msgtest_trace_msg_probe_func(from, to, msgId, payload, len);
        g_collect_msg_log_func(from, to, msgId, payload, len);

        const auto &it = getMsgProc().find(to);
        if (it != getMsgProc().end()) {
            (it->second)(from, msgId, payload, len);
        }
    }

    void MsgScheduler::scheduleMsg(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len) {
        msgtest_dispatch_test_msg(from, to, msgId, payload, len);
    }

    void MsgScheduler::registerMsgProcFunc(ActorId actorId, MsgProcFunc f) {
        getMsgProc()[actorId] = f;
    }


MSGTEST_NS_END
