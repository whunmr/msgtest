#ifndef MSGTEST_MSGPAYLOAD_H_H
#define MSGTEST_MSGPAYLOAD_H_H

struct MsgPayload {
    MsgPayload() : fieldA(0), fieldB(0), fieldC(0) {}

    int fieldA;
    short fieldB;
    char fieldC;
};

struct MsgPayloadRsp : MsgPayload {
    MsgPayloadRsp() : fieldD(0) {}
    int fieldD;
};

const int kfieldA_value_in_bob_to_alice_rsp = 10;
const short kfieldB_value_in_bob_to_alice_rsp = 11;
const char kfieldC_value_in_bob_to_alice_rsp = 12;

const int kfieldA_value_in_alice_to_bob_ack = 13;

const int kfieldA_value_in_bob_to_alice_release_resource = 14;

#endif //MSGTEST_MSGPAYLOAD_H_H
