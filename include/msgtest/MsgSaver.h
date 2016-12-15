#ifndef MSGTEST_MSGSAVER_H
#define MSGTEST_MSGSAVER_H
#include <msgtest/msgtest_ns.h>
#include <cstdlib>
#include <cassert>
#include <cstring>

MSGTEST_NS_START

    struct PayloadAddressTempHolder {
        bool operator()(void *payload) {
            payloadAddr_ = payload;
            return true;
        }
        static void* payloadAddr_;
    };

    struct MsgSaverBase {
        MsgSaverBase();
        ~MsgSaverBase();

        bool operator()(size_t len);

        void* payload_;
        size_t len_;

        //Mock predicate object will be copy construct and saved,
        //we need to pass the address of the payload_ into the copyed Saver,
        //then the original saver and the copyed saver both will see the same payload.
        void** payload_mem_addr_;
        size_t* len_mem_addr_;
    };

    template<typename T>
    struct MsgSaver : MsgSaverBase {
        T* operator->() {
            return static_cast<T*>(payload_);
        }
    };


    #define ___save_to(MSG_SAVER) checkWith(PayloadAddressTempHolder()), checkWith(MSG_SAVER)

MSGTEST_NS_END
#endif //MSGTEST_MSGSAVER_H
