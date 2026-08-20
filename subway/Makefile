# THEOS_DEVICE_IP = 127.0.0.1 -p 2222 # install to device from pc
ARCHS = arm64
DEBUG = 0
FINALPACKAGE = 1
FOR_RELEASE = 1

# 0 to treat warnings as errors, 1 otherwise.
IGNORE_WARNINGS=0

# 0 to compile for rootful jailbreaks, 1 otherwise.
ROOTLESS ?= 1

ifeq ($(ROOTLESS), 1)
THEOS_PACKAGE_SCHEME = rootless
endif 

# only set this  to 1 if you are on mobile theos
# assuming you have an sdk at your theos sdks directory
# this will include c++ headers and other needed headers for your project so you don't need to manually include them or something like that
# if some c++ headers are still missing in your sdk like "initializer_list" then manually copy them to your c++ headers directory and not your project folder
# for example, C++ headers should be supplied by the toolchain used with the SDK.
# please note, do not include c++ headers in your theos includes to enable c++ which is a ghetto solution and use this approach instead
MOBILE_THEOS = 1
TARGET = iphone:clang:18.4:14.0
ifeq ($(MOBILE_THEOS),1)
  # path to the iPhoneOS 18.4 SDK
  SDK_VERSION = 18.4
  SDK_PATH = $(THEOS)/sdks/iPhoneOS$(SDK_VERSION).sdk/
  $(info ===> Setting SYSROOT to $(SDK_PATH)...)
  SYSROOT = $(SDK_PATH)
else
  TARGET = iphone:clang:latest:8.0
endif


## Common frameworks ##
PROJ_COMMON_FRAMEWORKS = UIKit Foundation Security QuartzCore CoreGraphics CoreText AudioToolbox Accelerate

## source files ##
KITTYMEMORY_SRC = $(wildcard KittyMemory/*.cpp)
SCLALERTVIEW_SRC =  $(wildcard SCLAlertView/*.m)
MENU_SRC = Menu.mm

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = subway
subway_USE_MODULES = 0

subway_CFLAGS = -fobjc-arc -fno-modules -Wno-deprecated-declarations
subway_CCFLAGS = -std=c++11 -fno-rtti -fno-exceptions -DNDEBUG -fno-modules -Wno-deprecated-declarations

ifeq ($(IGNORE_WARNINGS),1)
  subway_CFLAGS += -w
  subway_CCFLAGS += -w
endif


subway_FILES = Tweak.xm $(MENU_SRC) $(KITTYMEMORY_SRC) $(SCLALERTVIEW_SRC)

subway_LIBRARIES += substrate

subway_FRAMEWORKS = $(PROJ_COMMON_FRAMEWORKS)
# GO_EASY_ON_ME = 1

include $(THEOS_MAKE_PATH)/tweak.mk

internal-package-check::
	@chmod 777 versionCheck.sh # Give permission to script 	
	@./versionCheck.sh # Script to verify template's current version

after-install::
	install.exec "killall -9  || :"
