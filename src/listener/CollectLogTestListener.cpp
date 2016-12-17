#include "msgtest/listener/CollectLogTestListener.h"
#include <msgtest/msgflow.h>

MSGTEST_NS_START

    namespace {
        LogTranslator *translator_;

        std::vector<std::string> logs;

        struct MsgTypeInfo {
            MsgTypeInfo(ActorId from, ActorId to, MsgId msgId, const std::string &name)
                    : from_(from), to_(to), msgId_(msgId), name_(name) {/**/}

            ActorId from_;
            ActorId to_;
            MsgId msgId_;
            std::string name_;
        };

        std::vector<MsgTypeInfo> msgInfos_;

        std::string typeNameOfMsg(ActorId from, ActorId to, MsgId msgId) {
            for (auto& info : msgInfos_) {
                if (info.from_ == from && info.to_ == to && info.msgId_ == msgId) {
                    return info.name_;
                }
            }
            return std::to_string(msgId);
        }

    }

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

    void CollectLogTestListener::setLogTranslator(LogTranslator &logTranslator) {
        translator_ = &logTranslator;
    }

    ////////////////////////////////////////////////////////////////////////////
    void CollectLogTestListener::addPayloadTypeInfo(ActorId from, ActorId to, MsgId msgId, const std::string &name) {
        MsgTypeInfo info(from, to, msgId, name);
        msgInfos_.push_back(info);
    }

    ////////////////////////////////////////////////////////////////////////////
    void g_collect_msg_log_func(ActorId from, ActorId to, MsgId msgId, const void *payload, size_t len) {
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
        ss << " " << typeNameOfMsg(from, to, msgId);

        logs.push_back(ss.str());
    }

MSGTEST_NS_END
