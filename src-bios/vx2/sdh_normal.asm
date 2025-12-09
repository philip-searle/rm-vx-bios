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
		ENDPROC	SDH_Normal

ENDPROGRAM	SDH_NORMAL
