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
        }
        return std::to_string(actorId);
    }

    virtual std::string msg2String(ActorId fromActorId, MsgId msgId) const {
        switch(msgId) {
            case EV_ALICE_REQ:            return "EV_ALICE_REQ";
            case EV_BOB_RSP:              return "EV_BOB_RSP";
            case EV_ALICE_ACK:            return "EV_ALICE_ACK";
            case EV_BOB_RELEASE_RESOURCE: return "EV_BOB_RELEASE_RESOURCE";
        }
        return std::to_string(msgId);
    }
};

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    MSGTEST_SET_SCHEDULE_MSG_FUNC(g_app_msg_loop);
    //MSGTEST_SET_MSG_TO_STRING_FUNC(g_msg_to_string_func);        //TODO:
    //MSGTEST_SET_ACTOR_TO_STRING_FUNC(g_actor_to_string_func);  //TODO:
    CollectLogTestListener::setLogTranslator(*(new MyAppLogTranslator));

    return RUN_ALL_TESTS();
}
