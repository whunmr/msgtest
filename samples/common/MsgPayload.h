#ifndef MSGTEST_MSGPAYLOAD_H_H
#define MSGTEST_MSGPAYLOAD_H_H

struct MsgPayload {
    int fieldA;
    short fieldB;
    char fieldC;
};

const int kfieldA_value_in_bob_to_alice_rsp = 999;
const short kfieldB_value_in_bob_to_alice_rsp = 1000;
const char kfieldC_value_in_bob_to_alice_rsp = 88;

#endif //MSGTEST_MSGPAYLOAD_H_H
