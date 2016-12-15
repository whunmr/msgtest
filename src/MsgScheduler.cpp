#include <msgtest/MsgScheduler.h>
#include <cassert>

MSGTEST_NS_START

static ScheduleMsgFunc scheduleMsgFunc_;

void MsgScheduler::set_app_schedule_msg_func(ScheduleMsgFunc f) {
    scheduleMsgFunc_ = f;
}

void MsgScheduler::scheduleMsg(ActorId from, ActorId to, MsgId msgId, void *payload, size_t len) {
    assert((scheduleMsgFunc_ != nullptr) && "Should call MsgScheduler::set_app_schedule_msg_func before run tests.");
    scheduleMsgFunc_(from, to, msgId, payload, len);
}

MSGTEST_NS_END
