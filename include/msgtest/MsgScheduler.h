#ifndef MSGTEST_MSGHOOKS_H
#define MSGTEST_MSGHOOKS_H

#include <msgtest/Typedefs.h>
#include <msgtest/msgtest_ns.h>
#include <cstddef>
#include <functional>
MSGTEST_NS_START

typedef std::function<void(ActorId, ActorId, MsgId, void*, size_t)> ScheduleMsgFunc;

struct MsgScheduler {
    static void setScheduleMsgFunc(ScheduleMsgFunc);
    static void scheduleMsg(ActorId, ActorId, MsgId, void*, size_t);
};

MSGTEST_NS_END
#endif //MSGTEST_MSGHOOKS_H
