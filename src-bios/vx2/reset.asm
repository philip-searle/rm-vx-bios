
RESET		PROGRAM	OutFile=reset.obj

		include	"macros.inc"
		include	"segments.inc"
		include	"segments/bda.inc"
		include	"segments/ivt.inc"
		include	"cmos.inc"
		include	"keyboard.inc"
		include	"ports.inc"

		PUBLIC	Reset_Actual

; ═╡ FatalError ╞══════════════════════════════════════════╡ nostack noreturn ╞═
;
; Called by reset code to indicate startup cannot proceed.
;
; Writes an error code to port 28F8h then continually blinks the network LED.
; Also writes to ports 4FAh and 8FAh?
;
; On entry:
;   AL = Error code
;   SI → Scratch memory
; ══════════════════════════════════════════════════════════════════════════════
FatalError	PROC
		cli
		mov	dx, PORT_UNKNOWN_28F8	; ???
		out	dx, al

		mov	ah, MISC_IO_UNK40 | MISC_IO_NETLED
.blinkLed	mov	al, 0
		mov	dx, PORT_UNKNOWN_4F8	; ???
		out	dx, al
		inc	dx			; Advance to PORT_UNKNOWN_4F9
		mov	al, ah,CODE=LONG
		out	dx, al

		xor	cx, cx,CODE=LONG			; Max iterations
.wait		mov	[si], cx		; Store iteration count
		mov	dx, PORT_UNKNOWN_4FA
		mov	al, cl,CODE=LONG
		out	dx, al			; ??? lo byte of loop count
		in	al, dx			; readback value
		mov	dx, PORT_UNKNOWN_8FA
		mov	al, cl,CODE=LONG
		out	dx, al			; ??? lo byte of loop count
		in	al, dx			; readback value
		mov	dx, [si]
		mov	dx, [si]		; ??? why read twice
		loop	.wait

		xor	ah, MISC_IO_NETLED	; toggle LED
		jmp	.blinkLed
		ENDPROC	FatalError

; ═╡ Reset_Actual ╞════════════════════════════════════════╡ nostack noreturn ╞═
;
; First code executed after jumping from the reset vector.
; ══════════════════════════════════════════════════════════════════════════════
Reset_Actual	PROC
		cli
		in	al, PORT_UNKNOWN_81	; clear flipflop?
		mov	dx, PORT_UNKNOWN_CFF
		mov	al, 80h			; ???
		out	dx, al

; ──────────────────────────────────────────────────────────────────────────────
		DiagOut	Code=01h, Subcode=01h	; Check shutdown reason

		; Store status register in CH for later
		in	al, PORT_KBC_STATUS
		mov_	ch, al

		; Read shutdown reason to CL
		mov	al, CMOS_SHUTDOWN_REASON | NMI_DISABLE
		out	PORT_CMOS_ADDRESS, al
		Delay	2
		in	al, PORT_CMOS_DATA
		Delay	2
		mov_	cl, al

		; Reset shutdown reason
		xor_	al, al
		out	PORT_CMOS_DATA, al

		; Output shutdown reason to diagnostic port
		; [Undoc] not mentioned in [Service B.1]
		DiagOut	Subcode=cl
		ENDPROC	Reset_Actual

ENDPROGRAM	RESET
