STK_TOP	DW	0xFF

; these procedures will use R8, R9
; return address is assumed to be in RE, instead of RF

; push RF into stack
push	lda	R8, 1
	ld	R9, STK_TOP
	sub	R9, R9, R8
	st	R9, STK_TOP
	sti	RF, R9
	jr	RE

; pop and return [top] to RF
pop	lda	R8, 0xFF
	ld	R9, STK_TOP
	sub	R8, R8, R9
	bz	R8, popexit
	ldi	RF, R9
	lda	R8, 1
	add	R9, R9, R8
	st	R9, STK_TOP
popexit	jr	RE

; the size of the stack, the result is in R9
stksize	lda	R8, 0xFF
	ld	R9, STK_TOP
	sub	R9, R8, R9
	jr	RE


