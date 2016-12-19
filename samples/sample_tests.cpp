#include <gtest/gtest.h>
#include <mockcpp/mockcpp.hpp>
USING_MOCKCPP_NS

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

TEST(msgtest, should_able_to__auto_detect_payload_len___according_payload_type) {
    MsgPayload payload;
    alice---->bob(EV_ALICE_REQ, &payload);
    alice<----bob(EV_ALICE_REQ, &payload);
}

TEST(msgtest, should_able_to__check_expected___ack_msg_from_bob) {
    MsgPayload payload;

    msg_interaction(
            alice ---->bob(EV_ALICE_REQ, &payload);
            alice<<----bob(EV_BOB_RSP);
    );
}

TEST(msgtest, should_able_to__check_expected___ack_msg_from_bob____in_reverse_messaging_direction_of_DSL) {
    static MsgPayload payload;

    msg_interaction(
            bob<---- alice(EV_ALICE_REQ, &payload);
            bob---->>alice(EV_BOB_RSP);
    );
}

TEST(msgtest, should_able_to__support__multiple__msg_interaction) {
    MsgPayload payload;

    msg_interaction(
            alice ---->bob(EV_ALICE_REQ, &payload);
            alice<<----bob(EV_BOB_RSP);
    );


    msg_interaction(
            bob<---- alice(EV_ALICE_REQ, &payload);
            bob---->>alice(EV_BOB_RSP);
    );
}


TEST(msgtest, should_able_to__save_msg_payload___for_further_check_and_inspection) {
    MsgSaver<MsgPayloadRsp> rspMsg;

    MsgPayload payload;

    msg_interaction(
            alice ---->bob(EV_ALICE_REQ, &payload);
            alice<<----bob(EV_BOB_RSP, ___save_to(rspMsg));
    );

    EXPECT_EQ(kfieldA_value_in_bob_to_alice_rsp, rspMsg->fieldA);
    EXPECT_EQ(kfieldB_value_in_bob_to_alice_rsp, rspMsg->fieldB);
    EXPECT_EQ(kfieldC_value_in_bob_to_alice_rsp, rspMsg->fieldC);
}


TEST(msgtest, should_able_to__check_schedule_order___of_expected_msgs) {
    MsgSaver<MsgPayloadRsp> bob_to_alice_rsp;
    MsgSaver<MsgPayload> alice_to_bob_ack;

    MsgPayload payload;

    msg_interaction(
            alice ------>bob(EV_ALICE_REQ, &payload);
            alice<<------bob(EV_BOB_RSP             , ___save_to(bob_to_alice_rsp));
            alice------>>bob(EV_ALICE_ACK           , ___save_to(alice_to_bob_ack));
            alice<<------bob(EV_BOB_RELEASE_RESOURCE, ___type(MsgPayloadXXXXX));
    );

    EXPECT_EQ(kfieldA_value_in_bob_to_alice_rsp, bob_to_alice_rsp->fieldA);
    EXPECT_EQ(kfieldA_value_in_alice_to_bob_ack, alice_to_bob_ack->fieldA);
}

