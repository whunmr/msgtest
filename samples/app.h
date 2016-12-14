#ifndef MSGTEST_APP_H
#define MSGTEST_APP_H
#include <msgtest/msgtest.h>
USING_MSGTEST_NS

void g_send_msg_func(ActorId from, ActorId to, MsgId msgId, void* payload, size_t len);

#endif //MSGTEST_APP_H
