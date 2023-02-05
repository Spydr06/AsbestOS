LIBK = libk.a

BUILDDIR := .build

SOURCES := $(shell find . -name *.c)
OBJECTS := $(patsubst %.c, $(BUILDDIR)/%.o, $(SOURCES))

INCLUDE_DIR = include
KERNEL_INCLUDE_DIR = ..

TARGET = i686-elf-
CC = $(TARGET)gcc
AR = $(TARGET)ar
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -O2 -nostartfiles -nodefaultlibs -Wall -Wextra -c \
		 -I$(INCLUDE_DIR) -I$(KERNEL_INCLUDE_DIR) -D__is_libk

$(LIBK): $(OBJECTS)
	$(AR) ruv $@ $(OBJECTS)

$(BUILDDIR)/%.o: %.c | $(BUILDDIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

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
