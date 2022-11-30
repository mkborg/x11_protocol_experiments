include makefiles/common_prefix.Makefile


# There are two possible variants of 'position-independent code'
# generation: '-fpic' and '-fPIC'
#CFLAGS += -fpic
CFLAGS += -fPIC

# '-shared' is option for 'linking'
LDFLAGS += -shared


#LIB_DIR := LIB_DIR
LIB_DIR := BUILD_DIR
LIB_FILE_NAME := lib$(LIB_NAME).so
BUILD_LIB_FILE := $(LIB_DIR)/$(LIB_FILE_NAME)
$(info "BUILD_LIB_FILE='$(BUILD_LIB_FILE)'")

# 'link' library
all: $(BUILD_LIB_FILE)
$(BUILD_LIB_FILE): $(OBJECTS) | $$(dir $$@)
	$(CXX) $(CXXFLAGS) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)


INSTALL_DIR := INSTALL_DIR
INSTALL_LIB_FILE := $(INSTALL_DIR)/$(LIB_FILE_NAME)

.PHONY: install_library
install: install_library
install_library: $(BUILD_LIB_FILE)
	install -D -m 0755 $(BUILD_LIB_FILE) $(INSTALL_LIB_FILE)


include makefiles/common_suffix.Makefile
