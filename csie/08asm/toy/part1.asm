t		dw	1000		;t=1000
div		sub	ra,ra,rc	;do{ra-=rc
		add	rb,rb,r1	;	rb++
		bp	ra,div		;}while(ra>0)
		add	ra,ra,rc	;ra+=rc
		sub	rb,rb,r1	;rb--
		jr	re			;return
bcd		lda	rb,0		;rb=0
		lda	r1,1		;r1=1
		lda	r4,4		;r1=1
		add	ra,ra,r1	;ra++
		ld	rc,t		;rc=1000
		jl	re,div		;rb+=ra/rc
		shl	rb,rb,r4	;rb<<=4
		lda	rc,100		;rc=100
		jl	re,div		;rb+=ra/rc
		shl	rb,rb,r4	;rb<<=4
		lda	rc,10		;rc=10
		jl	re,div		;rb+=ra/rc
		shl	rb,rb,r4	;rb<<=4
		lda	rc,1		;rc=1
		jl	re,div		;rb+=ra/rc
		jr	rf			;return
