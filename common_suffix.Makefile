# Directories for object files and binaries
BUILD_SUBDIRS := $(sort $(OBJECTS_DIRS) $(dir $(EXECUTABLE)))
#$(info BUILD_SUBDIRS="$(BUILD_SUBDIRS)")
$(BUILD_SUBDIRS):
	mkdir -pv $@

# There is no need to explicitly remove $(BUILD_SUBDIRS),
# $(OBJECTS) or '*.d' files.
# It shall be enough to recursively remove $(TARGET_BUILD_DIR).
.PHONY: clean-build-dir
clean: clean-build-dir
clean-build-dir:
	@rm -rf $(TARGET_BUILD_DIR)

.PHONY: clean-install-dir
clean: clean-install-dir
clean-install-dir:
	@rm -rf $(BASE_INSTALL_DIR)
