#include "msgtest/listener/CollectLogTestListener.h"
#include <msgtest/msgflow.h>

MSGTEST_NS_START

    std::vector<std::string> logs;

    ////////////////////////////////////////////////////////////////////////////
    void msgtest_log(const std::string &log) {
        logs.push_back(log);
    }

    ////////////////////////////////////////////////////////////////////////////
    void CollectLogTestListener::OnTestStart(const ::testing::TestInfo &) {
        logs.push_back("#!MF:regex:.*\\[(\\w+)\\].*---->.*\\[(\\w+)\\] (.+? *) (.*)"
                       ", #!MF:reformat_to:src:@1, dst:@2, msg_id:@3, extra_info:@4");
        logs.push_back("#!MF:main_actor:bob");
        logs.push_back("#!MF:unknwn_msg_as_extra_info:");
        logs.push_back("#!MF:draw_from_right:");
    }

    void CollectLogTestListener::OnTestEnd(const ::testing::TestInfo &) {
        std::cout << draw_msgflow(logs) << std::endl;
        logs.clear();
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
            ss << "[" << from;
            ss << "] ----> [" << to;
            ss << "] " << msgId;
        } else {
            ss << "[" << translator_->actor2String(from);
            ss << "] ----> [" << translator_->actor2String(to);
            ss << "] " << translator_->msg2String(from, msgId);
        }

        ss << " " << payload;
        ss << " " << len;

        logs.push_back(ss.str());
    }

MSGTEST_NS_END
