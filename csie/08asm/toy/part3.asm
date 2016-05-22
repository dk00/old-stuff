s		dup	33			;short s[32]
		lda	rc,s		;rc=s
		lda	r1,1		;r1=1
s0		ld	r2,0xff		;{	read(r2)
		bz	r2,s1		;	if(!r2)break
		sti	r2,rc		;	mem[rc]=r2
		add	rc,rc,r1	;	rc++
		bz	r0,s0		;}while(1)
s1		lda	ra,s		;ra=s
		sub	rc,rc,ra	;rc-=ra
		jl	rf,cnt0		;rb=cnt0(ra,rc)
		add	ra,r0,rb	;ra=rb
		jl	rf,bcd		;rb=bcd(ra)
		st	rb,0xff		;print rb
		hlt
