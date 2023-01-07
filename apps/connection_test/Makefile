ROOTDIR := ../..
TARGET := connection_test

SOURCES += main.cpp

INCLUDE += libs/include
LIB_DIRS += libs/lib

LIBS += logger
LIBS += libc
LIBS += x11

LIBS += cxx

#LDFLAGS += '-Wl,-rpath=$$ORIGIN/$(ROOTDIR)/$(LIB_DIRS)'
LDFLAGS += '-Wl,-rpath=$$ORIGIN/../../libs/lib'

include $(ROOTDIR)/executable.Makefile
