#ifndef ANDROID_DEMO_SERVICE_H
#define ANDROID_DEMO_SERVICE_H

#include <binder/Parcel.h>
#include <binder/BinderService.h>

#include <utils/KeyedVector.h>
#include "IDemoService.h"

namespace android {
namespace os {

class DemoService :
    public BinderService<DemoService>,
    public BnDemoService
{
    friend class BinderService<DemoService>;
public:

    static const char* getServiceName() { return "von.demoservice";}

    DemoService();
    virtual ~DemoService();

    virtual status_t send(int cmd, int subCmd);
    virtual void registerDataCallback(const sp<IDataCallback>& callback);

    virtual status_t onTransact(uint32_t code, const Parcel& data,
                                Parcel* reply, uint32_t flags);
private:
    void removeCallbackClient(pid_t pid);
    void notifyCallbackClients(int32_t cmd, const uint8_t* bytes, size_t length);

    class CallbackClient : public IBinder::DeathRecipient {
    public:
        CallbackClient(const sp<DemoService>& service,
            const sp<IDataCallback>& client, pid_t pid);
        virtual ~CallbackClient();
        const sp<IDataCallback> getCallback() { return mCallback;}
        virtual void binderDied(const wp<IBinder>& who);
    private:
        const sp<DemoService> mService;
        const pid_t mPid;
        const sp<IDataCallback> mCallback;
    };

    DefaultKeyedVector<pid_t, sp<CallbackClient> >* mCallbackClients;
};

}; // namespace os
}; // namespace android

#endif // ANDROID_DEMO_SERVICE_H
