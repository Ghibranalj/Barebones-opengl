# -----------------------------------------------------------------------------
# CMake project wrapper Makefile ----------------------------------------------
# -----------------------------------------------------------------------------

SHELL := /bin/bash
RM    := \rm -rf
MKDIR := mkdir -p
MAKE  := make --no-print-directory

all: ./build/Makefile
	@$(MAKE) -C ./build

run: all
	 @$(MAKE) -C ./build run || true

./build/Makefile:
	@($(MKDIR) build > /dev/null)
	@(cd build > /dev/null 2>&1 && cmake ..)

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


ifeq ($(findstring distclean,$(MAKECMDGOALS)),)
	@$(MAKECMDGOALS): ./build/Makefile
	@$(MAKE) -C build $(MAKECMDGOALS)
endif
