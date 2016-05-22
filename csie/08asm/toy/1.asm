CYY_TZHUAN_VICTOR_R1 dw 0
CYY_TZHUAN_VICTOR_R2 dw 0

; main
	lda	R1, 0
	lda	R2, 0
	lda	R3, 0
	lda	R4, 0
	lda	R5, 0
	lda	R6, 0
	lda	R7, 0
	lda	R8, 0
	lda	R9, 0
	lda	RA, 0
	lda	RB, 0
	lda	RC, 0
	lda	RD, 0
	lda	RE, 0
	lda	RF, 0

	lda	R1, 1
	ld	R2, 255
CYY_TZHUAN_VICTOR_LOOP ld RA, 255
	st	R1, CYY_TZHUAN_VICTOR_R1
	st	R2, CYY_TZHUAN_VICTOR_R2
	jl	RF, BCD
	st	RB, 255
	ld	R2, CYY_TZHUAN_VICTOR_R2
	ld	R1, CYY_TZHUAN_VICTOR_R1
	sub	R2, R2, R1
	bp	R2, CYY_TZHUAN_VICTOR_LOOP
	hlt
