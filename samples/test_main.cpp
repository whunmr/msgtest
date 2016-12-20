#include <gtest/gtest.h>
#include <msgtest/msgtest.h>
#include "app.h"
#include "app_ids.h"
#include "common/MsgId.h"

USING_MSGTEST_NS


struct MyAppLogTranslator : LogTranslator {
    virtual std::string actor2String(ActorId actorId) const {
        switch(actorId) {
            case id_of_alice: return "alice";
            case id_of_bob  : return "bob";
            case id_of_clair: return "clair";
            case id_of_dan:   return "dan";
        }
        return std::to_string(actorId);
    }

    virtual std::string msg2String(ActorId fromActorId, MsgId msgId) const {
        return getString(msgId) + "=" + std::to_string(msgId);
    }

    std::string getString(MsgId msgId) const {
        switch(msgId) {
            case EV_ALICE_REQ:            return "EV_ALICE_REQ";
            case EV_BOB_RSP:              return "EV_BOB_RSP";
            case EV_ALICE_ACK:            return "EV_ALICE_ACK";
            case EV_BOB_RELEASE_RESOURCE: return "EV_BOB_RELEASE_RESOURCE";
            case EV_ALICE_TO_C_IND:       return "EV_ALICE_TO_C_IND";
            case EV_ALICE_TO_D_IND:       return "EV_ALICE_TO_D_IND";
            case EV_DAN_TO_ALICE:         return "EV_DAN_TO_ALICE";
            case EV_ALICE_REL_ACK:        return "EV_ALICE_REL_ACK";
        }
        return std::to_string(msgId);
    }
};

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::msgtest::InitMsgTest(new MyAppLogTranslator);
    return RUN_ALL_TESTS();
}
