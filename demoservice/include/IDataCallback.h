#ifndef ANDROID_IDATA_CALLBACK_H
#define ANDROID_IDATA_CALLBACK_H

#include <binder/IInterface.h>

namespace android{
namespace os{

class IDataCallback : public IInterface
{
public:
    DECLARE_META_INTERFACE(DataCallback)

    virtual void onReceiveBytes(int32_t cmd, const uint8_t* bytes, size_t length) = 0;

    enum {
        OP_ON_RECEIVE_BYTES = IBinder::FIRST_CALL_TRANSACTION
    };
};

class BnDataCallback : public BnInterface<IDataCallback>
{
public:
    virtual status_t onTransact(uint32_t code,
                                const Parcel& data,
                                Parcel *reply,
                                uint32_t flags = 0);
};

}; // namespace os
}; // namespace android

#endif // ANDROID_IDATA_CALLBACK_H
