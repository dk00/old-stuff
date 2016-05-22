
A	DUP	32

	lda	R1, 1
	lda	RA, A
	lda	RC, 0

read	ld	RD, 0xFF
	bz	RD, exit
	add	R2, RA, RC
	sti	RD, R2
	add	RC, RC, R1
	bz	R0, read

exit	jl	RF, printr
	hlt

; print reverse
; starting address must be placed at RA
; number of elements must be placed at RC
printr	sub	RC, RC, R1
	add	R2, RA, RC
	ldi	RD, R2
	st	RD, 0xFF
	bp	RC, printr
	bz	RC, printr
return	jr	RF
