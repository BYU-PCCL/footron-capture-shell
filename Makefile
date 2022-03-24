TARGET_APP := FootronCaptureShell

LOCAL_CFLAGS += -IInclude

CC = gcc
CXX = g++
LD = ld

CFLAGS += -O0 \
          -Wall \
          -Wextra \
          -Wno-unused-parameter \
          -Wno-sign-compare \
          -Wno-unused-variable \
          -Wno-unused-but-set-variable \
          -Wno-missing-field-initializers  \
          -fPIC \
          -DLIBMWVIDEORENDER_LINUX_DEF \
          $(LOCAL_CFLAGS) \
	  

ifeq ($(ARCH),)
ARCH =$(shell uname -m)
endif

ifeq ($(ARCH),x86_64)
override ARCH = x64
else
ifeq ($(ARCH),i386)
CFLAGS += -m32
else
ifeq ($(ARCH),i686)
CFLAGS += -m32
override ARCH = i386
else
ifeq ($(ARCH),aarch64)
override ARCH = arm64
else
override ARCH = arm32
endif
endif
endif
endif


CLIB = -lGL -lGLEW -lglfw -lpthread -ldl -ludev -lasound -lv4l2 
MWCAPTURE_LIBA = ./libMWCapture.a



all: $(TARGET_APP)

LOWLATENCYPREVIEW_OBJS = ./FootronCaptureShell.o ./VideoRenderOpenGL/glLowLatency.o ./VideoRenderOpenGL/LibMWVideoRender.o
	
$(TARGET_APP) : $(LOWLATENCYPREVIEW_OBJS) $(MWCAPTURE_LIBA) 
	$(CXX) -o $(TARGET_APP) $(LOWLATENCYPREVIEW_OBJS) $(MWCAPTURE_LIBA) $(CLIB)

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(LOCAL_CFLAGS) $< -o $*.o

clean:	
	rm -rf  $(TARGET_APP) $(LOWLATENCYPREVIEW_OBJS)

