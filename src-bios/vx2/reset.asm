; ╔══════════════════════════════════════════════╤═════════════════════════════╗
; ║ reset.asm                                    │ Research Machines VX/2 BIOS ║
; ╟──────────────────────────────────────────────┴─────────────────────────────╢
; ║ Power-on-reset code, run immediately after the CPU starts up.              ║
; ╚════════════════════════════════════════════════════════════════════════════╝

RESET		PROGRAM	OutFile=reset.obj

		include	"macros.inc"
		include	"segments.inc"
		include	"segments/bda.inc"
		include	"segments/ivt.inc"
		include	"cmos.inc"
		include	"keyboard.inc"
		include	"npu.inc"
		include	"pic.inc"
		include	"ports.inc"

		EXTERN	SDH_Normal

		PUBLIC	FatalError, Reset_Actual

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
		mov_	al, ah
		out	dx, al

		xor_	cx, cx			; Max iterations
.wait		mov	[si], cx		; Store iteration count
		mov	dx, PORT_DRAT_4FA
		mov_	al, cl
		out	dx, al			; ??? lo byte of loop count
		in	al, dx			; readback value
		mov	dx, PORT_GENE_8FA
		mov_	al, cl
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

; ──────────────────────────────────────────────────────────────────────────────
		; We only care about certain shutdown reasons.  Keep the ones we
		; care about in CX, and discard the other ones.

		; Output shutdown reason to diagnostic port
		; [Undoc] not mentioned in [Service B.1]
		DiagOut	Subcode=cl

		; Cold boot makes any shutdown reason irrelevant
		test	ch, KBC_STATUS_SYS
		jz	.discardReason
		; Some shutdown reasons require us to skip as much init code as
		; possible, so keep them around.
		cmp	cl, SD_BLOCK_MOVE
		jz	.knowReason
		cmp	cl, SD_JMP_WITHOUT_INT
		jz	.knowReason
		cmp	cl, SD_JMP_WITH_INT
		jz	.knowReason
		; All other shutdown reasons need no special handling

.discardReason	xor_	cx, cx
.knowReason	; Non-zero CX triggers different behaviour later

; ──────────────────────────────────────────────────────────────────────────────
		; Decide whether we need to set the NPU type
		mov	al, 0
		mov	dx, PORT_UNKNOWN_4F8
		out	dx, al
		inc	dx		; advance to PORT_UNKNOWN_4F9_IN
		in	al, dx
		test	al, MISC_IO_NPUDETECT
		jz	.npuDetected	; skip NPU detect?
		jcxz	.npuIs387	; ??? cold boot doesnt't do detect

		mov	al, CMOS_EQUIPMENT | NMI_DISABLE
		out	PORT_CMOS_ADDRESS, al
		Delay	2
		in	al, PORT_CMOS_DATA
		test	al, CMOS_EQUIP_NPU_INST
		jz	.npuIs287

.npuIs387	MovEaxCr0
		or	al, 10h		; set ET=387
		MovCr0Eax
		jmp	.npuDetected

.npuIs287	MovEaxCr0
		and	al, 0EFh	; set ET=287
		MovCr0Eax

.npuDetected

; ──────────────────────────────────────────────────────────────────────────────
		; Minimal reset code complete: check for shutdown reasons that
		; require us to skip the remaining reset code.
		cmp	cl, SD_BLOCK_MOVE
		jnz	.L1
		jmp	.SDH_BLockMove
.L1		cmp	cl, SD_JMP_WITHOUT_INT
		jnz	.L2
		jmp	.SDH_Jmp
		FillerNop
.L2		; Must be cold boot or SD_JMP_WITH_INT

; ──────────────────────────────────────────────────────────────────────────────
		; Initialize interrupt controllers in FE3010
		DiagOut	Subcode=2

		; ICW1: edge triggered, 4-byte IVT entries, cascade, ICW4 needed
		mov	al, 11h
		out	PORT_PIC1_CTRL, al
		Delay	2
		; ICW2: base vector = 8
		mov	al, 08h
		out	PORT_PIC1_CTRL2, al
		Delay	2
		; ICW3: Cascade input on IRQ2
		mov	al, 04h
		out	PORT_PIC1_CTRL2, al
		Delay	2
		; ICW4: x86 mode, normal EOI, nonbuffered
		mov	al, 01h
		out	PORT_PIC1_CTRL2, al
		Delay	2
		; Mask all IRQs
		mov	al, 0FFh
		out	PORT_PIC1_MASK, al
		Delay	2

		; ICW1: edge triggered, 4-byte IVT entries, cascade, ICW4 needed
		mov	al, 11h
		out	PORT_PIC2_CTRL, al
		Delay	2
		; ICW2: base vector = 70h
		mov	al, 70h
		out	PORT_PIC2_CTRL2, al
		Delay	2
		; ICW3: Cascade output on IRQ9
		mov	al, 02h
		out	PORT_PIC2_CTRL2, al
		Delay	2
		; ICW4: x86 mode, normal EOI, nonbuffered
		mov	al, 01h
		out	PORT_PIC2_CTRL2, al
		Delay	2
		; Mask all IRQs
		mov	al, 0FFh
		out	PORT_PIC2_MASK, al
		Delay	2

; ──────────────────────────────────────────────────────────────────────────────
		; Reset maths coprocessor (NPU)
		DiagOut	Subcode=3

		xor_	al, al
		out	PORT_287RESET, al
		Delay	2

; ──────────────────────────────────────────────────────────────────────────────
		; If we want a normal startup then jump to the code to handle
		; that.  Otherwise, drain the keyboard controller so it won't
		; keep triggering interruots and then return to user code in the
		; appropriate way.
		jcxz	.SDH_Normal

		; Drain keyboard controller
.drainKbc	in	al, PORT_KBC_STATUS
		Delay	2
		test	al, KBC_STATUS_OBF	; KBC drained?
		jz	.SDH_JmpWithInt		; done, if so
		in	al, PORT_KBC_DATA	; read KBC byte
		Delay	2
		jmp	.drainKbc

; ──────────────────────────────────────────────────────────────────────────────
.SDH_JmpWithInt	; Acknowledge interrupt and jump to saved address
		mov	al, NONSPECIFIC_EOI
		out	PORT_PIC1_CTRL, al
		; Fallthrough to .SDH_Jmp

; ──────────────────────────────────────────────────────────────────────────────
.SDH_Jmp	; Jump directly to saved return address
		mov	ax, BDA_SEGMENT
		mov	ds, ax
		jmpf	[AdapterRomOffset]

; ──────────────────────────────────────────────────────────────────────────────
.SDH_BLockMove	; Recover return value and complete int15 call
		mov	ax, BDA_SEGMENT
		mov	ds, ax
		mov	ss, [AdapterRomSegment]
		mov	sp, [AdapterRomOffset]	; restore stack
		mov_	bp, sp
		in	al, PORT_SD_SCRATCH	; recover return value
		mov	[bp+13h], al		; place in stack
		pop	ds
		pop	es
		popa
		iret

		; SDH_Normal expected to link after here so we can fallthrough
.SDH_Normal	ENDPROC	Reset_Actual

ENDPROGRAM	RESET
