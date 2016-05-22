	.text							@	4841248-4839744
	.align	2						@	3776816-3663960-3550720
d9:	.word	_9						@	u32	d9[]={ ... }
d6:	.word	_6						@	u32	d6[]={ ... }
ret	.req	r0
ori	.req	r1
i	.req	r2
dt6	.req	r3
p	.req	r4
s	.req	r5
x	.req	r6
dt9	.req	r9
m0	.req	r10
	.macro 	div 	i,o,a,d
	mov		\o, \i, lsl #23
	ldr		\o,[\d, \o, lsr #21]
	and		\a, \i, m0
	ldr		\a,[\d,	\a, lsr #8]
	orr		\o, \o,	\a, lsl #10
	ldr		\a,[\d,	\i, lsr #19]
	orr		\o, \o, \a, lsl #5
	.endm
	.macro	div9	i,o,a
	mov		\o, \i, lsl #13
	mov		\a, \o, lsr #5
	.endm
	.macro	div4 	i,o,a
	and		\a, \i, #0xF800000
	mov		\o, \i, lsr #2
	bic		\o, \o, #0x3E0
	orr		\o, \o, \a, lsr #18
	.endm
	.macro	decode 	i,o,a
	and		\a, \i, #0x3E0
	bic		\i, \i, #0x3E0
	add		\o, \o, \i
	add		\o, \o, \a, lsl #16
	.endm
	.macro	load2	o
	ldrh	r7, [ori, r11]			@
	Decode	r7,  \o,   r8			@		s+=decode(ori[i+1][0])
	.endm
	.macro	load0	o
	ldrh	r7, [ori, -r11]			@
	Decode	r7,  \o,   r8			@		s+=decode(ori[i-1][0])
	.endm
	.macro	loadb	o
	mov		\o,	 #0					@		x=0
	load0	\o
	ldrh	r7, [ori],#2			@
	Decode	r7,  \o,   r8			@		s+=decode(ori[i][0])
	.endm
	.macro	loada	o
	mov		\o,	 #0					@		x=0
	load2	\o
	ldrh	r7, [ori],#2			@
	Decode	r7,  \o,   r8			@		s+=decode(ori[i][0])
	.endm
	.macro	load	o
	mov		\o,	 #0					@		x=0
	load0	\o
	load2	\o
	ldrh	r7, [ori],#2			@
	Decode	r7,  \o,   r8			@		s+=decode(ori[i][0])
	.endm
	.global	myfilter
	.type	myfilter, %function
myfilter:							@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    stmfd	sp!,{r0-r12,lr}			@
	mov		r11, #480				@
	ldr		dt6, d6					@	set div6 table
	ldr		dt9, d9					@	set div6 table
	mov		m0,  #0x3FC00			@
	orr		m0,  m0, #0x40000
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mov		p,	 #0					@	p=0
	loada	s
	loada	x
	add		s,   s,   x				@	s+=x
	Div4	s,   r7,  r8
	strh	r7, [ret],#2			@	ret[i][j]=s/4
	.rept	238						@	{
	sub		s,   s,   p				@			s-=p
	sub		p,   s,   x				@			p=s-x
	loada	x
	add		s,   s,   x				@			s+=x
	Div		s,   r7,  r8,  dt6
	strh	r7, [ret],#2			@			ret[i][j]=s/6
	.endr							@	}
	sub		s,   s,   p				@	s-=p
	Div4	s,   r7,  r8
	strh	r7, [ret],#2			@	ret[i][j]=s/4
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mov		i,	 #157				@	for(i=157 -> 0)
l0:									@	{
	mov		p,	 #0					@		p=0
	load	s
	load	x
	add		s,   x,   s				@		s+=x
	Div		s,   r7,  r8, dt6
	strh	r7, [ret],#2			@		ret[i][j]=s/6
	.rept	238
	sub		s,   s,   p				@		s-=p
	sub		p,   s,   x				@		p=s-x
	load	x
	add		s,   s,   x				@		s+=x
	Div		s,   r7,  r8, dt9
	strh	r7, [ret],#2			@		ret[i][j]=s/9
	.endr
	sub		s,   s,   p				@		s-=p
	Div		s,   r7,  r8, dt6
	strh	r7, [ret],#2			@		ret[i][j]=s/6
	subs	i,   i,   #1			@
	bhs		l0						@	}
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mov		p,	 #0					@	p=0
	loadb	s
	loadb	x
	add		s,   s,   x				@	s+=x
	Div4	s,   r7,  r8
	strh	r7, [ret],#2			@	ret[i][j]=s/4
	.rept	238						@	{
	sub		s,   s,   p				@			s-=p
	sub		p,   s,   x				@			p=s-x
	loadb	x
	add		s,   s,   x				@			s+=x
	Div		s,   r7,  r8,  dt6
	strh	r7, [ret],#2			@			ret[i][j]=s/6
	.endr							@	}
	sub		s,   s,   p				@	s-=p
	Div4	s,   r7,  r8
	strh	r7, [ret],#2			@	ret[i][j]=s/4
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
exit:								@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	ldmfd	sp!,{r0-r12,lr}			@
    bx	lr							@	return
	.size	myfilter, .-myfilter
	.ident	"GCC: (GNU) 3.3.2"
	.data							@60800(15200) 573040(307040)
_6:	.word	0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,11,11,11,11,11,11,12,12,12,12,12,12,13,13,13,13,13,13,14,14,14,14,14,14,15,15,15,15,15,15,16,16,16,16,16,16,17,17,17,17,17,17,18,18,18,18,18,18,19,19,19,19,19,19,20,20,20,20,20,20,21,21,21,21,21,21,22,22,22,22,22,22,23,23,23,23,23,23,24,24,24,24,24,24,25,25,25,25,25,25,26,26,26,26,26,26,27,27,27,27,27,27,28,28,28,28,28,28,29,29,29,29,29,29,30,30,30,30,30,30,31,31,31,31,31,31
_9:	.word	0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,19,20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,22,23,23,23,23,23,23,23,23,23,24,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,30,30,30,30,30,30,30,30,30,31,31,31,31,31,31,31,31,31

