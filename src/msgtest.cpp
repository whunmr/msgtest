#include <msgtest/msgtest.h>

MSGTEST_NS_START

    void InitMsgTest(const LogTranslator* logTranslator) {
        ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

        listeners.Append(new VerifyMockTestListener);

        assert((logTranslator != nullptr) && "logTranslator can not be null.");
        CollectLogTestListener::setLogTranslator(*logTranslator);
        listeners.Append(new CollectLogTestListener);
    }

MSGTEST_NS_END

