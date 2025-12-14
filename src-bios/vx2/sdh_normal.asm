; ╔══════════════════════════════════════════════╤═════════════════════════════╗
; ║ sdh_normal.asm                               │ Research Machines VX/2 BIOS ║
; ╟──────────────────────────────────────────────┴─────────────────────────────╢
; ║ Initialization code for a "normal" startup, i.e. one that doesn't involve  ║
; ║ a reset just to get the 80286 out of protected mode.                       ║
; ╚════════════════════════════════════════════════════════════════════════════╝

SDH_NORMAL	PROGRAM	OutFile=sdh_normal.obj

		include	"macros.inc"
		include	"segments.inc"
		include	"segments/bda.inc"
		include	"segments/ivt.inc"
		include	"ega.inc"
		include	"ports.inc"

		EXTERN	FatalError

		PUBLIC	SDH_Normal

; ═╡ SDH_Normal ╞══════════════════════════════════════════╡ nostack noreturn ╞═
;
; Code for a normal startup.
;
; On entry:
;   PIC1 and PIC2 initialized with all IRQs masked.
;   NPU reset.
; ══════════════════════════════════════════════════════════════════════════════
SDH_Normal	PROC
		DiagOut	Code=02h, Subcode=01h	; Check DRAT present

		mov	dx, PORT_DRAT_4FA
		mov	ax, 5555h		; Write alternating ones
		out	dx, al
		Delay	2
		in	al, dx			; Readback
		cmp_	al, ah			; Equal?
		jne	.dratNotPresent
		not	ax			; Invert test pattern
		out	dx, al
		Delay	2
		in	al, dx			; Readback
		cmp_	al, ah
		je	.dratPresent

.dratNotPresent	DiagOut	Subcode=02h
		mov	al, 4Eh			; ??? error code
		jmp	FatalError

.dratPresent	; DRAT register exists

; ──────────────────────────────────────────────────────────────────────────────
		DiagOut	Code=03h, Subcode=01h	; Check GENE present

		mov	dx, PORT_GENE_8FA
		mov	ax, 5555h		; Write alternating ones
		out	dx, al
		Delay	2
		in	al, dx			; Readback
		cmp_	al, ah			; Equal?
		jne	.geneNotPresent
		not	ax			; Invert test pattern
		out	dx, al
		Delay	2
		in	al, dx			; Readback
		cmp_	al, ah
		je	.genePresent

.geneNotPresent	DiagOut	Subcode=04h
		mov	al, 3Eh			; ??? error code
		jmp	FatalError

.genePresent	; GENE register exists

; ──────────────────────────────────────────────────────────────────────────────
		DiagOut	Code=04h, Subcode=01h	; Init EGA controller

		mov	dx, PORT_GENE_8FA
		mov	al, 0C0h		; ??? GENE
		out	dx, al

		; Disable video adaptor
		mov	dx, PORT_VGA_ADAPTOR_ENABLE
		xor_	al, al			; VGA_ADAPTOR_DISABLE
		out	dx, al

		; Configure PEGA Paradise register:
		; CGA I/O mapping, 8-dot characters, normal clock, no AT&T/M24
		; support, suppress flicker, unlock CRTC registers
		UnlockParadise \
			UnlockPort=PORT_MDA_MODE_CTRL, \
			Port=PORT_PEGA_PARADISE_MDA
		sub_	al, al
		out	dx, al

		; Also configure PEGA Paradise register using CGA ports
		; just in case it was previously configured to use them
		; (might be possible for a warm reboot?)
		UnlockParadise \
			UnlockPort=PORT_CGA_MODE_CTRL, \
			Port=PORT_PEGA_PARADISE_CGA
		sub_	al, al
		out	dx, al

		; Configure EGA:
		; emulate CGA port addresses, disable RAM, 14MHz dot clock,
		; use internal output, positive h/v retrace polarity
		mov	dx, PORT_EGA_MISC_CONTROL
		sub_	al, al
		out	dx, al

		; Set any MDA adaptor horizontal total to 134 characters so it
		; doesn't drive the attached monitor beyond its horizontal
		; refresh frequency (the IBM 5151 monitor can be damaged if
		; hsync is out of range).
		mov	dx, PORT_MDA_CRTC_ADDR
		out	dx, al			; Reg 0: horizontal total
		UnlockParadise \
			UnlockPort=PORT_MDA_MODE_CTRL, \
			Port=PORT_MDA_CRTC_DATA
		mov	al, 134-1		; Horiz total is set minus one
		out	dx, al

		; Enable PEGA2 video adapter
		mov	dx, PORT_VGA_ADAPTOR_ENABLE
		mov	al, VGA_ADAPTOR_SETUP | VGA_ADAPTOR_ROMPAGE2 | VGA_ADAPTOR_ROMPAGE1
		out	dx, al
		mov	dx, PORT_VGA_GLOBAL_ENABLE
		mov	al, VGA_GLOBAL_ENABLE
		out	dx, al
		mov	dx, PORT_VGA_ADAPTOR_ENABLE
		mov	al, VGA_ADAPTOR_ENABLE | VGA_ADAPTOR_ROMPAGE2 | VGA_ADAPTOR_ROMPAGE1
		out	dx, al

		; ???
		mov	dx, PORT_UNKNOWN_8FD
		mov	al, 1
		out	dx, al			; Unlock 3C7
		mov	dx, PORT_UNKNOWN_3C7
		out	dx, al			; Port 3C7h <- 1
		mov	dx, PORT_UNKNOWN_8FD
		xor_	al, al
		out	dx, al			; Lock 3C7

		; Async reset PEGA
		mov	dx, PORT_EGA_SEQ_INDEX
		mov	ax, 2001h		; Write index+data in one go
		out	dx, ax

		; Disable PEGA2 video adapter
		mov	dx, PORT_VGA_ADAPTOR_ENABLE
		mov	al, VGA_ADAPTOR_SETUP | VGA_ADAPTOR_ROMPAGE2 | VGA_ADAPTOR_ROMPAGE1
		out	dx, al
		mov	dx, PORT_VGA_GLOBAL_ENABLE
		xor_	al, al
		out	dx, al			; VGA_GLOBAL_DISABLE
		mov	dx, PORT_VGA_ADAPTOR_ENABLE
		out	dx, al			; VGA_ADAPTOR_DISABLE

		; Set EGA palette index 0 to black
		mov	dx, PORT_EGA_ATC_REGISTER
		sub_	al, al
		out	dx, al			; Palette index 0
		out	dx, al			; Set to black
		ENDPROC	SDH_Normal

; ──────────────────────────────────────────────────────────────────────────────
		DiagOut	Code=05h, Subcode=01h	; Reinit DRAT and GENE

ENDPROGRAM	SDH_NORMAL
