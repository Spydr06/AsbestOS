# files
LINK_SCRIPT := link.ld
KERNEL_ELF := kernel.elf

SOURCES := $(wildcard *.[cs])
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
OBJECTS := $(patsubst %.s, %.o, $(OBJECTS))

# assembler, compiler flags
CC = gcc
AS = nasm
CFLAGS  = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		  -nostartfiles -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -T $(LINK_SCRIPT) -melf_i386
ASFLAGS = -f elf

.PHONY:
all: $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJECTS)
	ld $(LDFLAGS) $^ -o $(KERNEL_ELF)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

.PHONY:
clean:
ifneq ("$(wildcard $(KERNEL_ELF))", "")
	rm $(KERNEL_ELF)
endif
	rm *.o
