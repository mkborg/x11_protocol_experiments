ROOTDIR := ../..
TARGET := xauth_test

SOURCES += dump_authorization_file.cpp
SOURCES += main.cpp

SYS_INCLUDE += libs/include
LIB_DIRS += libs/lib

LIBS += logger
LIBS += libc

# Note: 'libc' depends on 'cxx'. It means that 'cxx' must be specified after 'libc'.
LIBS += cxx

#LIBS += cxx_template
#LIBS += cxx_Xau

include PKG_CONFIG.Xau.Makefile
include PKG_CONFIG.common.Makefile

#LDFLAGS += '-Wl,-rpath=$$ORIGIN/$(ROOTDIR)/$(LIB_DIRS)'
LDFLAGS += '-Wl,-rpath=$$ORIGIN/../../libs/lib'

include $(ROOTDIR)/executable.Makefile
