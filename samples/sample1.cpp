#include <gtest/gtest.h>
#include <msgtest/msgtest.h>
USING_MSGTEST_NS

#include "common/MsgPayload.h"
#include "common/MsgId.h"

const ActorId id_of_alice = 1;
const ActorId id_of_bob = 2;

StubActor alice(id_of_alice);
UnderTestActor bob(id_of_bob);

TEST(msgtest, should_support_send_msg__in__DSL_style) {
    MsgPayload payload;

    alice---->bob(EV_ALICE_REQ, &payload);
    alice---->bob(EV_ALICE_REQ, &payload, sizeof(payload));
    alice<----bob(EV_ALICE_REQ, &payload);
    alice<----bob(EV_ALICE_REQ, &payload, sizeof(payload));
}

