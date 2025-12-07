; ╔══════════════════════════════════════════════╤═════════════════════════════╗
; ║ keyboard.inc                                 │ Research Machines VX/2 BIOS ║
; ╟──────────────────────────────────────────────┴─────────────────────────────╢
; ║ I/O ports and constants for the 8042 keyboard interface.                   ║
; ║ See [Service 3-26] for details.                                            ║
; ╚════════════════════════════════════════════════════════════════════════════╝

; ═╡ RW/8 ╞═╡ Keyboard controller data ╞════════════════════════════════════════
PORT_KBC_DATA	equ	60h

; ═╡ R-/8 ╞═╡ Port B (keyswitch/monitor select) ╞═══════════════════════════════
PORT_KBC_PORTB	equ	61h

; ═╡ R-/8 ╞═╡ Keyboard controller status ╞══════════════════════════════════════
PORT_KBC_STATUS	equ	64h

; Bitmasks for PORT_KBC_STATUS reads
KBC_STATUS_PERR	equ	80h	; keyboard data parity error
KBC_STATUS_RxTO	equ	40h	; recieve timeout
KBC_STATUS_TxTO	equ	20h	; transmit timeout
KBC_STATUS_INH	equ	10h	; keyboard comms inhibit
KBC_STATUS_A2	equ	08h	; A2 address line for last port write
KBC_STATUS_SYS	equ	04h	; Last reset type: 0=cold boot, 1=warm boot
KBC_STATUS_IBF	equ	02h	; input buffer full
KBC_STATUS_OBF	equ	01h	; output buffer full

; ═╡ -W/8 ╞═╡ Keyboard controller command ╞═════════════════════════════════════
PORT_KBC_CMD	equ	64h
