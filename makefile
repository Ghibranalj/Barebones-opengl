# -----------------------------------------------------------------------------
# CMake project wrapper Makefile ----------------------------------------------
# -----------------------------------------------------------------------------

SHELL := /bin/bash
RM    := \rm -rf
MKDIR := mkdir -p
MAKE  := make

all: ./build/Makefile
	@$(MAKE) -C ./build

run: all
	 @$(MAKE) -C ./build run

./build/Makefile:
	@($(MKDIR) build > /dev/null)
	@(cd build > /dev/null 2>&1 && cmake ..)

.PHONY: distclean
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

clean:
	rm -rf ./build

# ifeq ($(findstring distclean,$(MAKECMDGOALS)),)
# 	@$(MAKECMDGOALS): ./build/Makefile
# 	@$(MAKE) -C build $(MAKECMDGOALS)
# endif
