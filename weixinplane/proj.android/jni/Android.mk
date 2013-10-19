LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/BulletLayer.cpp \
				   ../../Classes/Enemy1Layer.cpp \
				   ../../Classes/Enemy1Sprite.cpp \
				   ../../Classes/Enemy2Layer.cpp \
				   ../../Classes/Enemy3Layer.cpp \
				   ../../Classes/GameLayer.cpp \
				   ../../Classes/GameScene.cpp \
				   ../../Classes/PlaneLayer.cpp \
				   ../../Classes/WelcomeLayer.cpp \
				   ../../Classes/WelcomeScene.cpp \
				   ../../Classes/GameOverLayer.cpp \
				   ../../Classes/GameOverScene.cpp \
				   ../../Classes/ContronLayer.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
