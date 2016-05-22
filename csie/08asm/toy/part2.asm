cnt0	lda rb,0		;rb=0
		lda	r1,1		;r1=1
		bz	r0,c4		;goto c4
c3		ldi	r2,ra		;	r2=mem[ra]
		add	ra,ra,r1	;	ra++
		sub	rc,rc,r1	;	rc--
		lda	r3,1		;	r3=0x8000
c0		and r4,r3,r2	;		r4=r2&r3
		shl r3,r3,r1	;		r3<<=1
		bz 	r4,c1		;		if(!r4)
		bz	r0,c2		;
c1		add	rb,rb,r1	;		rb++
c2		bz	r3,c4		;	while(r3)
		bz	r0,c0		;
c4		bp 	rc,c3		;while(rc)
		jr	rf			;return
