#ifndef MSGTEST_MSGTEST_H_H
#define MSGTEST_MSGTEST_H_H

#include <msgtest/Typedefs.h>
#include <msgtest/StubActor.h>
#include <msgtest/MsgInteraction.h>
#include <msgtest/MsgSaver.h>
#include <msgtest/listener/VerifyMockTestListener.h>
#include <msgtest/listener/CollectLogTestListener.h>


#define ___type(expected_msg_type) #expected_msg_type


MSGTEST_NS_START

    void InitMsgTest(const LogTranslator*);

MSGTEST_NS_END
#endif //MSGTEST_MSGTEST_H_H
