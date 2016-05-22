
A	DW	3
B	DW	9
C	DW	0
SIXTEEN	DW	16

	ld	RA, A
	ld	RB, B
	ld	RC, C
	lda	R1, 1
	ld	R2, SIXTEEN	; R2 is i

loop	sub	R2, R2, R1
	shl	R3, RA, R2
	shr	R4, RB, R2
	and	R4, R4, R1
	bz	R4, end
	add	RC, RC, R3
end	bp	R2, loop

	st	RC, 0xFF
	hlt

