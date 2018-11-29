#include <binder/Parcel.h>
#include <private/binder/Static.h>

#include "IDataCallback.h"

namespace android {
namespace os {

static void readByteArray(const Parcel& in, const uint8_t** data, size_t* length) {
    ssize_t slength = in.readInt32();
    if (slength > 0) {
        *data = reinterpret_cast<const uint8_t*>(in.readInplace(slength));
        if (*data) {
            *length = static_cast<size_t>(slength);
        } else {
            *length = 0;
        }
    } else {
        *data = NULL;
        *length = 0;
    }
}

class BpDataCallback : public BpInterface<IDataCallback>
{
public:
    explicit BpDataCallback(const sp<IBinder>& impl)
        : BpInterface<IDataCallback>(impl)
    {
    }

    virtual void onReceiveBytes(int32_t cmd, const uint8_t* bytes, size_t length) {
        Parcel data;
        data.writeInterfaceToken(IDataCallback::getInterfaceDescriptor());
        data.writeInt32(cmd);
        data.writeByteArray(length, bytes);
        remote()->transact(OP_ON_RECEIVE_BYTES, data, NULL, IBinder::FLAG_ONEWAY);
    }
};

IMPLEMENT_META_INTERFACE(DataCallback, "com.von.demoservice.IDataCallback");

status_t BnDataCallback::onTransact(
    uint32_t code, const Parcel& data, Parcel *reply, uint32_t flags)
{
    switch(code) {
    case OP_ON_RECEIVE_BYTES: {
        CHECK_INTERFACE(IDataCallback, data, reply);
        int32_t cmd = data.readInt32();
        const uint8_t* token_bytes = NULL;
        size_t size = 0;
        readByteArray(data, &token_bytes, &size);
        onReceiveBytes(cmd, token_bytes, size);
        if (reply != NULL) {
            reply->writeNoException();
        }
        return NO_ERROR;
    } break;
    default:
        return BBinder::onTransact(code, data, reply, flags);
    }
}

}; // namespace os
}; // namespace android
