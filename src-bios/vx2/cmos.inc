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

CMOS_EQUIPMENT		equ	14h

; ═╡ RW/8 ╞═╡ Data port ╞═══════════════════════════════════════════════════════
PORT_CMOS_DATA         equ     71h

; ──────────────────────────────────────────────────────────────────────────────
; Valid values for the CMOS_SHUTDOWN_REASON register
; [Compat] These differ significantly from the values used in the IBM BIOS!
SD_JMP_WITH_INT		equ	05h	; Reset (JMP to [40:67h] after resetting PIC)
SD_BLOCK_MOVE		equ	09h	; Return from int15 block move ([40:67h] is SS:SP)
SD_JMP_WITHOUT_INT	equ	0Ah	; Reset (JMP to [40:67h] without resetting PIC)

; ──────────────────────────────────────────────────────────────────────────────
; Subfields of the CMOS_EQUIPMENT register
CMOS_EQUIP_FD_COUNT	equ	0C0h	; Floppy disk count
CMOS_EQUIP_DISP_TYPE	equ	030h	; Display type (00=none, 01=CGA40, 10=CGA80, 11=MDA)
CMOS_EQUIP_DISP_INST	equ	008h	; Display adapter installed
CMOS_EQUIP_KEYB_INST	equ	004h	; Keyboard installed
CMOS_EQUIP_NPU_INST	equ	002h	; NPU installed
CMOS_EQUIP_RESERVED	equ	001h	; Always 1
