; ╔══════════════════════════════════════════════╤═════════════════════════════╗
; ║ pic.inc                                      │ Research Machines VX/2 BIOS ║
; ╟──────────────────────────────────────────────┴─────────────────────────────╢
; ║ I/O ports and constants for the Programmable Interrupt Controller.         ║
; ║ See [Service 3-21].                                                        ║
; ╚════════════════════════════════════════════════════════════════════════════╝

; ═╡ -W/8 ╞═╡ Control ports ╞═══════════════════════════════════════════════════
PORT_PIC1_CTRL	equ	20h
PORT_PIC2_CTRL	equ	0A0h

; Initialization control words after ICW1 go to alternate port
PORT_PIC1_CTRL2	equ	21h
PORT_PIC2_CTRL2	equ	0A1h

; ═╡ RW/8 ╞═╡ IRQ mask registers ╞══════════════════════════════════════════════
PORT_PIC1_MASK	equ	21h
PORT_PIC2_MASK	equ	0A1h

; ──────────────────────────────────────────────────────────────────────────────
; Command to issue to PIC to complete IRQ
NONSPECIFIC_EOI	equ	20h

; ──────────────────────────────────────────────────────────────────────────────
; IRQ assignments, PIC1 mask values [Service 3-21]
IRQ_TIMER	equ	0y00000001
IRQ_KEYBOARD	equ	0y00000010
IRQ_CASCADE	equ	0y00000100	; not a real IRQ
;			0y00001000 Not allocated
;			0y00010000 COM1 (serial port)
;			0y00100000 Not allocated
IRQ_FDC		equ	0y01000000
;			0y10000000 Parallel port

; ──────────────────────────────────────────────────────────────────────────────
; IRQ assignments, PIC2 mask values [TechRef 5-3]
IRQ_RTC		equ	0y00000001
IRQ_9		equ	0y00000010	; actually wired to IRQ2 line in hardware
;			0y00000100 Not allocated
;			0y00001000 Not allocated
;			0y00010000 Not allocated
IRQ_NPU		equ	0y00100000
IRQ_HDC		equ	0y01000000
;			0y10000000 Not allocated
