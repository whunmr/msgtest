#include <msgtest/MsgSaver.h>
#include <list>
#include <iostream>

MSGTEST_NS_START

    void* PayloadAddressTempHolder::payloadAddr_;

    ////////////////////////////////////////////////////////////////////////////
    namespace {
        std::list<void**> msg_saver_free_list_;
    }

    /*  Due to msg_interaction is actually an embedded struct,
     *  all variable it refered has to be static, including our MsgSaver.
     *  So we need free memory occupied by MsgSaver onTestEnd.
     *
     *   static MsgSaver<MsgPayload> rspMsg;
     *   msg_interaction {
     *       alice<<----bob(EV_BOB_RSP, ___save_to(rspMsg));
     *   } ___end;
     */
    void MsgSaverBase::freeMsgSaverMemoryOnTestEnd() {
        for (void** p : msg_saver_free_list_) {
            free(*p);
            *p = nullptr;
        }
        msg_saver_free_list_.clear();
    }

    ////////////////////////////////////////////////////////////////////////////
    MsgSaverBase::MsgSaverBase()
            : payload_(nullptr)
            , len_(0)
            , payload_mem_addr_(&payload_)
            , len_mem_addr_(&len_) {
        /**/
    }

    ////////////////////////////////////////////////////////////////////////////
    //Called by through ::mockcpp::checkWith( bool(*)(T) )
    bool MsgSaverBase::operator()(size_t len) {
        assert((*payload_mem_addr_ == nullptr) && "Can only save one message in one instance.");
        assert((PayloadAddressTempHolder::payloadAddr_ != nullptr) && "Should use checkWith(globalPayloadAddressTempHolder). to record msg addr first.");

        if (len > 0) {
            *payload_mem_addr_ = malloc(len);
            if (*payload_mem_addr_ != nullptr) {
                msg_saver_free_list_.push_back(payload_mem_addr_);
                memcpy(*payload_mem_addr_, PayloadAddressTempHolder::payloadAddr_, len);
                *len_mem_addr_ = len;
            }
        }
        return true;
    }


MSGTEST_NS_END
