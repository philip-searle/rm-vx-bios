
&mkdir -p post

include ../../tools/euroasm_scanner.mk

OBJECTS	:=	reset.obj \
			sdh_normal.obj \
			rom_trailer.obj

%.obj %.asm.lst: %.asm euroasm.ini
	$(EUROASM) $(input)

bios.bin bios.map bios.hex: $(OBJECTS) glink.lnk
	$(GLINK) glink.lnk
	srec_cat -Output bios.hex bios.bin -Binary
