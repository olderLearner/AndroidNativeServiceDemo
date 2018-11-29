LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    von_demoservice_server.cpp

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libutils \
    liblog \
    libbinder \
    libdemoservice

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../include
LOCAL_MODULE := demoserver

LOCAL_PROPRIETARY_MODULE := true
#LOCAL_INIT_RC := vendor.von.demoservice.rc
include $(BUILD_EXECUTABLE)