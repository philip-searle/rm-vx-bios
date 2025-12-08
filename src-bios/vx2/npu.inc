; ╔══════════════════════════════════════════════╤═════════════════════════════╗
; ║ npu.inc                                      │ Research Machines VX/2 BIOS ║
; ╟──────────────────────────────────────────────┴─────────────────────────────╢
; ║ I/O ports and constants for the Numeric Processing Unit (NPU) interface    ║
; ║ as implemented by the FE3000 chip.                                         ║
; ║                                                                            ║
; ║ Ports 0E8h-0EFh and 0F8h-0FFh are reserved for 286/287 private             ║
; ║ communication.  See [FE3001A manual], section 2.9 "Coprocessor Interface"  ║
; ║ for details of the co-processor I/O port interface.                        ║
; ╚════════════════════════════════════════════════════════════════════════════╝

; ═╡ -W/8 ╞═╡ Clear NPU busy flag ╞═════════════════════════════════════════════
; Write all-bits zero to clear 80287 BUSY flag.
PORT_287CLRBUSY	equ	0F0h

; ═╡ -W/8 ╞═╡ Reset ╞═══════════════════════════════════════════════════════════
; Write all-bits zero to reset 80287
PORT_287RESET	equ	0F1h
