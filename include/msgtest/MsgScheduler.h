#ifndef MSGTEST_MSGHOOKS_H
#define MSGTEST_MSGHOOKS_H

#include <msgtest/Typedefs.h>
#include <msgtest/msgtest_ns.h>
#include <cstddef>
#include <functional>

MSGTEST_NS_START

    void msgtest_dispatch_test_msg(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len);

    typedef std::function<void(ActorId, ActorId, MsgId, const void *, size_t)> ScheduleMsgFunc;
    typedef std::function<void(ActorId from, MsgId, const void *, size_t)> MsgProcFunc;

    struct MsgScheduler {
        static void registerMsgProcFunc(ActorId actorId, MsgProcFunc f);

        static void scheduleMsg(ActorId, ActorId, MsgId, const void *, size_t);

        static void procAllBufferedMsg();
    };

MSGTEST_NS_END
#endif //MSGTEST_MSGHOOKS_H
