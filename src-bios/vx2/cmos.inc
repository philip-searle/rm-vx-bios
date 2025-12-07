; ╔══════════════════════════════════════════════╤═════════════════════════════╗
; ║ cmos.inc                                     │ Research Machines VX/2 BIOS ║
; ╟──────────────────────────────────────────────┴─────────────────────────────╢
; ║ I/O ports and constants for the Real-Time Clock (RTC).                     ║
; ║ The RTC function is provided by a 146818 chip, but it only handles the     ║
; ║ clock functionality.  System configuration is not stored in there (as it   ║
; ║ is in the IBM PC/AT); instead it is stored in the EEROM subsystem.         ║
; ║ See [Service 3-25].                                                        ║
; ╚════════════════════════════════════════════════════════════════════════════╝

; ═╡ R-/8 ╞═╡ Address port ╞════════════════════════════════════════════════════
; Needs setting after each data port access.
; NMI disable flag is in the high bit.
PORT_CMOS_ADDRESS      equ     70h

; ──────────────────────────────────────────────────────────────────────────────
; OR with register index to form value for CMOS_ADDRESS_PORT
NMI_ENABLE             equ     00h
NMI_DISABLE            equ     80h

; ──────────────────────────────────────────────────────────────────────────────
; CMOS register indexes
CMOS_RTC_SECONDS	equ	00h
CMOS_ALARM_SECONDS	equ	01h
CMOS_RTC_MINUTES	equ	02h
CMOS_ALARM_MINUTES	equ	03h
CMOS_RTC_HOURS		equ	04h
CMOS_ALARM_HOURS	equ	05h
CMOS_RTC_DAY_OF_WEEK	equ	06h
CMOS_RTC_DAY_OF_MONTH	equ	07h
CMOS_RTC_MONTH		equ	08h
CMOS_RTC_YEAR		equ	09h

CMOS_STATUS_A		equ	0Ah
CMOS_STATUS_B		equ	0Bh
CMOS_STATUS_C		equ	0Ch
CMOS_STATUS_D		equ	0Dh
CMOS_STATUS_DIAG	equ	0Eh
CMOS_SHUTDOWN_REASON	equ	0Fh

; ═╡ RW/8 ╞═╡ Data port ╞═══════════════════════════════════════════════════════
PORT_CMOS_DATA         equ     71h
