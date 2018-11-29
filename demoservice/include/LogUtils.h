#ifndef MYAPPLICATION_LOGUTILS_H
#define MYAPPLICATION_LOGUTILS_H

#include <cutils/properties.h>

namespace android {
namespace os {

static bool getProp(const char* prop) {
    char value[PROPERTY_VALUE_MAX] = { '\0' };
    //return (property_get(prop, value, "0") > 0) && (atoi(value) == 1);
    return true;
}

// debug flag
static const bool DEBUG = false || getProp("persist.demoservice.log");

}
}
#endif //MYAPPLICATION_LOGUTILS_H
