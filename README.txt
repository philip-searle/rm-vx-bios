Research Machines VX2 BIOS Disassembly
======================================

This is a work-in-progress project to create a documented assembly listing of
the RM VX2 BIOS that can be assembled into a byte-identical image of the
original ROMs.

This project is using EuroAssembler (<https://euroassembler.eu/eadoc/>),
MakePP (<http://makepp.sourceforge.net/>), and Perl 5.

Refer to BUILDING.txt for how to build the BIOS image.

References
==========

Some code comments are prefixed with a tag in square brackets.  These denote
important compatibility constraints or restrictions on behaviour imposed on the
BIOS, as well as references to GRiD documentation.  The possible tags are:

 * [Public]
   Identifies locations/APIs mentioned in publicly available documentation,
   e.g. Ralph Brown's Interrupt List or IBM Technical Reference.

 * [Compat]
   Identifies places where data/code layout must remain fixed for compatibility
   with software that relies on undocumented or semi-documented functionality.
