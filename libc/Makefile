LIBK = libk.a

BUILDDIR := .build

SOURCES := $(shell find . -name *.c)
OBJECTS := $(patsubst %.c, $(BUILDDIR)/%.o, $(SOURCES))

INCLUDE_DIR = include
KERNEL_INCLUDE_DIR = ..

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -c \
		 -I$(INCLUDE_DIR) -I$(KERNEL_INCLUDE_DIR) -D__is_libk

$(LIBK): $(OBJECTS)
	ar ruv $@ $(OBJECTS)

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
