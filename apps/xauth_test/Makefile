ROOTDIR := ../..
TARGET := xauth_test

SOURCES += dump_authorization_data.cpp
SOURCES += dump_authorization_file.cpp
SOURCES += main.cpp
SOURCES += test_XauGetAuthByAddr.cpp
SOURCES += test_XauGetBestAuthByAddr.cpp

SYS_INCLUDE += libs/include
SYS_INCLUDE += libs/include/utils
LIB_DIRS += libs/lib

LIBS += logger
LIBS += libc
LIBS += utils

# Note: 'libc' depends on 'cxx'. It means that 'cxx' must be specified after 'libc'.
LIBS += cxx

#LIBS += cxx_template
#LIBS += x11_xauth
LIBS += x11_constants

include PKG_CONFIG.xau.Makefile
include PKG_CONFIG.common.Makefile

#LDFLAGS += '-Wl,-rpath=$$ORIGIN/$(ROOTDIR)/$(LIB_DIRS)'
LDFLAGS += '-Wl,-rpath=$$ORIGIN/../../libs/lib'

include $(ROOTDIR)/executable.Makefile
