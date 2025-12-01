
RESET		PROGRAM	OutFile=reset.obj

		include	"macros.inc"
		include	"segments.inc"
		include	"segments/bda.inc"
		include	"segments/ivt.inc"

		PUBLIC	Reset_Compat

Reset_Compat	PROC
		ENDPROC	Reset_Compat

ENDPROGRAM	RESET
