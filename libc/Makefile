LIBK = libk.a

SOURCES := $(shell find . -name *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

INCLUDE_DIR = include
KERNEL_INCLUDE_DIR = ..

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -c \
		 -I$(INCLUDE_DIR) -I$(KERNEL_INCLUDE_DIR) -D__is_libk

$(LIBK): $(OBJECTS)
	ar ruv $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY:
clean:
ifneq ("$(shell find . -name "*.o" -or -name "*.a")", "")
	rm $(shell find . -name "*.o" -or -name "*.a")
endif
