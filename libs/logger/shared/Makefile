LIB_NAME := logger

CFLAGS += -DLOGGER_ENABLE_STDERR

# SOURCES:
SOURCES_DIRS += src
include src/Makefile
$(info "SOURCES='$(SOURCES)'")

#SYS_INCLUDE += src
SYS_INCLUDE += include

include makefiles/shared_library.Makefile
