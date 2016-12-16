#ifndef MSGTEST_TRACELOGTESTLISTENER_H
#define MSGTEST_TRACELOGTESTLISTENER_H
#include <gtest/gtest.h>
#include <msgtest/msgtest_ns.h>
MSGTEST_NS_START

class TraceLogTestListener : public ::testing::EmptyTestEventListener {
    virtual void OnTestStart(const ::testing::TestInfo& /*test_info*/) {
        std::cout << "OnTestStart" << std::endl;
    }

    virtual void OnTestEnd(const ::testing::TestInfo& /*test_info*/) {
        std::cout << "OnTestEnd" << std::endl;
    }

};

MSGTEST_NS_END
#endif //MSGTEST_TRACELOGTESTLISTENER_H
