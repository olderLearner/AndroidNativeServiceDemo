#define LOG_TAG "DemoService"
#define LOG_NDEBUG 0

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>

#include "DemoService.h"

using namespace android;
using namespace android::os;

int main(int argc, char **argv)
{
    (void*)&argc;
    (void*)argv;

    sp<IServiceManager> sm = defaultServiceManager();
    //ALOGD("ServiceManager pointer: %p, start native datacollector!", sm.get());
    DemoService::instantiate();
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}