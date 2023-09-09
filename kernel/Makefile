override MAKEFLAGS += -rR

LINK_SCRIPT := link.ld
KERNEL_ELF := kernel.elf
KERNEL_SYM := kernel.sym

BUILDDIR := .build

SOURCES := $(shell find . -name "*.c" -or -name "*.s")
OBJECTS := $(patsubst %, $(BUILDDIR)/%.o, $(SOURCES))

CC = x86_64-elf-gcc
AS = x86_64-elf-as
LD = x86_64-elf-ld
OBJCOPY = x86_64-elf-objcopy

override DEFAULT_CFLAGS := -c -g -O2 -pipe
override CFLAGS +=			\
	$(DEFAULT_CFLAGS)		\
	-Wall -Wextra			\
	-std=gnu99				\
	-ffreestanding			\
	-fno-stack-protector	\
	-fno-stack-check		\
	-fno-lto				\
	-fPIE					\
	-m64					\
	-march=x86-64			\
	-mno-80387 				\
    -mno-mmx 				\
    -mno-sse 				\
    -mno-sse2 				\
    -mno-red-zone			\
	-Ilib/include

override DEFAULT_LDFLAGS :=
override LDFLAGS += 		\
	$(DEFAULT_LDFLAGS)		\
	-m elf_x86_64			\
	-nostdlib				\
	-static					\
	-pie					\
	--no-dynamic-linker 	\
	-z text					\
	-z max-page-size=0x1000 \
	-T $(LINK_SCRIPT)

ASFLAGS = -O2

.PHONY:
all: $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJECTS)
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