# msgtest
Test framework for testing messaging interactions in Event Driven Architecture.

write tests like this:
```
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



TEST(msgtest, should_able_to__check_schedule_order___of_expected_msgs____in_paratheses_style) {
    MsgSaver<MsgPayloadRsp> bob_to_alice_rsp;
    MsgSaver<MsgPayload> alice_to_bob_ack;

    MsgPayload payload;

    msg_interaction(
            alice ---->bob(EV_ALICE_REQ, &payload);
            alice<<----bob(EV_BOB_RSP             , ___save_to(bob_to_alice_rsp));
            alice---->>bob(EV_ALICE_ACK           , ___save_to(alice_to_bob_ack));
            alice<<----bob(EV_BOB_RELEASE_RESOURCE, ___type(MsgPayloadXXXXX));
    );

    EXPECT_EQ(kfieldA_value_in_bob_to_alice_rsp, bob_to_alice_rsp->fieldA);
    EXPECT_EQ(kfieldA_value_in_alice_to_bob_ack, alice_to_bob_ack->fieldA);
}


TEST(msgtest, xx_should_able_to__express__payload_struct_info___in_DSL) {
    MsgPayload payload;
    alice<----bob(EV_ALICE_REQ, &payload);
}
```


by the way, the test log will show like the interaction diagram like this:

```
[==========] Running 8 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 8 tests from msgtest
[ RUN      ] msgtest.should_able_to_support_send_stub_msg__in__DSL_style


[       OK ] msgtest.should_able_to_support_send_stub_msg__in__DSL_style (0 ms)
[ RUN      ] msgtest.should_able_to__auto_detect_payload_len___according_payload_type


[       OK ] msgtest.should_able_to__auto_detect_payload_len___according_payload_type (0 ms)
[ RUN      ] msgtest.should_able_to__check_expected___ack_msg_from_bob
dan   clair   alice   bob
 |      |       |----->|     EV_ALICE_REQ              [1] 0000 0000 0000 0000 len:08 MsgPayload
 |      |       |<-----|     EV_BOB_RSP                [2] 0a00 0000 0b00 0c00 len:12
 |      |       |----->|     EV_ALICE_ACK              [3] 0d00 0000 0000 0000 len:08
 |      |       |<-----|     EV_BOB_RELEASE_RESOURCE   [4] 0e00 0000 0000 0000 len:08
 |      |<------|      |     EV_ALICE_TO_C_IND         [5] 0000 0000 0000 0000 len:12
 |<-------------|      |     EV_ALICE_TO_D_IND         [6] 0000 0000 0000 0000 len:12
[3] Got ack from alice, ready to send release_resource indicator.

[       OK ] msgtest.should_able_to__check_expected___ack_msg_from_bob (1 ms)
[ RUN      ] msgtest.should_able_to__check_expected___ack_msg_from_bob____in_reverse_messaging_direction_of_DSL
dan   clair   alice   bob
 |      |       |----->|     EV_ALICE_REQ              [1] 0000 0000 0000 0000 len:08 MsgPayload
 |      |       |<-----|     EV_BOB_RSP                [2] 0a00 0000 0b00 0c00 len:12
 |      |       |----->|     EV_ALICE_ACK              [3] 0d00 0000 0000 0000 len:08
 |      |       |<-----|     EV_BOB_RELEASE_RESOURCE   [4] 0e00 0000 0000 0000 len:08
 |      |<------|      |     EV_ALICE_TO_C_IND         [5] 0000 0000 0000 0000 len:12
 |<-------------|      |     EV_ALICE_TO_D_IND         [6] 0000 0000 0000 0000 len:12
[3] Got ack from alice, ready to send release_resource indicator.

[       OK ] msgtest.should_able_to__check_expected___ack_msg_from_bob____in_reverse_messaging_direction_of_DSL (0 ms)
[ RUN      ] msgtest.should_able_to__support__multiple__msg_interaction
dan   clair   alice   bob
 |      |       |----->|     EV_ALICE_REQ              [1] 0000 0000 0000 0000 len:08 MsgPayload
 |      |       |<-----|     EV_BOB_RSP                [2] 0a00 0000 0b00 0c00 len:12
 |      |       |----->|     EV_ALICE_ACK              [3] 0d00 0000 0000 0000 len:08
 |      |       |<-----|     EV_BOB_RELEASE_RESOURCE   [4] 0e00 0000 0000 0000 len:08
 |      |<------|      |     EV_ALICE_TO_C_IND         [5] 0000 0000 0000 0000 len:12
 |<-------------|      |     EV_ALICE_TO_D_IND         [6] 0000 0000 0000 0000 len:12
 |      |       |----->|     EV_ALICE_REQ              [7] 0000 0000 0000 0000 len:08 MsgPayload
 |      |       |<-----|     EV_BOB_RSP                [8] 0a00 0000 0b00 0c00 len:12
 |      |       |----->|     EV_ALICE_ACK              [9] 0d00 0000 0000 0000 len:08
 |      |       |<-----|     EV_BOB_RELEASE_RESOURCE   [10] 0e00 0000 0000 0000 len:08
 |      |<------|      |     EV_ALICE_TO_C_IND         [11] 0000 0000 0000 0000 len:12
 |<-------------|      |     EV_ALICE_TO_D_IND         [12] 0000 0000 0000 0000 len:12
[3] Got ack from alice, ready to send release_resource indicator.
[9] Got ack from alice, ready to send release_resource indicator.

[       OK ] msgtest.should_able_to__support__multiple__msg_interaction (0 ms)
[ RUN      ] msgtest.should_able_to__save_msg_payload___for_further_check_and_inspection
dan   clair   alice   bob
 |      |       |----->|     EV_ALICE_REQ              [1] 0000 0000 0000 0000 len:08 MsgPayload
 |      |       |<-----|     EV_BOB_RSP                [2] 0a00 0000 0b00 0c00 len:12
 |      |       |----->|     EV_ALICE_ACK              [3] 0d00 0000 0000 0000 len:08
 |      |       |<-----|     EV_BOB_RELEASE_RESOURCE   [4] 0e00 0000 0000 0000 len:08
 |      |<------|      |     EV_ALICE_TO_C_IND         [5] 0000 0000 0000 0000 len:12
 |<-------------|      |     EV_ALICE_TO_D_IND         [6] 0000 0000 0000 0000 len:12
[3] Got ack from alice, ready to send release_resource indicator.

[       OK ] msgtest.should_able_to__save_msg_payload___for_further_check_and_inspection (0 ms)
[ RUN      ] msgtest.should_able_to__check_schedule_order___of_expected_msgs____in_paratheses_style
dan   clair   alice   bob
 |      |       |----->|     EV_ALICE_REQ              [1] 0000 0000 0000 0000 len:08 MsgPayload
 |      |       |<-----|     EV_BOB_RSP                [2] 0a00 0000 0b00 0c00 len:12
 |      |       |----->|     EV_ALICE_ACK              [3] 0d00 0000 0000 0000 len:08 MsgPayload
 |      |       |<-----|     EV_BOB_RELEASE_RESOURCE   [4] 0e00 0000 0000 0000 len:08 MsgPayloadXXXXX
 |      |<------|      |     EV_ALICE_TO_C_IND         [5] 0000 0000 0000 0000 len:12
 |<-------------|      |     EV_ALICE_TO_D_IND         [6] 0000 0000 0000 0000 len:12
[3] Got ack from alice, ready to send release_resource indicator.

[       OK ] msgtest.should_able_to__check_schedule_order___of_expected_msgs____in_paratheses_style (1 ms)
[ RUN      ] msgtest.xx_should_able_to__express__payload_struct_info___in_DSL
alice   bob
  |<-----|     EV_ALICE_REQ   [1] 0000 0000 0000 0000 len:08 MsgPayload

[       OK ] msgtest.xx_should_able_to__express__payload_struct_info___in_DSL (0 ms)
[----------] 8 tests from msgtest (39 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test case ran. (39 ms total)
[  PASSED  ] 8 tests.
```

