ROOTDIR := ../..
TARGET := connection_test

SOURCES += main.cpp

INCLUDE += libs/include
LIB_DIRS += libs/lib

LIBS += logger
LIBS += libc
# 'x11' depends on 'cxx' and 'utils'
LIBS += x11

# 'utils' depends on 'cxx'
LIBS += utils

LIBS += cxx

#LDFLAGS += '-Wl,-rpath=$$ORIGIN/$(ROOTDIR)/$(LIB_DIRS)'
LDFLAGS += '-Wl,-rpath=$$ORIGIN/../../libs/lib'

include $(ROOTDIR)/executable.Makefile
