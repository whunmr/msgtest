#include <msgtest/MsgSaver.h>

MSGTEST_NS_START

    const void* PayloadAddressTempHolder::payloadAddr_;

    ////////////////////////////////////////////////////////////////////////////
    MsgSaverBase::MsgSaverBase()
            : payload_(nullptr)
            , len_(0)
            , payload_mem_addr_(&payload_)
            , len_mem_addr_(&len_) {
        /**/
    }

    MsgSaverBase::~MsgSaverBase() {
        //Mock predicate object will be copy construct and saved,
        //we need to pass the address of the payload_ into the copyed Saver,
        //then the original saver and the copyed saver both will see the same payload.
        bool isCopyConstructedPredicate = *payload_mem_addr_ != &payload_;

        if ( ! isCopyConstructedPredicate) {
            free(*payload_mem_addr_);
            *payload_mem_addr_ = nullptr;
        }
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

MSGTEST_NS_END
