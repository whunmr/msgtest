#include "app.h"

#include <iostream>
#include <msgtest/MsgMocker.h>
#include "app_ids.h"
#include "common/MsgId.h"
#include "common/MsgPayload.h"

////////////////////////////////////////////////////////////////////////////////
void msg_proc_of_bob(ActorId from, MsgId msgId, const void* payload, size_t len) {
    if (msgId == EV_ALICE_REQ) {
        MsgPayloadRsp payload1;
        payload1.fieldA = kfieldA_value_in_bob_to_alice_rsp;
        payload1.fieldB = kfieldB_value_in_bob_to_alice_rsp;
        payload1.fieldC = kfieldC_value_in_bob_to_alice_rsp;

        return g_app_msg_loop(id_of_bob, id_of_alice, EV_BOB_RSP, &payload1, sizeof(payload1));
    }

    if (msgId == EV_ALICE_ACK) {
        msgtest_log("Got ack from alice, ready to send release_resource indicator.");
        MsgPayload payload1;
        payload1.fieldA = kfieldA_value_in_bob_to_alice_release_resource;

        return g_app_msg_loop(id_of_bob, id_of_alice, EV_BOB_RELEASE_RESOURCE, &payload1, sizeof(payload1));
    }
}

////////////////////////////////////////////////////////////////////////////////
void msg_proc_of_alice(ActorId from, MsgId msgId, const void* payload, size_t len) {
    if (msgId == EV_BOB_RSP) {
        MsgPayload ack;
        ack.fieldA = kfieldA_value_in_alice_to_bob_ack;
        g_app_msg_loop(id_of_alice, id_of_bob, EV_ALICE_ACK, &ack, sizeof(ack));
    }

    if (msgId == EV_BOB_RELEASE_RESOURCE) {
        MsgPayloadRsp rsp;
        g_app_msg_loop(id_of_alice, id_of_clair, EV_ALICE_TO_C_IND, &rsp, sizeof(rsp));
        g_app_msg_loop(id_of_alice, id_of_dan, EV_ALICE_TO_D_IND, &rsp, sizeof(rsp));
    }
}

////////////////////////////////////////////////////////////////////////////////
void msg_proc_of_others(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len) {
}

////////////////////////////////////////////////////////////////////////////////
void g_app_msg_loop(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len) {
    MSGTEST_PROBE_MSG_SCHEDULE();

    if (to == id_of_bob) {
        msg_proc_of_bob(from, msgId, payload, len);
    } else if (to == id_of_alice) {
        msg_proc_of_alice(from, msgId, payload, len);
    } else {
        msg_proc_of_others(from , to, msgId, payload, len);
    }
}
