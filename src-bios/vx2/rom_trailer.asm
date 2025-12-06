
ROM_TRAILER	PROGRAM	OutFile=rom_trailer.obj

		include	"macros.inc"
		include	"segments.inc"
		include	"bios-version.inc"

		EXTERN	Reset_Actual

		PUBLIC	Reset, ReleaseMarker, MachineId

; ══════════════════════════════════════════════════════════════════════════════
; Power-On Reset Vector at F000:FFF0
; [Public] CPU reset vector is top of address space minus 16 bytes.
; AT BIOS calls this P_O_R (POWER ON RESET).
; Must be a far jump to set CS to the correct value.
; ══════════════════════════════════════════════════════════════════════════════
Reset		jmpf	Reset_Actual

; ══════════════════════════════════════════════════════════════════════════════
; BIOS identification in last 11 bytes
; ══════════════════════════════════════════════════════════════════════════════

		; [Public] IBM BIOS stores ROM date at F000:FFF5
		; (AT BIOS calls this 'RELEASE MARKER')
ReleaseMarker	db	%BIOS_DATE
		db	00h		; Unused byte

		; [Public] IBM BIOS stores machine ID byte at F000:FFFE
MachineId	db	0FCh		; Model FC == IBM AT (6 MHz)
		db	00		; Submodel 00 == no specific submodel

ENDPROGRAM	ROM_TRAILER
