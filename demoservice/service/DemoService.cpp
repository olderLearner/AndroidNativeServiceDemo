#define LOG_TAG "DemoService"
#define LOG_NDEBUG 0

#include <utils/Log.h>

#include "LogUtils.h"
#include "DemoService.h"

namespace android {
namespace os {

static bool mSendData = false;
DemoService::DemoService()
    : BnDemoService()
{
    if (DEBUG) {
        ALOGD("%s Enter", __FUNCTION__);
    }

    // init data structure
    mCallbackClients = new DefaultKeyedVector<pid_t, sp<CallbackClient> >();
}

DemoService::~DemoService()
{
    if (DEBUG) {
        ALOGD("%s Enter", __FUNCTION__);
    }

    if (mCallbackClients != NULL) {
        mCallbackClients->clear();
        delete mCallbackClients;
        mCallbackClients = NULL;
    }
}

status_t DemoService::send(int cmd, int subCmd)
{
    if (DEBUG) {
        ALOGD("%s Enter", __FUNCTION__);
    }

    ALOGI("cmd: 0x%x, subCmd %d", cmd, subCmd);
    mSendData = true;
    uint8_t ret[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    notifyCallbackClients(20, ret, 10);
    return NO_ERROR;
}

void DemoService::registerDataCallback(const sp<IDataCallback>& callback)
{
    if (DEBUG) {
        ALOGD("%s Enter", __FUNCTION__);
    }

    pid_t pid = IPCThreadState::self()->getCallingPid();
    if (mCallbackClients->indexOfKey(pid) < 0) {
        sp<CallbackClient> callbackClient = new CallbackClient(this, callback, pid);
        mCallbackClients->add(pid, callbackClient);
        sp<IBinder> binder = callback->asBinder();
        binder->linkToDeath(callbackClient);
    } else {
        ALOGI("client already registered! pid=%d", pid);
    }
}

status_t DemoService::onTransact(uint32_t code, const Parcel& data,
                                Parcel* reply, uint32_t flags)
{
    if (DEBUG) {
        ALOGD("Enter DemoService onTransact");
    }
    return BnDemoService::onTransact(code, data, reply, flags);
}

void DemoService::removeCallbackClient(pid_t pid)
{
    mCallbackClients->removeItem(pid);
}

void DemoService::notifyCallbackClients(int32_t cmd, const uint8_t* bytes, size_t length)
{
    if (DEBUG) {
        ALOGD("%s Enter", __FUNCTION__);
    }

    for (size_t i=0; i<mCallbackClients->size(); i++) {
        sp<IDataCallback> client = mCallbackClients->valueAt(i)->getCallback();
        client->onReceiveBytes(cmd, bytes, length);
    }
}

// ---------------------------------------------------------------------------------
// -----------------               INNER CLASS                ----------------------
// ---------------------------------------------------------------------------------
// CallbackClient
DemoService::CallbackClient::CallbackClient(
        const sp<DemoService>& collector, const sp<IDataCallback>& client, pid_t pid)
    :mService(collector), mPid(pid), mCallback(client)
{
    if (DEBUG) {
        ALOGD("%s Enter", __FUNCTION__);
    }
}

DemoService::CallbackClient::~CallbackClient()
{
}

void DemoService::CallbackClient::binderDied(const wp<IBinder>& who __unused)
{
    sp<CallbackClient> keep(this);
    mService->removeCallbackClient(mPid);
}
// ---------------------------------------------------------------------------------
// -----------------               INNER CLASS                ----------------------
// ---------------------------------------------------------------------------------

}; // namespace os
}; // namespace android
