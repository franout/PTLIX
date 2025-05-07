
DOXYGEN ?= doxygen 
CC ?= gcc
CXX ?= g++


# target macros
TARGET := ptlix_compliant_stl
MAIN_SRC := test.c

# compile macros
DIRS := src # FILL: only the dirs which contain the src files, in this case, `src` should be added
OBJS := # FILL: only the objects in current dir, and do not include the one contains `main()`

# intermedia compile macros
# NOTE: ALL_OBJS are intentionally left blank, no need to fill it
ALL_OBJS := 
CLEAN_FILES := $(TARGET) $(OBJS)
DIST_CLEAN_FILES := $(OB JS)

# recursive wildcard
rwildcard=$(foreach d,$(wildcard $(addsuffix *,$(1))),$(call rwildcard,$(d)/,$(2))$(filter $(subst *,%,$(2)),$(d)))

# default target
default: all

# non-phony targets
$(TARGET):  $(OBJS) 
	@echo -e "\t" CC $(CFLAGS) $(ALL_OBJS) $(MAIN_SRC) -o $@
	@$(CC) $(CFLAGS) $(ALL_OBJS) $(MAIN_SRC) -o $@

# phony targets
.PHONY: all
all: $(TARGET)
	@echo Target $(TARGET) build finished.

.PHONY: lib
lib: all
	@echo Making lib
	@echo -e "\t" CC $(CFLAGS) $(ALL_OBJS) $(MAIN_SRC) -o $@
	@$(CC) $(CFLAGS) $(ALL_OBJS) $(MAIN_SRC) -o $@

.PHONY: clean
clean: clean-subdirs
	@echo CLEAN $(CLEAN_FILES)
	@rm -f $(CLEAN_FILES)

.PHONY: distclean
distclean: clean-subdirs
	@echo CLEAN $(DIST_CLEAN_FILES)
	@rm -f $(DIST_CLEAN_FILES)


.PHONY: docs
docs: 
	@echo Building docs
	$(DOXYGEN)

.PHONY: clean_docs
clean_docs:
	@echo Cleaning docs
	rm -rf ./docs
