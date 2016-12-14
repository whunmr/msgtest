#include <gtest/gtest.h>
//#include <mockcpp/mockcpp.hpp>
#include <msgtest/msgtest.h>
USING_MSGTEST_NS

#include "common/MsgPayload.h"
#include "common/MsgId.h"
#include "app_ids.h"

StubActor alice(id_of_alice);
UnderTestActor bob(id_of_bob);

TEST(msgtest, should_able_to_support_send_stub_msg__in__DSL_style) {
    MsgPayload payload;
    alice---->bob(EV_ALICE_REQ, &payload, sizeof(payload));
    alice<----bob(EV_ALICE_REQ, &payload, sizeof(payload));
}

TEST(msgtest, should_able_to___auto_detect_payload_len___according_payload_type) {
    MsgPayload payload;
    alice---->bob(EV_ALICE_REQ, &payload);
    alice<----bob(EV_ALICE_REQ, &payload);
}

TEST(msgtest, should_able_to__check_expected___ack_msg_from_bob){
    MsgPayload payload;
    alice---->bob(EV_ALICE_REQ, &payload);
    alice<<----bob(EV_BOB_RSP);
    alice---->>bob(EV_ALICE_ACK);
}

