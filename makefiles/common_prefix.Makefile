.PHONY: default
default: all

.PHONY: all
.PHONY: clean
.PHONY: install
install: all

# Let's use '.SECONDEXPANSION:' for substitutions in prerequisites
.SECONDEXPANSION:

# search $(SOURCES) in $(SOURCES_DIRS)
vpath %.c $(SOURCES_DIRS)
vpath %.cpp $(SOURCES_DIRS)

# search include files next to sources
INCLUDE += $(SOURCES_DIRS)


CXXFLAGS += -std=c++11

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wno-format-zero-length
CFLAGS += -g
CFLAGS += -O2
#CFLAGS += -fvisibility=hidden

CFLAGS += $(addprefix -isystem , $(SYS_INCLUDE))
CFLAGS += $(addprefix -iquote , $(INCLUDE))

# Generate dependencies
CFLAGS += -MMD

#LDFLAGS += -Wl,--as-needed
#LDFLAGS += -Wl,-Map=$@.map

LDFLAGS += $(addprefix -L, $(LIB_DIRS))
LDFLAGS += $(addprefix -l, $(LIBS))


CC := gcc
CXX := g++
MAKE += -r
#$(info "MAKE='$(MAKE)'")


#OBJECTS_DIR := OBJECTS_DIR
OBJECTS_DIR := BUILD_DIR
OBJECTS := $(patsubst %,$(OBJECTS_DIR)/%.o,$(SOURCES))
$(info "OBJECTS='$(OBJECTS)'")
OBJECTS_DIRS := $(sort $(dir $(OBJECTS)))
$(info "OBJECTS_DIRS='$(OBJECTS_DIRS)'")


# C sources compilation
$(OBJECTS_DIR)/%.c.o : %.c | $$(dir $$@)
	$(CC) -c $(CFLAGS) -o $@ $<

# C++ sources compilation
$(OBJECTS_DIR)/%.cpp.o: %.cpp | $$(dir $$@)
	$(CXX) -c $(CXXFLAGS) $(CFLAGS) -o $@ $<


# Load dependencies if present
-include $(OBJECTS:.o=.d)
