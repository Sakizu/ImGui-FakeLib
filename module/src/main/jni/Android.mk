LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# ============================================================================#
LOCAL_MODULE            := libdobby
LOCAL_SRC_FILES         := Dobby/libraries/$(TARGET_ARCH_ABI)/libdobby.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/Dobby/
include $(PREBUILT_STATIC_LIBRARY)

# ============================================================================#



include $(CLEAR_VARS)

LOCAL_MODULE            := unity


LOCAL_CFLAGS            := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS            += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS          := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS          += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS           += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE          := arm
LOCAL_LDLIBS            := -llog -landroid -lEGL -lGLESv3 -lGLESv2 -lGLESv1_CM -lz

LOCAL_C_INCLUDES        += $(LOCAL_PATH)
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/xdl
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/xdl/include
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/KittyMemory
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/imgui
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/imgui/backends
LOCAL_C_INCLUDES        += $(LOCAL_PATH)/Dobby


LOCAL_SRC_FILES := imgui/imgui.cpp \
imgui/imgui_demo.cpp \
imgui/imgui_draw.cpp \
imgui/imgui_tables.cpp \
imgui/imgui_widgets.cpp \
imgui/backends/imgui_impl_android.cpp \
imgui/backends/imgui_impl_opengl3.cpp \
xdl/xdl.c \
xdl/xdl_iterate.c \
xdl/xdl_linker.c \
xdl/xdl_lzma.c \
xdl/xdl_util.c \
KittyMemory/KittyMemory.cpp \
KittyMemory/MemoryPatch.cpp \
KittyMemory/MemoryBackup.cpp \
KittyMemory/KittyUtils.cpp \
hack.cpp \
utils.cpp \

LOCAL_STATIC_LIBRARIES  := libdobby
LOCAL_CPP_FEATURES     := exceptions

include $(BUILD_SHARED_LIBRARY)
# ============================================================================ #
