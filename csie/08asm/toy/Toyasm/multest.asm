A	DW	3
B	DW	4
C	DW	5

; calculate A*B*C
main	ld	RA, A
	ld	RB, B
	ld	RC, C
	jl	RF, mul3
	st	RD, 0xFF
	hlt

; RD=RA*RB*RC
; return address is in RF
mul3	jl	RE, push	; push return address

	lda	RD, 0		; RD=0
	add	RD, RC, R0	; RD=RC	
	jl	RF, mul		; RC=RA*RB
	
	add	RA, RC, R0	; RA=RC=RA*RB
	add	RB, RD, R0	; RB=RD=RC
	jl	RF, mul

	add	RD, RC, R0	; move result to RD

	jl	RE, pop		; pop return address and return
	jr	RF
