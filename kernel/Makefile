
CURDIR=$(SRCDIR)/kernel

CFLAGS+=-I$(CURDIR)/include -I${CURDIR}/include/klibc

MODULES:=boot gdt idt util vga klibc
SRC_C:=$(foreach mod,$(MODULES),$(wildcard $(CURDIR)/$(mod)/*.c))
SRC_S:=$(foreach mod,$(MODULES),$(wildcard $(CURDIR)/$(mod)/*.asm))

OBJ_C:=$(patsubst $(CURDIR)/%.c,$(CURDIR)/obj/%.c.o,$(SRC_C))
OBJ_S:=$(patsubst $(CURDIR)/%.asm,$(CURDIR)/obj/%.asm.o,$(SRC_S))

.PHONY: init
init:
	mkdir -p $(foreach mod,$(MODULES),$(CURDIR)/obj/$(mod))

$(CURDIR)/obj/%.c.o: $(CURDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(CURDIR)/obj/%.asm.o: $(CURDIR)/%.asm
	$(AS) -o $@ $<

.PHONY: clean
clean:
	- rm $(foreach mod,$(MODULES),$(CURDIR)/obj/$(mod)/*.o)

kernel: $(CURDIR)/libkernel.a

$(CURDIR)/libkernel.a: $(OBJ_C) $(OBJ_S)
	$(AR) rcs $@ $^
