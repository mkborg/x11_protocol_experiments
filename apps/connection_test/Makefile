ROOTDIR := ../..
TARGET := connection_test

SOURCES += connection.cpp
SOURCES += main.cpp

SYS_INCLUDE += libs/include
LIB_DIRS += libs/lib

LIBS += logger
LIBS += libc

LIBS += cxx

#LDFLAGS += '-Wl,-rpath=$$ORIGIN/$(ROOTDIR)/$(LIB_DIRS)'
LDFLAGS += '-Wl,-rpath=$$ORIGIN/../../libs/lib'

include $(ROOTDIR)/executable.Makefile
