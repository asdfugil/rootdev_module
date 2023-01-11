PONGO_SRC ?= ../PongoOS
CC ?= clang -arch arm64
CFLAGS +=  -I$(PONGO_SRC)/include -I$(PONGO_SRC)/src/kernel -I$(PONGO_SRC)/newlib/aarch64-none-darwin/include -Iinclude -I$(PONGO_SRC)/apple-include
CFLAGS += -Os -ffreestanding -nostdlib -U__nonnull -DTARGET_OS_OSX=0 -DTARGET_OS_MACCATALYST=0 -D_GNU_SOURCE -DDER_TAG_SIZE=8
LDFLAGS += -Wl,-kext -Wl,-dead_strip -flto=thin -fno-stack-protector

all: set_rootdev

%.o: %.c
	$(CC) -c -nostdlibinc $(CFLAGS) $<

set_rootdev: main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o set_rootdev

clean:
	rm -f set_rootdev *.o

