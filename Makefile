# Cross-compiler for RISC-V
CC = riscv64-unknown-elf-gcc
CFLAGS = -march=rv64gc -mabi=lp64d -O3 -Iinclude
AS = riscv64-unknown-elf-as
ASFLAGS = -march=rv64gc
LDFLAGS = -T link.ld -nostdlib -static

OBJS = src/main.o src/preprocessing.o src/kmeans.o src/elbow.o src/riscv_utils.o

all: clustering.elf

clustering.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f $(OBJS) clustering.elf

test: clustering.elf
	spike pk clustering.elf
