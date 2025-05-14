DOXYGEN ?= doxygen
CC ?= gcc
CXX ?= g++

# Target macros
TARGET := ptlix_compliant_stl

# Compile macros
DIRS := src
OBJS := $(patsubst %.c,%.o,$(call rwildcard,$(DIRS),*.c)) # Automatically find all .c files in src and convert to .o

# Intermediate compile macros
ALL_OBJS := $(OBJS)
CLEAN_FILES := $(TARGET) $(OBJS)
DIST_CLEAN_FILES := $(CLEAN_FILES)

# Recursive wildcard
rwildcard=$(foreach d,$(wildcard $(addsuffix /,$(1))),$(call rwildcard,$(d),$(2)) $(filter $(subst *,%,$(2)),$(d)))

# Default target
default: all

# Non-phony targets
$(TARGET): $(OBJS)
	@echo "Building target: $@"
	$(CC) $(CFLAGS) $(ALL_OBJS) -o $@

# Phony targets
.PHONY: all
all: $(TARGET)
	@echo "Target $(TARGET) build finished."

.PHONY: lib
lib: $(OBJS)
	@echo "Building static library lib$(TARGET).a"
	ar rcs lib$(TARGET).a $(OBJS)

.PHONY: clean
clean:
	@echo "Cleaning files: $(CLEAN_FILES)"
	rm -f $(CLEAN_FILES)

.PHONY: distclean
distclean: clean
	@echo "Cleaning distribution files: $(DIST_CLEAN_FILES)"
	rm -f $(DIST_CLEAN_FILES)

.PHONY: docs
docs:
	@echo "Building documentation"
	$(DOXYGEN)

.PHONY: clean_docs
clean_docs:
	@echo "Cleaning documentation"
	rm -rf ./docs

.PHONY: format
format: .clang-format
	@echo "Formatting source files using .clang-format"
	clang-format -i --style=file $(call rwildcard,$(DIRS),*.c) $(call rwildcard,$(DIRS),*.h)
