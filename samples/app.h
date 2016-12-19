#ifndef MSGTEST_APP_H
#define MSGTEST_APP_H
#include <msgtest/msgtest.h>
USING_MSGTEST_NS

void msg_proc_of_alice(ActorId from, MsgId msgId, const void* payload, size_t len);
void msg_proc_of_bob(ActorId from, MsgId msgId, const void* payload, size_t len);
void msg_proc_of_clair(ActorId from, MsgId msgId, const void* payload, size_t len);
void msg_proc_of_dan(ActorId from, MsgId msgId, const void* payload, size_t len);

#endif //MSGTEST_APP_H
