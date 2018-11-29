LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_SRC_FILES += src/com/von/demoservice/IDataCallback.aidl


LOCAL_CERTIFICATE := platform

LOCAL_PROGUARD_ENABLED:= disabled

LOCAL_PACKAGE_NAME := DemoServiceTest

LOCAL_DEX_PREOPT := false

include $(BUILD_PACKAGE)
