
PORT_UNKNOWN_28F8	equ	28F8h

; ═╡ RW/16 ╞═╡ Misc I/O ╞═══════════════════════════════════════════════════════
; Write bit 0: network LED?
PORT_UNKNOWN_4F8	equ	4F8h
	MISC_IO_UNKHI	equ	0FFh
PORT_UNKNOWN_4F9	equ	4F9h
	MISC_IO_UNKLO	equ	0BEh
	MISC_IO_UNK40	equ	040h
	MISC_IO_NETLED	equ	001h

PORT_UNKNOWN_81		equ	81h
PORT_UNKNOWN_4FA	equ	4FAh
PORT_UNKNOWN_8FA	equ	8FAh
PORT_UNKNOWN_CFF	equ	0CFFh

; ═╡ -W/8/16 ╞═╡ RM diagnostic code ╞═══════════════════════════════════════════
; Output code to be read by LED diagnostic card.
; Supports 8-bit writes to the hi/lo halves of the card.
PORT_RM_DIAG_LO		equ	0CF8h	; Lo byte of code
PORT_RM_DIAG_HI		equ	0CF9h	; Hi byte of code
PORT_RM_DIAG		equ	PORT_RM_DIAG_LO
