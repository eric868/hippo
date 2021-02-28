#######Makefile Begin#######################

TARGET := base

#debug or release
VERSION := debug

#dynamic_lib/static_lib/executable
TARGET_TYPE := static_lib

SRCDIR   := ./src

#solution dir
SOLUTIONDIR := ../../

#include dir
INCLUDES := -I$(SOLUTIONDIR)3rd/openssl-1.0.1/include  
#INCLUDES += -I$(SOLUTIONDIR)3rd/libevent-2.1.11-stable/include
INCLUDES += -I$(SOLUTIONDIR)3rd

#depends lib
LIBS := -L$(SOLUTIONDIR)3rd/openssl-1.0.1/linux
#LIBS += -L$(SOLUTIONDIR)3rd/libevent-2.1.11-stable/linux
LIBS += -L$(SOLUTIONDIR)3rd/jsoncpp-1.6.5/linux
LIBS += -L$(SOLUTIONDIR)3rd/zlib-1.2.8/linux
#LIBS += -levent -levent_core -levent_extra
LIBS += -lssl -lcrypto -ljson_linux-gcc-4.8.5_libmt -lz
	
include $(SOLUTIONDIR)Makefile.share

### End of the Makefile 
###############################################################################

