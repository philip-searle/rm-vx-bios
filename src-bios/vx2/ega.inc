; ╔══════════════════════════════════════════════╤═════════════════════════════╗
; ║ ega.inc                                      │ Research Machines VX/2 BIOS ║
; ╟──────────────────────────────────────────────┴─────────────────────────────╢
; ║ I/O ports for the Paradise Systems PEGA 2 video system provided with the   ║
; ║ RM X Series machines.                                                      ║
; ╚════════════════════════════════════════════════════════════════════════════╝

; ═╡ RW/8 ╞═╡ IBM onboard VGA - GLOBAL ENABLE REGISTER ╞════════════════════════
; Note: Only accessible in setup mode (port 46E8h bit 4 = 1).
PORT_VGA_GLOBAL_ENABLE		equ	102h
VGA_GLOBAL_DISABLE		equ	000h
VGA_GLOBAL_ENABLE		equ	001h
VGA_GLOBAL_ENABLE_RESERVED	equ	0FEh

; ═╡ RW/8 ╞═╡ IBM VGA adaptor - VIDEO ADAPTOR ENABLE ╞══════════════════════════
; See also PORT_VGA_SUBSYS_ENABLE
PORT_VGA_ADAPTOR_ENABLE		equ	46E8h
VGA_ADAPTOR_DISABLE		equ	000h	; disable ROM, display memory, all IO except 102h/46E8h
VGA_ADAPTOR_SETUP		equ	010h	; enable IO ports 102h/46E8h, and BIOS ROM but disable display RAM
VGA_ADAPTOR_ENABLE		equ	008h	; enable display adaptor IO access
VGA_ADAPTOR_ROMPAGE2		equ	004h	; PEGA2-specific
VGA_ADAPTOR_ROMPAGE1		equ	002h	; PEGA2-specific
VGA_ADAPTOR_ROMPAGE0		equ	0E1h	; PEGA2-specific

; ═╡ RW/8 ╞═╡ Compatibility ports - IBM MDA ╞═══════════════════════════════════
PORT_MDA_CRTC_ADDR	equ	3B4h
PORT_MDA_CRTC_DATA	equ	3B5h
PORT_MDA_MODE_CTRL	equ	3B8h
PORT_MDA_STATUS		equ	3BAh
PORT_MDA_CLEAR_LIGHTPEN	equ	3BBh

; ═╡ RW/8 ╞═╡ Compatibility ports - IBM CGA ╞═══════════════════════════════════
PORT_CGA_CRTC_ADDR	equ	3D4h
PORT_CGA_CRTC_DATA	equ	3D5h
PORT_CGA_MODE_CTRL	equ	3D8h
PORT_CGA_COLOR_CTRL	equ	3D9h
PORT_CGA_STATUS		equ	3DAh
PORT_CGA_CLEAR_LIGHTPEN	equ	3DBh

; ═╡ -W/8 ╞═╡ Attribute control index/data register - IBM EGA ╞═════════════════
; Writes alternate between index and data register.  Clear the flip-flop that
; controls write destination by reading from PORT_MDA_STATUS or PORT_CGA_STATUS.
PORT_EGA_ATC_REGISTER	equ	3C0h

; ═╡ -W/8 ╞═╡ Miscellaneous controle register - IBM EGA ╞═══════════════════════
PORT_EGA_MISC_CONTROL	equ	3C2h
EGA_MISC_CTRL_SELECT3BX	equ	01h	; 1=3BxH (emulate MDA); 0=3DxH (CGA)
EGA_MISC_CTRL_ENABLERAM	equ	02h	; 1=enable RAM
EGA_MISC_CTRL_DOTCLK	equ	0Ch	; 00=14mHz; 01=16mHz; 10=external
EGA_MISC_CTRL_FEATOUT	equ	10h	; 1=feature output; 0=internal output
EGA_MISC_CTRL_OE_PAGE	equ	20h	; Page bit for odd/even mode
EGA_MISC_CTRL_POLARITYH	equ	40h	; Horiz retrace polarity: 1=negative
EGA_MISC_CTRL_POLARITYV	equ	80h	; Vert retrace polarity: 1=negative

; ═╡ RW/8 ╞═╡ Video subsystem enable - IBM EGA ╞════════════════════════════════
; See also PORT_VGA_ADAPTOR_ENABLE
PORT_VGA_SUBSYS_ENABLE	equ	3C3h
VGA_SUBSYS_DISABLE		equ	000h	; vga adaptor disabled
VGA_SUBSYS_ENABLE_03C3		equ	001h	; select video subsystem (address 03C3h)
VGA_SUBSYS_ENABLE_46E8		equ	008h	; select video subsystem (address 46E8h)
VGA_SUBSYS_ENABLE_RESERVED	equ	0F6h

; ═╡ -W/8 ╞═╡ Sequencer index register - IBM EGA ╞══════════════════════════════
PORT_EGA_SEQ_INDEX	equ	3C4h

; ═╡ -W/8 ╞═╡ Sequencer data register - IBM EGA ╞═══════════════════════════════
POT_EGA_SEQ_DATA	equ	3C5h

; ═╡ -W/8 ╞═╡ Graphics 2 position register - IBM EGA ╞══════════════════════════
PORT_EGA_GRAPHICS2_POS	equ	3CAh

; ═╡ -W/8 ╞═╡ Graphics 1 position register - IBM EGA ╞══════════════════════════
PORT_EGA_GRAPHICS1_POS	equ	3CCh

; ═╡ -W/8 ╞═╡ Graphics address register - IBM EGA ╞═════════════════════════════
PORT_EGA_GRAPHICS_INDEX	equ	3CEh

; ═╡ -W/8 ╞═╡ Graphics data register - IBM EGA ╞════════════════════════════════
PORT_EGA_GRAPHICS_DATA	equ	3CFh

; ═╡ -W/8 ╞═╡ Paradise register- PEGA2 ╞════════════════════════════════════════
; PEGA2-specific.  Available at the MDA and CGA lightpen register addresses
; after reading from the corresponding mode control port twice.  The config
; register is automatically locked after writing.
PORT_PEGA_PARADISE_MDA	equ	3BBh
PORT_PEGA_PARADISE_CGA	equ	3DBh
PEGA_PARADISE_IO_MAP	equ	80h	; 1=MDA I/O mapping, 0=CGA
PEGA_PARADISE_OLIVETTI	equ	40h	; 1=Mono Olivetti monitor, 0=colour
PEGA_PARADISE_ALPHADOTS	equ	20h	; 1=9 dots/char, 0=8 dots/char
PEGA_PARADISE_CLOCKSEL	equ	10h	; 1=high speeed, 0=normal
PEGA_PARADISE_EXTRAREGS	equ	08h	; 1=enable AT&T/M24/Plantronics regs
PEGA_PARADISE_FLICKER	equ	04h	; 1=respect video enable, 0=no flicker
PEGA_PARADISE_LOCKCRTC	equ	02h	; 1=lock CRTC registers 0-11h
PEGA_PARADISE_CHARCLK	equ	01h	; 1=force 80-column, 0=enable 40-column

; ═╡ UnlockParadise [MDA|CGA] ╞═════════════════════════════════════════════════
; Macro that unlocks the PEGA Paradise register.  Pass in either MDA or CGA to
; specify whether the Paradise register is made available at port 3BBh or 3DBh.
; Output new value to DX immediately: the next I/O operation will cause the
; register to relock.
UnlockParadise	%macro	UnlockPort, Port
		mov	dx, %UnlockPort
		in	al, dx		; Read twice to unlock port
		in	al, dx
		mov	dx, %Port
%endmacro
