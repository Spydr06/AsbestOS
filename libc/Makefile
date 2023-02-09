LIBK = libk.a

BUILDDIR := .build

SOURCES := $(shell find . -name *.c -or -name *.s)
OBJECTS := $(patsubst %, $(BUILDDIR)/%.o, $(SOURCES))

INCLUDE_DIR = include
KERNEL_INCLUDE_DIR = ..

CC = i686-elf-gcc
AS = i686-elf-as
AR = i686-elf-ar
CFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -O2 -nostartfiles -nodefaultlibs -Wall -Wextra -c \
		 -I$(INCLUDE_DIR) -I$(KERNEL_INCLUDE_DIR) -D__is_libk -g
ASFLAGS = -O2

$(LIBK): $(OBJECTS)
	$(AR) ruv $@ $(OBJECTS)

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
ifneq ("$(wildcard $(BUILDDIR))", "")
	rm -r $(BUILDDIR)
endif
ifneq ("$(wildcard $(LIBK))", "")
	rm $(LIBK)
endif
