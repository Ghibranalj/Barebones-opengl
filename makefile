# -----------------------------------------------------------------------------
# CMake project wrapper Makefile ----------------------------------------------
# -----------------------------------------------------------------------------

SHELL := /bin/bash
RM    := \rm -rf
MKDIR := mkdir -p
MAKE  := make --no-print-directory
src_files := $(shell find src -name '*.cpp' -or -name '*c' -or -name '*.h' -or -name '*.hpp')
CMAKE_FLAGS :=

.PHONY: all
all: ./build/Makefile
	@$(MAKE) -C ./build

release: CMAKE_FLAGS += -DCMAKE_BUILD_TYPE=Release
release: clean all distclean
	@echo "Release build complete."

run: ./build/Makefile
	 @$(MAKE) -C ./build run || true

./build/Makefile: $(src_files)
	@($(MKDIR) build > /dev/null)
	@(cd build > /dev/null 2>&1 && cmake $(CMAKE_FLAGS) .. )

.PHONY: valgrind
valgrind: ./build/Makefile
	@$(MAKE) -C ./build valgrind || true

.PHONY: distclean clean
clean:
	@$(RM) -rf ./build
distclean:
	@($(MKDIR) build > /dev/null)
	@(cd build > /dev/null 2>&1 && cmake .. > /dev/null 2>&1)
	@$(RM) ./build/Makefile
	@$(RM) ./build/src
	@$(RM) ./build/test
	@$(RM) ./build/CMake*
	@$(RM) ./build/cmake.*
	@$(RM) ./build/*.cmake
	@$(RM) ./build/*.txt
	@$(RM) ./build/compile_commands.json
	@$(RM) ./build/vendor
