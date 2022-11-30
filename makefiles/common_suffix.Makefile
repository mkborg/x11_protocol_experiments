# Directories for object files, libraries and binaries
BUILD_SUBDIRS := $(sort $(OBJECTS_DIRS) $(dir $(LIB_FILE)) $(dir $(EXECUTABLE)))
$(info BUILD_SUBDIRS="$(BUILD_SUBDIRS)")
$(BUILD_SUBDIRS):
	mkdir -pv $@


# There is no need to explicitly remove $(BUILD_SUBDIRS),
# $(OBJECTS) or '*.d' files.
# It shall be enough to recursively remove $(BUILD_DIR).
.PHONY: clean-build-dir
clean: clean-build-dir
clean-build-dir:
	@rm -rf $(BUILD_DIR)

.PHONY: clean-install-dir
clean: clean-install-dir
clean-install-dir:
	@rm -rf $(INSTALL_DIR)


#.PHONY: clean_$(LIB_FILE)
#clean: clean_$(LIB_FILE)
#clean_$(LIB_FILE):
#	rm -fv $(LIB_FILE)
#	rm -fv $(OBJECTS)
#	rm -fv $(OBJECTS:.o=.d)
#	-rmdir -pv $(BUILD_SUBDIRS)
#	rm -rfv $(OBJ_DIR)
