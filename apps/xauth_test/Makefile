ROOTDIR := ../..
TARGET := xauth_test

SOURCES += dump_authorization_data.cpp
SOURCES += dump_authorization_file.cpp
SOURCES += main.cpp
SOURCES += test_XauGetAuthByAddr.cpp
SOURCES += test_XauGetBestAuthByAddr.cpp

INCLUDE += libs/include
INCLUDE += libs/include/utils
LIB_DIRS += libs/lib

LIBS += logger
LIBS += libc
LIBS += utils
LIBS += x11

# Note: 'libc' depends on 'cxx'. It means that 'cxx' must be specified after 'libc'.
LIBS += cxx

include PKG_CONFIG.xau.Makefile
include PKG_CONFIG.common.Makefile

#LDFLAGS += '-Wl,-rpath=$$ORIGIN/$(ROOTDIR)/$(LIB_DIRS)'
LDFLAGS += '-Wl,-rpath=$$ORIGIN/../../libs/lib'

include $(ROOTDIR)/executable.Makefile
