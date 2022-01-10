export tool-out  := $(TOOL)
export tool-name := $(notdir $(TOOL))
export tool-src-dir := $(src-dir)/$(tool-name)

tool-srcs := $(shell find $(tool-src-dir) | grep -E "\.cpp$$")
tool-objs := $(tool-srcs:.cpp=.o)

common-cflags := -std=gnu++17 -g -Wall -O3 -nostdlib -nostdinc -ffreestanding -fno-stack-protector -mno-sse -mno-avx -no-pie
tool-cflags   := $(common-cflags) -I$(inc-dir)
tool-ldflags  := $(common-cflags) -static
# -Wl,-dynamic-linker,__INFOS_DYNAMIC_LINKER__

export BUILD-TARGET = $(patsubst $(top-dir)/%,%,$@)

all: $(tool-out)

clean:
	@echo "  RM    $(tool-out) $(tool-objs)"
	$(q)rm -f $(tool-out) $(tool-objs)

$(tool-out): $(real-lib-target) $(real-crt-target) $(tool-objs)
	@echo "  LD      $(BUILD-TARGET)"
	$(q)g++ -o $@ $(tool-ldflags) $(tool-objs) $(real-crt-target) $(real-lib-target)
# -L$(bin-dir) -linfos

$(tool-objs): %.o: %.cpp
	@echo "  C++     $(BUILD-TARGET)"
	$(q)g++ -c -o $@ $(tool-cflags) $<
