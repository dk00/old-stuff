A	DW	1
B	DW	2
C	DW	3
D	DW	4

main	ld	RF, A
	jl	RE, push

	ld	RF, B
	jl	RE, push

	jl	RF, pop
	st	R5, 0xFF

	jl	RE, pop
	st	RF, 0xFF

	jl	RE, pop
	st	RF, 0xFF

	hlt
