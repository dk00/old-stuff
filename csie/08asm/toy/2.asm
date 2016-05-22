CYY_TZHUAN_VICTOR_R1 dw 0
CYY_TZHUAN_VICTOR_R2 dw 0
CYY_TZHUAN_VECTOR_ARRAY dup 32

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
	lda RC, 0
	lda	RA, CYY_TZHUAN_VECTOR_ARRAY

CYY_TZHUAN_VICTOR_LOOP ld R2, 255
	bz	R2, CYY_TZHUAN_VICTOR_EXIT
	sti	R2, RA
	add RA, RA, R1
	add RC, RC, R1
	bz	R0, CYY_TZHUAN_VICTOR_LOOP

CYY_TZHUAN_VICTOR_EXIT lda	RA, CYY_TZHUAN_VECTOR_ARRAY
	jl	RF, CNT0
	st	RB, 255
	hlt
