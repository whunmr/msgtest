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

TEST(msgtest, should_able_to___auto_detect_payload_len___according_payload_type) {
    MsgPayload payload;
    alice---->bob(EV_ALICE_REQ, &payload);
    alice<----bob(EV_ALICE_REQ, &payload);
}

struct msgtest_fixture : ::testing::Test {
};

TEST_F(msgtest_fixture, should_able_to__check_expected___ack_msg_from_bob){
    static MsgPayload payload;

    struct MsgInteraction {
        static void exec() {
            alice ---->bob(EV_ALICE_REQ, &payload);
            alice<<----bob(EV_BOB_RSP);
        }

        static void setup_mocks___and___execute() {
            TestPhase::phase_ = TestPhase::SetupMockPhase;
            exec();
            MOCKER(g_msgtest_trace_msg_probe_func).stubs().with(any(), any(), any(), any(), any());

            TestPhase::phase_ = TestPhase::ExecuteMsgInteractionPhase;
            exec();
        }
    };

    MsgInteraction::setup_mocks___and___execute();

//    TestPhase::phase_ = TestPhase::SetupMockPhase;
//    alice ---->bob(EV_ALICE_REQ, &payload);
//    alice<<----bob(EV_BOB_RSP);
//
//    TestPhase::phase_ = TestPhase::ExecuteMsgInteractionPhase;
//    alice ---->bob(EV_ALICE_REQ, &payload);
//    alice<<----bob(EV_BOB_RSP);

}

