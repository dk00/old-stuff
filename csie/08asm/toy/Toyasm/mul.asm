
SIXTEEN	DW	16

; multiply RC=RA*RB
; return address is in RF
; it will modify R2, R3 and R4 as well
mul	jl	RE, push

	lda	RC, 0
	lda	R1, 1
	ld	R2, SIXTEEN	; R2 is i

m_loop	sub	R2, R2, R1
	shl	R3, RA, R2
	shr	R4, RB, R2
	and	R4, R4, R1
	bz	R4, m_end
	add	RC, RC, R3
m_end	bp	R2, m_loop

	jl	RE, pop
	jr	RF
