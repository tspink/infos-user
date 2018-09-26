export tool-out  := $(TOOL)
export tool-name := $(notdir $(TOOL))
export tool-src-dir := $(src-dir)/$(tool-name)

tool-srcs := $(shell find $(tool-src-dir) | grep -E "\.cpp$$")
tool-objs := $(tool-srcs:.cpp=.o)

tool-cflags  := -g -Wall -O3 -nostdlib -nostdinc -std=gnu++17 -I$(inc-dir) -ffreestanding -mno-sse -mno-avx -fno-stack-protector
tool-ldflags := -static -nostdlib -nostdinc

export BUILD-TARGET = $(patsubst $(top-dir)/%,%,$@)

all: $(tool-out)

clean:
	@echo "  RM    $(tool-out) $(tool-objs)"
	$(q)rm -f $(tool-out) $(tool-objs)

$(tool-out): $(real-lib-target) $(tool-objs)
	@echo "  LD      $(BUILD-TARGET)"
	$(q)g++ -o $@ $(tool-ldflags) $(tool-objs) $(real-lib-target)

$(tool-objs): %.o: %.cpp
	@echo "  C++     $(BUILD-TARGET)"
	$(q)g++ -c -o $@ $(tool-cflags) $<
