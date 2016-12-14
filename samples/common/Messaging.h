#ifndef MSGTEST_MESSAGING_H
#define MSGTEST_MESSAGING_H

#include <iostream>

#include <msgtest/msgtest.h>
USING_MSGTEST_NS

void g_send_msg_func(ActorId from, ActorId to, MsgId msgId, void* payload, size_t len) {
    std::cout << "Actor from: " << from << std::endl;
    std::cout << "Actor to: " << to << std::endl;
    std::cout << "msgid: " << msgId << std::endl;
    std::cout << "payload: " << payload << std::endl;
    std::cout << "len: " << len << std::endl << std::endl;
}

#endif //MSGTEST_MESSAGING_H
