ROOTDIR := .

SUBDIRS += libs/libc

SUBDIRS += apps/connection_test

include $(ROOTDIR)/Makefile.SUBDIRS

.PHONY: LIBS_SUBDIRS-ALL
LIBS_SUBDIRS-ALL += .subdir-libs_libc-all

.PHONY: APPS_SUBDIRS-ALL
APPS_SUBDIRS-ALL += .subdir-apps_connection_test-all

.subdir-apps/connection_test-all: .subdir-libs/libc-all
