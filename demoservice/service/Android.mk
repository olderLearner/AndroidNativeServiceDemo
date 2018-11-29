LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_SRC_FILES := \
    IDemoService.cpp \
    DemoService.cpp \
    IDataCallback.cpp

LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := \
    libutils \
    libcutils \
    liblog \
    libbinder

LOACL_CLANG := true
LOCAL_MODULE := libdemoservice

LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_SHARED_LIBRARY)
