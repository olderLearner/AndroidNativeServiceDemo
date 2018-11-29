#define LOG_TAG "I-DemoService"
#define LOG_NDEBUG 0
#include <binder/Parcel.h>
#include <utils/Log.h>

#include "LogUtils.h"
#include "IDemoService.h"

namespace android {
namespace os {

enum {
    SEND = IBinder::FIRST_CALL_TRANSACTION,
    REGISTER_DATA_CALLBACK
};
// ---------------------------------------------------------
class BpDemoService : public BpInterface<IDemoService>
{
public:
    BpDemoService(const sp<IBinder>& impl)
        : BpInterface<IDemoService>(impl)
    {
        if (DEBUG) {
            ALOGD("%s Bp Enter", __FUNCTION__);
        }
    }

    virtual status_t send(int cmd, int subCmd)
    {
        if (DEBUG) {
            ALOGD("%s Bp Enter", __FUNCTION__);
        }

        Parcel data, reply;
        data.writeInterfaceToken(IDemoService::getInterfaceDescriptor());
        data.writeInt32(cmd);
        data.writeInt32(subCmd);
        status_t ret = remote()->transact(SEND, data, &reply);
        if (ret == NO_ERROR) {
            ret = (status_t)reply.readInt32();
        }
        return ret;
    }

    virtual void registerDataCallback(const sp<IDataCallback>& callback)
    {
        if (DEBUG) {
            ALOGD("%s Bp Enter", __FUNCTION__);
        }

        Parcel data, reply;
        data.writeInterfaceToken(IDemoService::getInterfaceDescriptor());
        //data.writeStrongBinder(IInterface::asBinder(callback));
        data.writeStrongBinder(callback->asBinder());
        remote()->transact(REGISTER_DATA_CALLBACK, data, &reply);
    }

};

IMPLEMENT_META_INTERFACE(DemoService, "von.IDemoService");

// ---------------------------------------------------------
status_t BnDemoService::onTransact(uint32_t code, const Parcel& data,
    Parcel* reply, uint32_t flags)
{
    if (DEBUG) {
        ALOGD("%s Bn_Enter, code %d", __FUNCTION__, code);
    }

    switch(code) {

        case SEND:{
            CHECK_INTERFACE(IDemoService, data, reply);
            int cmd = data.readInt32();
            int subCmd = data.readInt32();
            int ret= send(cmd, subCmd);
            if (reply != NULL) {
                reply->writeInt32(ret);
            }
            return NO_ERROR;
        } break;

        case REGISTER_DATA_CALLBACK: {
            CHECK_INTERFACE(IDemoService, data, reply);
            sp<IDataCallback> client = interface_cast<IDataCallback>(
            data.readStrongBinder());
            registerDataCallback(client);
            return NO_ERROR;
        } break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}
// ---------------------------------------------------------

}; // namespace os
}; // namespace android
