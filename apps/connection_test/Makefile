ROOTDIR := ../..
TARGET := connection_test

SOURCES += connection.cpp
SOURCES += connection_config.cpp
SOURCES += connection_protocol.cpp
SOURCES += main.cpp
#SOURCES += x11_unix_endpoint.cpp

INCLUDE += libs/include
LIB_DIRS += libs/lib

LIBS += logger
LIBS += libc
LIBS += x11

LIBS += cxx

#LDFLAGS += '-Wl,-rpath=$$ORIGIN/$(ROOTDIR)/$(LIB_DIRS)'
LDFLAGS += '-Wl,-rpath=$$ORIGIN/../../libs/lib'

include $(ROOTDIR)/executable.Makefile
