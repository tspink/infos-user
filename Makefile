export MAKEFLAGS    += -rR --no-print-directory
export q := @

export top-dir := $(CURDIR)
export inc-dir := $(top-dir)/inc
export lib-dir := $(top-dir)/lib
export src-dir := $(top-dir)/src
export bin-dir := $(top-dir)/bin

lib-target := libinfos.a
tool-targets := init ls shell sched-test1 sched-test2 cat date
	
export real-lib-target   := $(bin-dir)/$(lib-target)
real-tool-targets := $(patsubst %,$(bin-dir)/%,$(tool-targets))
real-tool-clean-targets := $(patsubst %,__clean__$(bin-dir)/%,$(tool-targets))
	
lib-srcs := $(shell find $(lib-dir) | grep -E "\.cpp$$")
lib-objs := $(lib-srcs:.cpp=.o)
lib-cxxflags := -g -Wall -Wno-main -nostdlib -nostdinc -std=gnu++17 -O3 -I$(inc-dir) -fno-builtin -ffreestanding -mno-sse -mno-avx -fno-stack-protector
	
fs-target := $(bin-dir)/rootfs.tar
	
export BUILD-TARGET = $(patsubst $(top-dir)/%,%,$@)

all: $(real-lib-target) $(real-tool-targets)
	
clean: $(real-tool-clean-targets)
	@echo "  RM    $(real-lib-target) $(lib-objs) $(real-tool-targets)"
	$(q)rm -f $(real-lib-target) $(lib-objs) $(real-tool-targets)
	
fs: $(fs-target)
	
$(real-lib-target): $(bin-dir) $(lib-objs)
	@echo "  AR      $(BUILD-TARGET)"
	$(q)ar rcs $@ $(lib-objs)
	
$(bin-dir):
	mkdir $@

$(real-tool-targets): $(real-lib-target) .FORCE
	@make -f Makefile.tool TOOL=$@

$(real-tool-clean-targets): .FORCE
	@make -f Makefile.tool TOOL=$(patsubst __clean__%,%,$@) clean

$(lib-objs): %.o: %.cpp
	@echo "  C++     $(BUILD-TARGET)"
	$(q)g++ -c -o $@ $(lib-cxxflags) $<

$(fs-target): all
	mkdir -p $(bin-dir)/docs
	mkdir -p $(bin-dir)/subdir1/subdir11/subdir111
	mkdir -p $(bin-dir)/subdir1/subdir11/subdir112
	mkdir -p $(bin-dir)/subdir1/subdir11/subdir113
	mkdir -p $(bin-dir)/subdir1/subdir12
	mkdir -p $(bin-dir)/subdir1/subdir13/subdir131
	mkdir -p $(bin-dir)/subdir2/subdir21

	touch $(bin-dir)/subdir1/A
	touch $(bin-dir)/subdir1/B
	touch $(bin-dir)/subdir1/C
	touch $(bin-dir)/subdir1/subdir11/D
	touch $(bin-dir)/subdir1/subdir11/subdir111/E
	touch $(bin-dir)/subdir1/subdir11/subdir111/F
	touch $(bin-dir)/subdir1/subdir12/G
	touch $(bin-dir)/subdir1/subdir12/H
	touch $(bin-dir)/subdir1/subdir13/I
	touch $(bin-dir)/subdir1/subdir13/J
	touch $(bin-dir)/subdir1/subdir13/subdir131/K
	touch $(bin-dir)/subdir2/L
	touch $(bin-dir)/subdir2/subdir21/M
	touch $(bin-dir)/subdir2/subdir21/N

	cp README $(bin-dir)/docs/

	tar cf $@ -C $(bin-dir) $(tool-targets) docs/ subdir1/ subdir2/

.PHONY: .FORCE
