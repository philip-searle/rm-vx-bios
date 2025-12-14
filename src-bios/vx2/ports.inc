
PORT_UNKNOWN_28F8	equ	28F8h

; ═╡ -W/16 ╞═╡ Misc I/O ╞═══════════════════════════════════════════════════════
; Write bit 0: network LED?
PORT_UNKNOWN_4F8	equ	4F8h
	MISC_IO_UNKHI	equ	0FFh
PORT_UNKNOWN_4F9	equ	4F9h
	MISC_IO_UNKLO	equ	0BEh
	MISC_IO_UNK40	equ	040h
	MISC_IO_NETLED	equ	001h

; ═╡ R-/16 ╞═╡ Misc I/O ╞═══════════════════════════════════════════════════════
; Write 00h to PORT_UNKNOWN_4F8 to read from PORT_UNKNOWN_4F9_IN
PORT_UNKNOWN_4F9_IN	equ	4F9h
	; XXX: Is this actually 286 vs 386 strap?
	MISC_IO_NPUDETECT	equ	80h	; 0=skip NPU detect on boot

PORT_UNKNOWN_81		equ	81h
PORT_UNKNOWN_3C7	equ	3C7h	; accessed when 8FD=1???
PORT_DRAT_4FA		equ	4FAh
PORT_GENE_8FA		equ	8FAh
PORT_UNKNOWN_8FD	equ	8FDh
PORT_UNKNOWN_CFF	equ	0CFFh

; ═╡ -W/8/16 ╞═╡ RM diagnostic code ╞═══════════════════════════════════════════
; Output code to be read by LED diagnostic card.
; Supports 8-bit writes to the hi/lo halves of the card.
PORT_RM_DIAG_LO		equ	0CF8h	; Lo byte of code
PORT_RM_DIAG_HI		equ	0CF9h	; Hi byte of code
PORT_RM_DIAG		equ	PORT_RM_DIAG_LO

; ═╡ -W/8/ ╞═╡ Shutdown scratch register ╞══════════════════════════════════════
; 8-bit scratch register, used to store the return code for the int15 block move
; function.  The IBM PC/AT also used it for diagnostic output, but VX/2 uses
; PORT_RM_DIAG instead.
PORT_SD_SCRATCH		 equ	80h
