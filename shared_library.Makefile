include $(ROOTDIR)/common_prefix.Makefile

CFLAGS += -fPIC
CFLAGS += -shared

# prohibit undefined symbols
LDFLAGS += -Wl,-z,defs

TARGET_INSTALL_DIR := $(BASE_INSTALL_DIR)/lib
#LIBRARY := $(TARGET_INSTALL_DIR)/$(TARGET)

all: $(TARGET_BUILD_DIR)/$(TARGET)
# 'link' library
$(TARGET_BUILD_DIR)/$(TARGET): $(OBJECTS) | $$(dir $$@)
	$(CXX) $(CXXFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: install_library
install: install_library
install_library:
	install -D -m 0755 $(TARGET_BUILD_DIR)/$(TARGET) $(TARGET_INSTALL_DIR)/$(TARGET)

include $(ROOTDIR)/common_suffix.Makefile
