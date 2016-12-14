#ifndef MSGTEST_STUBACTOR_H
#define MSGTEST_STUBACTOR_H

#include <msgtest/DSLActor.h>
#include <msgtest/BaseActor.h>
#include <msgtest/msgtest_ns.h>

MSGTEST_NS_START

struct StubActor : BaseActor, DSLActor<StubActor> {
    StubActor(ActorId actorId);
};

MSGTEST_NS_END

#endif //MSGTEST_STUBACTOR_H
