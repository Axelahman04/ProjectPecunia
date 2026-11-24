SRC_DIR   ?= .
BUILD_DIR ?= build
SOURCES   := $(shell find $(SRC_DIR) -name '*.c' -or -name '*.S')
OBJECTS   := $(addsuffix .o, $(basename $(notdir $(SOURCES))))
LINKER    := $(CURDIR)/platform/dtekv-script.lds

TOOLCHAIN ?= riscv32-unknown-elf-
CFLAGS ?= -Wall -nostdlib -O3 -mabi=ilp32 -march=rv32imzicsr -fno-builtin \
          -I$(CURDIR)/platform -I$(CURDIR)/gfx -I$(CURDIR)/ui -I$(CURDIR)/game

build: clean main.bin

main.elf:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(TOOLCHAIN)gcc -c $(CFLAGS) $(addprefix $(CURDIR)/,$(SOURCES))
	cd $(BUILD_DIR) && $(TOOLCHAIN)ld -o $(CURDIR)/$@ -T $(LINKER) \
	    $(filter-out boot.o,$(OBJECTS)) $(CURDIR)/platform/softfloat.a

main.bin: main.elf
	$(TOOLCHAIN)objcopy --output-target binary $< $@
	$(TOOLCHAIN)objdump -D $< > $<.txt

clean:
	rm -rf $(BUILD_DIR) main.elf main.bin main.elf.txt