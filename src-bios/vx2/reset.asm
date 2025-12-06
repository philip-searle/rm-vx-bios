
RESET		PROGRAM	OutFile=reset.obj

		include	"macros.inc"
		include	"segments.inc"
		include	"segments/bda.inc"
		include	"segments/ivt.inc"
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
; ══════════════════════════════════════════════════════════════════════════════
Reset_Actual	PROC
		ENDPROC	Reset_Actual

ENDPROGRAM	RESET
