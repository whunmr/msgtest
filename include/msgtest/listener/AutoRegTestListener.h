#ifndef MSGTEST_AUTOREGISTERONCONSTRUCTIONTESTLISTENER_H
#define MSGTEST_AUTOREGISTERONCONSTRUCTIONTESTLISTENER_H

#include <gtest/gtest.h>
#include <msgtest/msgtest_ns.h>

MSGTEST_NS_START

    struct AutoRegTestListener : public ::testing::EmptyTestEventListener {
        AutoRegTestListener();
        void deRegister();
    };

MSGTEST_NS_END
#endif //MSGTEST_AUTOREGISTERONCONSTRUCTIONTESTLISTENER_H
