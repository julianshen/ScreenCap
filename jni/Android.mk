LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES:= \
    com_cust_android_screencap_ScreenCap.cpp

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libutils \
	libbinder \
	libskia \
	libui\
	libsurfaceflinger_client

LOCAL_C_INCLUDES += \
        external/skia/include/core \
        external/skia/include/effects \
        external/skia/include/images \
        external/skia/src/ports \
        external/skia/include/utils

LOCAL_MODULE := libscrcap
LOCAL_MODULE_TAGS := eng

include $(BUILD_SHARED_LIBRARY)
