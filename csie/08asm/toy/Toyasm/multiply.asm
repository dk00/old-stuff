
A 	DW	3
B 	DW	9
C	DW	0

	ld 	RA, A
	ld 	RB, B
	ld 	RC, C
	lda	R1, 1
loop	bz	RA, exit
	add	RC, RC, RB
	sub	RA, RA, R1
	bz	R0, loop

exit	st	RC, 0xFF
	hlt
