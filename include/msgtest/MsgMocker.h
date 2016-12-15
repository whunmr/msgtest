#ifndef MSGTEST_MSGMOCKER_H
#define MSGTEST_MSGMOCKER_H

#include <msgtest/Typedefs.h>
#include <msgtest/msgtest_ns.h>
#include <cstddef>
#include <mockcpp/Constraint.h>

MSGTEST_NS_START

    void g_msgtest_trace_msg_probe_func(ActorId from, ActorId to, MsgId, void*, size_t);

    struct MsgMocker {
        static void setupMsgMockSpec(ActorId from, ActorId to, MsgId msgId, mockcpp::Constraint *pConstraint,
                                            mockcpp::Constraint *pConstraint1);

        static void verifyMockSpec();
    };

MSGTEST_NS_END
#endif //MSGTEST_MSGMOCKER_H
