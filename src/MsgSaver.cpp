#include <msgtest/MsgSaver.h>

MSGTEST_NS_START

    void* PayloadAddressTempHolder::payloadAddr_;

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
                memcpy(*payload_mem_addr_, PayloadAddressTempHolder::payloadAddr_, len);
                *len_mem_addr_ = len;
            }
        }
        return true;
    }

    void MsgSaverBase::OnTestEnd(const ::testing::TestInfo &test_info) {
        free(*payload_mem_addr_);
        *payload_mem_addr_ = nullptr;

        AutoRegTestListener::deRegister();
    }


MSGTEST_NS_END
