
SHELL=/bin/bash
ifndef .VERBOSE
    .SILENT:
endif
ROOT=$(shell pwd)
ROOT=/home/arden/Programming/cpp/signi
CXX=clang++
CXXIGNORE=
CXXFLAGS=-std=c++17 -fPIC -Wall -Wpedantic --static
LINK=-lz
SOURCE=source
INCLUDE_DIR=include
INCLUDE=-I$(ROOT)/$(EXTERNAL)/estl -I$(ROOT)/$(BUILD)/libpng/include -I$(ROOT)/$(BUILD)/libjpeg/include
BUILD=build
EXTERNAL=external
TEST=test
PREFIX=~/testing
COMMON_INCLUDE=-I$(ROOT)/$(INCLUDE_DIR) $(INCLUDE)

SCAN_COLOR=\033[1;35m
BUILD_COLOR=\033[32m
CLEAN_COLOR=\033[1;33m
LINK_COLOR=\033[1;32m
INSTALL_COLOR=\033[1;36m
CMD_COLOR=\033[1;34m
HELP_COLOR=\033[1;34m

define scan_target
printf "%b%s%b\n" "$(SCAN_COLOR)" "Scaning dependencies for target $(1)" "\033[0m"
endef
define complete_target
printf "%s\n" "Built target $(1)"
endef
define clean_target
printf "%b%s%b\n" "$(CLEAN_COLOR)" "Cleaning target $(1)" "\033[0m"
endef
define install_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Installing target $(1)" "\033[0m"
endef
define uninstall_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Unnstalling target $(1)" "\033[0m"
endef
define print_build_c
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C object $$str" "\033[0m"
endef
define print_build_cpp
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C++ object $$str" "\033[0m"
endef
define print_link_lib
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking static library $$str" "\033[0m"
endef
define print_link_exe
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking executable $$str" "\033[0m"
endef
define print_run_cmd
printf "%b%s%b\n" "$(CMD_COLOR)" "Running '$(1)'" "\033[0m"
endef
define help
printf "%b%*s%b: %s\n" "$(HELP_COLOR)" 20 "$(1)" "\033[0m" "$(2)"
endef

all: build-signi

clean: clean-signi clean-libsigni.a

# SIGNI {{{

SIGNI=/home/arden/Programming/cpp/signi/signi
SIGNI_FILES=source/main.cpp
SIGNI_OBJS=$(SIGNI_FILES:%=$(ROOT)/$(BUILD)/%.o)
-include $(SIGNI_OBJS:.o=.d)

build-signi: build-libsigni.a pre-signi $(SIGNI)
	$(call complete_target,$(shell basename $(SIGNI)))

clean-signi:
	$(call clean_target,$(shell basename $(SIGNI)))
	if [ -e "$(SIGNI)" ]; then rm $(SIGNI); fi

pre-signi:
	$(call scan_target,$(shell basename $(SIGNI)))

$(SIGNI): $(SIGNI_OBJS)
	$(call print_link_exe,$(shell basename $(SIGNI)))
	$(CXX) $(SIGNI_OBJS) $(LIBSIGNI.A) $(LINK) $(COMMON_INCLUDE) -o $(SIGNI)

install-signi: build-signi
	$(call install_target,$(shell basename $(SIGNI)))
	mkdir -p $(PREFIX)/bin/
	cp $(SIGNI) $(PREFIX)/bin

uninstall-signi:
	$(call uninstall_target,$(shell basename $(SIGNI)))
	if [ -e "$(PREFIX)/bin/$(shell basename $(SIGNI))" ]; then rm $(PREFIX)/bin/$(shell basename $(SIGNI)); fi

# }}}
# LIBSIGNI.A {{{

LIBSIGNI.A=build/libsigni.a
LIBSIGNI.A_FILES=$(filter-out source/main.cpp, $(shell find "source/" -name "*.cpp"))
LIBSIGNI.A_OBJS=$(LIBSIGNI.A_FILES:%=$(ROOT)/$(BUILD)/%.o)
-include $(LIBSIGNI.A_OBJS:.o=.d)

build-libsigni.a: build-libpng.a build-libjpeg.a pre-libsigni.a $(LIBSIGNI.A)
	$(call complete_target,$(shell basename $(LIBSIGNI.A)))

clean-libsigni.a: clean-libpng.a clean-libjpeg.a
	$(call clean_target,$(shell basename $(LIBSIGNI.A)))
	if [ -e "$(LIBSIGNI.A)" ]; then rm $(LIBSIGNI.A); fi

pre-libsigni.a:
	$(call scan_target,$(shell basename $(LIBSIGNI.A)))

$(LIBSIGNI.A): $(LIBSIGNI.A_OBJS)
	$(call print_link_lib,$(shell basename $(LIBSIGNI.A)))
	ar rcs $@ $(LIBSIGNI.A_OBJS)
	mkdir -p $(ROOT)/tmp/libpng.a && cd $(ROOT)/tmp/libpng.a && ar x /home/arden/Programming/cpp/signi/build/libpng.a/lib/libpng.a && ar qc $(ROOT)/$@ $(ROOT)/tmp/libpng.a/*.o && rm -rf $(ROOT)/tmp/libpng.a
	mkdir -p $(ROOT)/tmp/libjpeg.a && cd $(ROOT)/tmp/libjpeg.a && ar x /home/arden/Programming/cpp/signi/build/libjpeg.a/lib/libjpeg.a && ar qc $(ROOT)/$@ $(ROOT)/tmp/libjpeg.a/*.o && rm -rf $(ROOT)/tmp/libjpeg.a

install-libsigni.a: build-libsigni.a
	$(call install_target,$(shell basename $(LIBSIGNI.A)))
	mkdir -p $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/$(NAME)/
	cp $(LIBSIGNI.A) $(PREFIX)/lib
	if [ ! -z "$(INCLUDE_DIR)" ]; then cp -R $(INCLUDE_DIR)/ $(PREFIX)/include/$(NAME)/; fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.h")" ]; then cd $(SOURCE_DIR) && cp --parents $(sehll cd $(SOURCE_DIR) && find . -name "*.h") $(PREFIX)/include/$(NAME); fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.hpp")" ]; then cd $(SOURCE_DIR) && cp --parents $(sehll cd $(SOURCE_DIR) && find . -name "*.hpp") $(PREFIX)/include/$(NAME); fi

uninstall-libsigni.a:
	$(call uninstall_target,$(shell basename $(LIBSIGNI.A)))
	if [ ! -e "$(PREFIX)/lib/$(shell basename $(LIBSIGNI.A))" ]; then rm $(PREFIX)/lib/$(shell basename $(LIBSIGNI.A)); fi
	if [ ! -e "$(PREFIX)/include/$(NAME)" ]; then rm $(PREFIX)/include/$(NAME) -r; fi

# }}}
# LIBPNG.A {{{

build-libpng.a: pre-libpng.a
	if [ ! -f "external/libpng/configure" ]; then $(call print_run_cmd,autogen.sh) && cd external/libpng && ./autogen.sh; fi
	if [ ! -f "external/libpng/Makefile" ]; then $(call print_run_cmd,configure) && cd external/libpng && ./configure --prefix=/home/arden/Programming/cpp/signi/build/libpng.a; fi
	if [ ! -d "/home/arden/Programming/cpp/signi/build/libpng.a" ]; then $(call print_run_cmd,make) && cd external/libpng && make install; fi
	$(call complete_target,libpng.a)

clean-libpng.a:
	$(call clean_target,libpng.a)
	if [ -e "external/libpng/Makefile" ]; then cd external/libpng && make clean && rm Makefile; fi
	if [ -d "/home/arden/Programming/cpp/signi/build/libpng.a" ]; then rm /home/arden/Programming/cpp/signi/build/libpng.a -r; fi

pre-libpng.a:
	$(call scan_target,libpng.a)

# }}}
# LIBJPEG.A {{{

build-libjpeg.a: pre-libjpeg.a
	if [ ! -f "external/jpeg-8d/configure" ]; then $(call print_run_cmd,autogen.sh) && cd external/jpeg-8d && ./autogen.sh; fi
	if [ ! -f "external/jpeg-8d/Makefile" ]; then $(call print_run_cmd,configure) && cd external/jpeg-8d && ./configure --prefix=/home/arden/Programming/cpp/signi/build/libjpeg.a; fi
	if [ ! -d "/home/arden/Programming/cpp/signi/build/libjpeg.a" ]; then $(call print_run_cmd,make) && cd external/jpeg-8d && make install; fi
	$(call complete_target,libjpeg.a)

clean-libjpeg.a:
	$(call clean_target,libjpeg.a)
	if [ -e "external/jpeg-8d/Makefile" ]; then cd external/jpeg-8d && make clean && rm Makefile; fi
	if [ -d "/home/arden/Programming/cpp/signi/build/libjpeg.a" ]; then rm /home/arden/Programming/cpp/signi/build/libjpeg.a -r; fi

pre-libjpeg.a:
	$(call scan_target,libjpeg.a)

# }}}

$(ROOT)/$(BUILD)/%.cpp.o: %.cpp
	$(call print_build_cpp,$@)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $(COMMON_INCLUDE) $< -o $@
