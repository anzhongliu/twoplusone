LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/CardSprite.cpp \
                   ../../Classes/GlobalString.cpp \
                   ../../Classes/MainScene.cpp \
                   ../../Classes/Config.cpp \
                   ../../Classes/MenuScene.cpp \
                   ../../Classes/OverScene.cpp \
                   ../../Classes/StartScene.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
