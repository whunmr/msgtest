#include "msgtest/listener/CollectLogTestListener.h"

MSGTEST_NS_START

    ////////////////////////////////////////////////////////////////////////////
    void CollectLogTestListener::OnTestStart(const ::testing::TestInfo &) {
    }

    void CollectLogTestListener::OnTestEnd(const ::testing::TestInfo &) {
    }

    namespace {
        LogTranslator *translator_;
    }

    void CollectLogTestListener::setLogTranslator(LogTranslator &logTranslator) {
        translator_ = &logTranslator;
    }

    void g_collect_msg_log_func(ActorId from, ActorId to, MsgId msgId, void *payload, size_t len) {
        std::stringstream ss;

        if (translator_ == nullptr) {
            ss << "Actor from: [" << from;
            ss << "] ----> [" << to;
            ss << "] msgid: " << msgId;
        } else {
            ss << "Actor from: [" << translator_->actor2String(from);
            ss << "] ----> [" << translator_->actor2String(to);
            ss << "] msgid: " << translator_->msg2String(from, msgId);
        }

        ss << " payload: " << payload;
        ss << " len: " << len;

        std::cout << ss.str() << std::endl;
    }

MSGTEST_NS_END
