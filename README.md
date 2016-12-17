# msgtest
Test framework for testing messaging interactions in Event Driven Architecture.

write tests like this:
```
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
    static MsgPayload payload;

    msg_interaction_ex {
            alice ---->bob(EV_ALICE_REQ, &payload);
            alice<<----bob(EV_BOB_RSP);
    } ___end;
}

TEST(msgtest, should_able_to__check_expected___ack_msg_from_bob____in_reverse_messaging_direction_of_DSL) {
    static MsgPayload payload;

    msg_interaction_ex {
            bob<---- alice(EV_ALICE_REQ, &payload);
            bob---->>alice(EV_BOB_RSP);
    } ___end;
}

TEST(msgtest, should_able_to__support__multiple__msg_interaction) {
    static MsgPayload payload;

    msg_interaction_ex {
            alice ---->bob(EV_ALICE_REQ, &payload);
            alice<<----bob(EV_BOB_RSP);
    } ___end;


    msg_interaction_ex {
            bob<---- alice(EV_ALICE_REQ, &payload);
            bob---->>alice(EV_BOB_RSP);
    } ___end;
}


TEST(msgtest, should_able_to__save_msg_payload___for_further_check_and_inspection) {
    static MsgSaver<MsgPayload> rspMsg;

    static MsgPayload payload;

    msg_interaction_ex {
            alice ---->bob(EV_ALICE_REQ, &payload);
            alice<<----bob(EV_BOB_RSP, ___save_to(rspMsg));
    } ___end;

    EXPECT_EQ(kfieldA_value_in_bob_to_alice_rsp, rspMsg->fieldA);
    EXPECT_EQ(kfieldB_value_in_bob_to_alice_rsp, rspMsg->fieldB);
    EXPECT_EQ(kfieldC_value_in_bob_to_alice_rsp, rspMsg->fieldC);
}

TEST(msgtest, should_able_to__check_schedule_order___of_expected_msgs) {
    static MsgSaver<MsgPayload> bob_to_alice_rsp;
    static MsgSaver<MsgPayload> alice_to_bob_ack;

    static MsgPayload payload;
    msg_interaction_ex {
            alice ---->bob(EV_ALICE_REQ, &payload);
            alice<<----bob(EV_BOB_RSP, ___save_to(bob_to_alice_rsp));
            msgtest_log("xxxxx");
            alice---->>bob(EV_ALICE_ACK, ___save_to(alice_to_bob_ack));
            msgtest_log("yyyyyy");
            alice<<----bob(EV_BOB_RELEASE_RESOURCE);
    } ___end;

    EXPECT_EQ(kfieldA_value_in_bob_to_alice_rsp, bob_to_alice_rsp->fieldA);
    EXPECT_EQ(kfieldA_value_in_alice_to_bob_ack, alice_to_bob_ack->fieldA);
}

```


by the way, the test log will show like the interaction diagram like this:

```
[==========] Running 8 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 8 tests from msgtest
[ RUN      ] msgtest.should_able_to_support_send_stub_msg__in__DSL_style


[       OK ] msgtest.should_able_to_support_send_stub_msg__in__DSL_style (1 ms)
[ RUN      ] msgtest.should_able_to__auto_detect_payload_len___according_payload_type


[       OK ] msgtest.should_able_to__auto_detect_payload_len___according_payload_type (0 ms)
[ RUN      ] msgtest.should_able_to__check_expected___ack_msg_from_bob
alice   bob
  |----->|     EV_ALICE_REQ              [1] 0x6fc3b8 8
  |<-----|     EV_BOB_RSP                [2] 0x7ffe6e40d8a0 8
  |----->|     EV_ALICE_ACK              [3] 0x7ffe6e40d830 8
  |<-----|     EV_BOB_RELEASE_RESOURCE   [4] 0x7ffe6e40d7c0 8

[       OK ] msgtest.should_able_to__check_expected___ack_msg_from_bob (1 ms)
[ RUN      ] msgtest.should_able_to__check_expected___ack_msg_from_bob____in_reverse_messaging_direction_of_DSL
alice   bob
  |----->|     EV_ALICE_REQ              [1] 0x6fc3c0 8
  |<-----|     EV_BOB_RSP                [2] 0x7ffe6e40d8a0 8
  |----->|     EV_ALICE_ACK              [3] 0x7ffe6e40d830 8
  |<-----|     EV_BOB_RELEASE_RESOURCE   [4] 0x7ffe6e40d7c0 8

[       OK ] msgtest.should_able_to__check_expected___ack_msg_from_bob____in_reverse_messaging_direction_of_DSL (0 ms)
[ RUN      ] msgtest.should_able_to__support__multiple__msg_interaction
alice   bob
  |----->|     EV_ALICE_REQ              [1] 0x6fc3c8 8
  |<-----|     EV_BOB_RSP                [2] 0x7ffe6e40d8a0 8
  |----->|     EV_ALICE_ACK              [3] 0x7ffe6e40d830 8
  |<-----|     EV_BOB_RELEASE_RESOURCE   [4] 0x7ffe6e40d7c0 8
  |----->|     EV_ALICE_REQ              [5] 0x6fc3c8 8
  |<-----|     EV_BOB_RSP                [6] 0x7ffe6e40d8a0 8
  |----->|     EV_ALICE_ACK              [7] 0x7ffe6e40d830 8
  |<-----|     EV_BOB_RELEASE_RESOURCE   [8] 0x7ffe6e40d7c0 8

[       OK ] msgtest.should_able_to__support__multiple__msg_interaction (0 ms)
[ RUN      ] msgtest.should_able_to__save_msg_payload___for_further_check_and_inspection
alice   bob
  |----->|     EV_ALICE_REQ              [1] 0x6fc408 8
  |<-----|     EV_BOB_RSP                [2] 0x7ffe6e40d820 8
  |----->|     EV_ALICE_ACK              [3] 0x7ffe6e40d7b0 8
  |<-----|     EV_BOB_RELEASE_RESOURCE   [4] 0x7ffe6e40d740 8

[       OK ] msgtest.should_able_to__save_msg_payload___for_further_check_and_inspection (0 ms)
[ RUN      ] msgtest.should_able_to__check_schedule_order___of_expected_msgs
alice   bob
  |----->|     EV_ALICE_REQ              [1] 0x6fc488 8
  |<-----|     EV_BOB_RSP                [2] 0x7ffe6e40d7e0 8
  |----->|     EV_ALICE_ACK              [3] 0x7ffe6e40d770 8
  |<-----|     EV_BOB_RELEASE_RESOURCE   [4] 0x7ffe6e40d700 8
[0] xxxxx
[0] yyyyyy
[4] xxxxx
[4] yyyyyy

[       OK ] msgtest.should_able_to__check_schedule_order___of_expected_msgs (1 ms)
[ RUN      ] msgtest.should_able_to__express__payload_struct_info___in_DSL


[       OK ] msgtest.should_able_to__express__payload_struct_info___in_DSL (0 ms)
[----------] 8 tests from msgtest (36 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test case ran. (36 ms total)
[  PASSED  ] 8 tests.
```

