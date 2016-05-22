
A	DW	0
B	DW	1

	ld	RA, A
	ld	RB, B

loop	st	RA, 0xFF
	add	RA, RA, RB
	sub	RB, RA, RB
	bp	RA, loop

	hlt
