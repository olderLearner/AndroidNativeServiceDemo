#ifndef ANDROID_IDEMO_SERVICE_H
#define ANDROID_IDEMO_SERVICE_H

#include <binder/IInterface.h>
#include <utils/String8.h>

#include "IDataCallback.h"

namespace android {
namespace os {

class IDemoService : public IInterface
{
public:
    DECLARE_META_INTERFACE(DemoService);
    virtual status_t send(int cmd, int subCmd) = 0;
    virtual void registerDataCallback(const sp<IDataCallback>& callback) = 0;
};

class BnDemoService : public BnInterface<IDemoService>
{
public:
    virtual status_t onTransact(uint32_t code,
                                const Parcel& data,
                                Parcel* reply,
                                uint32_t flags = 0);
};

}; // namespace os
}; // namespace android

#endif // ANDROID_IDEMO_SERVICE_H