
; Predefine all virtual segments (that shouldn't be emitted into the
; final BIOS image), then switch back to the CODE segment so data and
; instructions will be emitted into it.

; BIOS code (F000:8000 - F000:FFFF)
[CODE]	SEGMENT WIDTH=16, ALIGN=1, CLASS=CODE, PURPOSE=DATA|CODE, COMBINE=PUBLIC

BIOS_SEGMENT	equ	0F000h
BIOS_START	equ	08000h
BIOS_START_PARA	equ	(BIOS_SEGMENT + BIOS_START >> 4)

; BIOS stack (0030:0000 - 0030:0080)
[STACK]	SEGMENT WIDTH=16, ALIGN=16, CLASS=STACK, PURPOSE=STACK, COMBINE=STACK

STACK_SEGMENT	equ	0030h
STACK_TOP	equ	0080h
STACK_TOP2	equ	0100h

; BIOS data area (0040:0000 - 0040:00FF)
[BDA]	SEGMENT WIDTH=16, ALIGN=16, CLASS=VIRT, PURPOSE=DATA, COMBINE=COMMON

BDA_SEGMENT	equ	0040h

; Boot sector load location (0000:7C00)
BOOT_SEGMENT	equ	0000h
BOOT_OFFSET	equ	7C00h

; Interrupt vector table (0000:0000 - 0000:0400)
[IVT]	SEGMENT WIDTH=16, ALIGN=16, CLASS=VIRT, PURPOSE=DATA, COMBINE=COMMON

IVT_SEGMENT	equ	0000h

;  Default to CODE segment
[CODE]

SEGMENTS_DEFINED	equ	1
