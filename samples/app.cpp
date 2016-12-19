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

        return msgtest_dispatch_test_msg(id_of_bob, id_of_alice, EV_BOB_RSP, &payload1, sizeof(payload1));
    }

    if (msgId == EV_ALICE_ACK) {
        msgtest_log("Got ack from alice, ready to send release_resource indicator.");
        MsgPayload payload1;
        payload1.fieldA = kfieldA_value_in_bob_to_alice_release_resource;

        return msgtest_dispatch_test_msg(id_of_bob, id_of_alice, EV_BOB_RELEASE_RESOURCE, &payload1, sizeof(payload1));
    }
}

////////////////////////////////////////////////////////////////////////////////
void msg_proc_of_alice(ActorId from, MsgId msgId, const void* payload, size_t len) {
    if (msgId == EV_BOB_RSP) {
        MsgPayload ack;
        ack.fieldA = kfieldA_value_in_alice_to_bob_ack;
        msgtest_dispatch_test_msg(id_of_alice, id_of_bob, EV_ALICE_ACK, &ack, sizeof(ack));
    }

    if (msgId == EV_BOB_RELEASE_RESOURCE) {
        MsgPayloadRsp rsp;
        msgtest_dispatch_test_msg(id_of_alice, id_of_clair, EV_ALICE_TO_C_IND, &rsp, sizeof(rsp));
        msgtest_dispatch_test_msg(id_of_alice, id_of_dan, EV_ALICE_TO_D_IND, &rsp, sizeof(rsp));
    }

    if (msgId == EV_DAN_TO_ALICE) {
        MsgPayloadRsp rsp;
        msgtest_dispatch_test_msg(id_of_alice, id_of_bob, EV_ALICE_REL_ACK, &rsp, sizeof(rsp));
    }
}

void msg_proc_of_clair(ActorId from, MsgId msgId, const void* payload, size_t len) {
}

void msg_proc_of_dan(ActorId from, MsgId msgId, const void* payload, size_t len) {
    if (msgId == EV_ALICE_TO_D_IND) {
        MsgPayload ack;
        ack.fieldA = kfieldA_value_in_alice_to_bob_ack;
        msgtest_dispatch_test_msg(id_of_dan, id_of_alice, EV_DAN_TO_ALICE, &ack, sizeof(ack));
    }
}

