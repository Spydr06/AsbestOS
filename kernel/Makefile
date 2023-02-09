# files
LINK_SCRIPT := link.ld
KERNEL_ELF := kernel.elf
KERNEL_SYM := kernel.sym
LIBK := libk.a

BUILDDIR := .build

SOURCES := $(shell find . -name "*.c" -or -name "*.s")
OBJECTS := $(patsubst %, $(BUILDDIR)/%.o, $(SOURCES))

LIBK_INCLUDE := ../libc/include

# assembler, compiler flags
CC = i686-elf-gcc
AS = i686-elf-as
LD = i686-elf-ld
OBJCOPY = objcopy
CFLAGS  = -g -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		  -O2 -nostartfiles -nodefaultlibs -Wall -Wextra -c -I$(LIBK_INCLUDE)
LDFLAGS = -T $(LINK_SCRIPT)
ASFLAGS = -O2

.PHONY:
all: $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJECTS) $(LIBK)
	$(LD) $(LDFLAGS) $^ -o $(KERNEL_ELF)
	$(OBJCOPY) --only-keep-debug $(KERNEL_ELF) $(KERNEL_SYM)
	$(OBJCOPY) --strip-debug $(KERNEL_ELF)

$(BUILDDIR)/%.c.o: %.c | $(BUILDDIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.s.o: %.s | $(BUILDDIR)
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR):
	mkdir $@

.PHONY:
clean:
ifneq ("$(wildcard $(KERNEL_ELF))", "")
	rm $(KERNEL_ELF)
endif
ifneq ("$(wildcard $(KERNEL_SYM))", "")
	rm $(KERNEL_SYM)
endif
ifneq ("$(wildcard $(BUILDDIR))", "")
	rm -r $(BUILDDIR)
endif
ifneq ("$(wildcard $(LIBK))", "")
	rm $(LIBK)
endif
