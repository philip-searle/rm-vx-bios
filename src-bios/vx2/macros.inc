
; ===========================================================================
;
; Macro definitions used throughout the BIOS code.
;
; ===========================================================================

EUROASM FPU=ON
EUROASM LISTINCLUDE=OFF, LISTVAR=ON, LISTMACRO=OFF, LISTREPEAT=OFF
EUROASM AUTOALIGN=OFF, AUTOSEGMENT=OFF

; ---------------------------------------------------------------------
; FillRom address, fill
;
; Advances the current location to the specified address, filling any space
; with the byte provided.
FillRom		%macro
		%if (%1 - offset#$ - %XxxBase) > 0 && (%1 - offset#$ - %XxxBase) <= 2147483647
		d	(%1 - offset#$ - %XxxBase) * byte %2
		%else
		; Don't raise an error if out of range, some modules
		; are temporarily out of range until the final assembler
		; pass where they settle down to a reasonable value.
		; Not sure how to detect the final pass to suppress the
		; error message, so for now I'm relying on the linker's
		; assertions to detect public symbols shifting around.
		;%error	XXXX: %1 - offset#$ - %XxxBase > MAX
		%endif
		%endmacro

; ---------------------------------------------------------------------
; PUBLIC_COMPAT symbol [, symbol...]
;
; Makes the supplied symbols available as PUBLIC exports, but with the
; name prefixed with a tilde (~).  Intended for symbols which aren't
; intended to be referenced from other BIOS modules, but which need to
; be made available so the linker can assert that their addresses
; match publicly-known values.
PUBLIC_COMPAT	%macro
symbol		%for 1..%#
~%1		equ	%1
		PUBLIC	~%1
		%shift
		%endfor
		%endmacro

; ---------------------------------------------------------------------
; AssertEqual lhs, rhs, message
;
; Raises an error if the two arguments are not equal in value
AssertEqual	%macro
		%if %1 != %2
		%error %1 != %2: %3
		%endif
		%endmacro

; ---------------------------------------------------------------------
; Delay count
;
; Inserts short jumps to delay execution by count*7 clocks.
Delay		%macro
i		%for	1..%1
		jmps	$+2
		%endfor
%endmacro

; ---------------------------------------------------------------------
; FillerNop
;
; Apparently 'useless' nop inserted after a jmp where the original assembler
; couldn't determine the jump range.  EuroASM can reduce these jmp instructions
; to their smallest possible representation with its multi-pass behavour, but
; the assembler GRiD used was not so capable.  This macro allows us to pad out
; such jmp instances to obtain a bit-identical ROM, with the possibility of
; later making this macro a true no-op and saving some space in the ROM.
FillerNop	%macro
		nop
%endmacro

; ---------------------------------------------------------------------
; Unused symbol
;
; Suppresses warning W2101 for the specified symbol.  Useful for code that will
; be referenced by code that has not yet been written, or for genuinely unused
; (dead) code.
Unused		%macro
		EUROASM	PUSH, NOWARN=2101
Unused_%.:	equ	%1
		EUROASM	POP
		%endmacro

; ---------------------------------------------------------------------
; Macro to convert word literal into big-endian format
dw_b	%macro
	db	(%1 >> 8) & 0FFh
	db	(%1 >> 0) & 0FFh
	%endmacro
