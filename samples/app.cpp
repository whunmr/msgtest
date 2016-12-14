#include "app.h"

#include <iostream>
#include "app_ids.h"
#include "common/MsgId.h"
#include "common/MsgPayload.h"

////////////////////////////////////////////////////////////////////////////////
void log_msg(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len) {
    std::__1::cout << "Actor from: " << from;
    std::__1::cout << " ----> " << to;
    std::__1::cout << " msgid: " << msgId;
    std::__1::cout << " payload: " << payload;
    std::__1::cout << " len: " << len << std::__1::endl;
}

////////////////////////////////////////////////////////////////////////////////
void send_rsp_msg_to_alice() {
    MsgPayload payload;
    g_send_msg_func(id_of_bob, id_of_alice, EV_BOB_RSP, &payload, sizeof(payload));
}

void msg_proc_of_bob(ActorId from, MsgId msgId, void* payload, size_t len) {
    log_msg(from, id_of_bob, msgId, payload, len);

    send_rsp_msg_to_alice();
}

////////////////////////////////////////////////////////////////////////////////
void msg_proc_of_others(ActorId from, ActorId to, MsgId msgId, void* payload, size_t len) {
    log_msg(from, to, msgId, payload, len);
}

////////////////////////////////////////////////////////////////////////////////
void g_send_msg_func(ActorId from, ActorId to, MsgId msgId, void* payload, size_t len) {
    if (to == id_of_bob) {
        msg_proc_of_bob(from, msgId, payload, len);
    } else {
        msg_proc_of_others(from , to, msgId, payload, len);
    }
}

