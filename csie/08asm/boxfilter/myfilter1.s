	.text
	.align	2
d9:	.word	_9						@	u32	d9[]={ ... }
d6:	.word	_6						@	u32	d6[]={ ... }
ret	.req	r0
ori	.req	r1
i	.req	r2
j	.req	r3
p	.req	r4
s	.req	r5
x	.req	r6
dt	.req	r9
	.macro 	div i,o,a
	mov		\o, \i, lsl #23
	ldr		\o,[dt, \o, lsr #21]
	mov		\a, \i, lsl #13
	bic		\a, \a,	#0x200000
	ldr		\a,[dt,	\a, lsr #21]
	orr		\o, \o,	\a, lsl #10
	ldr		\a,[dt,	\i, lsr #19]
	orr		\o, \o, \a, lsl #5
	.endm
	.macro	decode	i,o,a
	and		\a, \i, #0x3E0
	bic		\i, \i, #0x3E0
	add		\o, \o, \i
	add		\o, \o, \a, lsl #16
	.endm
	.global	myfilter
	.type	myfilter, %function
myfilter:							@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    stmfd	sp!,{r0-r12,lr}			@
	mov		r11, #480				@
	movs	i,	 #159				@	for(i=159 -> 0)
l0:									@	{
	ldr		r12, da					@
	mov		p,	 #0					@		p=0
	mov		x,	 #0					@		x=0
	beq		l00						@		if(i)
	ldrh	r7, [ori, r11]			@
	Decode	r7,  x,   r8			@			x+=decode(ori[i+1][0])
l00:ldreq	r12, db					@!
	cmp		i, 	 #159				@		if(i<159)
	beq		l01						@
	ldrh	r7, [ori, -r11]			@
	Decode	r7,  x,   r8			@			x+=decode(ori[i-1][0])
l01:ldrh	r7, [ori],#2			@
	Decode	r7,  x,   r8			@		x+=decode(ori[i][0])
	mov		s,   x					@		s=x
	ldreq	r12, db					@!
	movs	j,   #239				@		for(j=239 ->0)
l1:									@		{
	sub		s,   s,   p				@			s-=p
	sub		p,   s,   x				@			p=s-c
	mov		x,   #0					@			x=0
	subeq	r12, r12, #48			@!
	beq		l2						@			if(j)
	cmp		i, 	 #159				@			{
	beq		l10						@				if(i)
	ldrh	r7, [r1,  -r11]			@					x+=decode(ori[i-1][j+1])
	Decode	r7,  x,   r8			@
l10:cmp		i, 	 #0					@
	beq		l11						@
	ldrh	r7, [r1,  r11]			@				if(i<159)
	Decode	r7,  x,   r8			@					x+=decode(ori[i+1][j+1])
l11:ldrh	r7, [r1], #2			@
	Decode	r7,  x,   r8			@				x+=decode(ori[i][j+1])
	add		s,   s,   x				@				c+=x
l2:									@			}
@	b		test					@!
	bx		r12						@!
back:
	strh	r7, [ret],#2			@			ret[i][j]=s/9
	subs	r3,  r3,  #1			@
	bhs		l1						@		}
	subs	i,   i,   #1			@
	bhs		l0						@	}
exit:								@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	ldmfd	sp!,{r0-r12,lr}			@
    bx	lr							@	return
divb:
	and		r8, s,  #0xF800000
	mov		r7, s,  lsr #2
	bic		r7, r7, #0x3E0
	orr		r7, r7, r8, lsr #18
	add		r12, r12, #48
	ldr		dt,  d6
	b		back
	b		back
	b		back
	b		back
	b		back
	b		back
	Div		s,   r7,  r8
	b		back
diva:
	ldr		dt,  d6
	Div		s,   r7,  r8
	ldr		dt,  d9
	add		r12, r12, #48
	b		back
test:
	Div		s,   r7,  r8
	b		back
da:	.word	diva
db:	.word	divb
	.size	myfilter, .-myfilter
	.ident	"GCC: (GNU) 3.3.2"
	.data							@60800(15200) 573040(307040)
	.align	2
_9:	.word	0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,19,20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,22,23,23,23,23,23,23,23,23,23,24,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,30,30,30,30,30,30,30,30,30,31,31,31,31,31,31,31,31,31
_6:	.word	0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,11,11,11,11,11,11,12,12,12,12,12,12,13,13,13,13,13,13,14,14,14,14,14,14,15,15,15,15,15,15,16,16,16,16,16,16,17,17,17,17,17,17,18,18,18,18,18,18,19,19,19,19,19,19,20,20,20,20,20,20,21,21,21,21,21,21,22,22,22,22,22,22,23,23,23,23,23,23,24,24,24,24,24,24,25,25,25,25,25,25,26,26,26,26,26,26,27,27,27,27,27,27,28,28,28,28,28,28,29,29,29,29,29,29,30,30,30,30,30,30,31,31,31,31,31,31
