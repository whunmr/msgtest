#include "msgtest/listener/CollectLogTestListener.h"
#include <msgtest/msgflow.h>

MSGTEST_NS_START

    namespace {
        LogTranslator *translator_;

        std::vector<std::string> logs;

        enum MsgType {
            MT_STIMULATE_INPUT,
            MT_EXPECTED_RESPONSE
        };

        struct MsgInfo {
            MsgInfo(ActorId from, ActorId to, MsgId msgId, const std::string &name, MsgType msgType)
                    : from_(from), to_(to), msgId_(msgId), name_(name), msgType_(msgType) {/**/}

            ActorId from_;
            ActorId to_;
            MsgId msgId_;
            std::string name_;
            MsgType msgType_;
        };

        std::vector<MsgInfo> msgInfos_;

        std::string payloadTypeOfMsg(ActorId from, ActorId to, MsgId msgId) {
            for (auto& info : msgInfos_) {
                if (info.from_ == from && info.to_ == to && info.msgId_ == msgId) {
                    return info.name_;
                }
            }
            return "";
        }

        std::string typeOfMsg(ActorId from, ActorId to, MsgId msgId) {
            for (auto& info : msgInfos_) {
                if (info.from_ == from && info.to_ == to && info.msgId_ == msgId) {
                    if (info.msgType_ == MT_STIMULATE_INPUT) {
                        return "<input>";
                    } else if (info.msgType_ == MT_EXPECTED_RESPONSE) {
                        return "<expected>";
                    }
                }
            }
            return "<not_care>";
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    void msgtest_log(const std::string &log) {
        logs.push_back(log);
    }

    ////////////////////////////////////////////////////////////////////////////
    void CollectLogTestListener::OnTestStart(const ::testing::TestInfo &) {
        logs.push_back("#!MF:regex:.*\\[(\\w+)\\].*---->.*\\[(\\w+)\\] (.+? *) <(.*?)> (.*)"
                       ", #!MF:reformat_to:src:@1, dst:@2, msg_id:@3, msg_type:@4, extra_info:@5");
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
    void CollectLogTestListener::addStimulateMsgInfo(ActorId from, ActorId to, MsgId msgId, const std::string &name) {
        MsgInfo info(from, to, msgId, name, MT_STIMULATE_INPUT);
        msgInfos_.push_back(info);
    }

    void CollectLogTestListener::addExpectedMsgInfo(ActorId from, ActorId to, MsgId msgId, const std::string &name) {
        MsgInfo info(from, to, msgId, name, MT_EXPECTED_RESPONSE);
        msgInfos_.push_back(info);
    }

    ////////////////////////////////////////////////////////////////////////////
    std::string payload_content(const unsigned char* payload, size_t len) {
        std::stringstream ss;
        ss << std::hex;
        for (int i = 0; i < len; ++i) {
            if (i % 2 == 0) ss << " ";
            ss << std::setfill('0') << std::setw(2) << (int)payload[i];
        }
        return ss.str();
    }

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

        ss << " " << typeOfMsg(from, to, msgId);
        ss << payload_content((const unsigned char*)payload, std::min(8, (int)len));
        ss << " len:" << std::setfill('0') << std::setw(2) << len;
        ss << " " << payloadTypeOfMsg(from, to, msgId);

        logs.push_back(ss.str());
    }



MSGTEST_NS_END
