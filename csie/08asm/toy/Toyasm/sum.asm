
	lda	RC, 0
loop	ld	RA, 0xFF
	bz	RA, exit
	add	RC, RC, RA
	bz	R0, loop

exit	st	RC, 0xFF
	hlt
