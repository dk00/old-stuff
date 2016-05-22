ori	.req	r1
rt0	.req	r0
rt1	.req	r1
x0	.req	r2
x1	.req	r3
x2	.req	r4
x3	.req	r5
x4	.req	r6
x5	.req	r7
x6	.req	r8
x7	.req	r9
x8	.req	r10
t0	.req	r11
t1	.req	r12
	.macro 	div 	i,o,d,a
		mov		\o, \i, lsl #23
		ldrb	\o,[\d, \o, lsr #23]
		mov		\a, \i, lsl #13
		ldrb	\a,[\d,	\a, lsr #23]
		orr		\o, \o,	\a, lsl #10
		ldrb	\a,[\d,	\i, lsr #21]
		orr		\o, \o, \a, lsl #5
	.endm
	.macro	div4 	i,o,a
		and		\a, \i, #0xF800000
		mov		\o, \i, lsr #2
		bic		\o, \o, #0x3E0
		orr		\o, \o, \a, lsr #18
		bic		\o, \o, #0xFF0000
		bic		\o, \o, #0xFF000000
	.endm
	.macro	dec		o
		and		sp, \o, #0x3E0
		bic		\o, \o, #0x3E0
		orr		\o, \o, sp, lsl #16
	.endm
	.macro	load3	t,a,b,c,d,e
		.irp	x,\c,\d,\e
			ldrh	\x, [ori],#2
			Dec		\x
		.endr
		add		\b, \b, \c
		add		\a, \a, \b
		add		\b, \b, \d
		add		\d, \d, \e
		add		\c, \c, \d
	.endm
	.macro	load4	t,a,b,c,d,e,f
		Load3	\t,\a,\b,\c,\d,\e
		ldrh	\f,[ori],#2
		Dec		\f
		add		\d, \d, \f
		stmia	\t,{\a,\b,\c,\d}
		add		\t, \t, #32
	.endm
	.macro	load	t
		mov		x0, #0
		ldrh	x1,[ori],#2
		Dec		x1
		.rept	29
			Load4	\t, x0, x1, x4, x5, x2, x3
			Load4	\t, x2, x3, x4, x5, x0, x1
		.endr
		Load4	\t, x0, x1, x4, x5, x2, x3
		Load3	\t, x2, x3, x4, x5, x0
		stmia	\t,{x2,x3,x4,x5}
	.endm
	.macro	addm	a,b,c,d,e,f,g,h
		add		\a, \a, \e
		add		\b, \b, \f
		add		\c, \c, \g
		add		\d, \d, \h
	.endm
	.macro	save	o,a,b,c,d,e,pre,end,si
		.if		\si>0
		sub		lr, lr, #192
		.endif
		.if		\pre>0
		.if		\si>0
		Div4	\a, \e, sp
		.else
		sub		lr, lr, #192
		Div		\a, \e, lr, sp
		add		lr, lr, #192
		.endif
		.else
		Div		\a, \e, lr, sp
		.endif
		Div		\b, \a, lr, sp
		Div		\c, \b, lr, sp
		.if		\end>0
		.if		\si>0
		sub		lr, lr, #192
		Div4	\d, \c, sp
		add		lr, lr, #192
		.else
		sub		lr, lr, #192
		Div		\d, \c, lr, sp
		add		lr, lr, #192
		.endif
		.else
		Div		\d, \c, lr, sp
		.endif
		orr		\a, \e, \a, lsl #16
		orr		\b, \b, \c, lsl #16
		stmia	\o!,{\a,\b}
		.if		\si>0
		add		lr, lr, #192
		.endif
	.endm
	.macro	Go		u,v,o0,o1,pre,end
		ldmia	\u!,{x0,x1,x2,x3,x4,x5,x6,x7}
		Addm	x0, x1, x2, x3, x4, x5, x6, x7
		ldmia	\v!,{x4,x5,x6,x7}
		Addm	x4, x5, x6, x7, x0, x1, x2, x3
		Save	\o0,x4, x5, x6, x7, x8, 1, 0, 0
		.if		\end>0
		mov		x4, x0
		mov		x5, x1
		mov		x6, x2
		mov		x7, x3
		add		\v, \v, #16
		.else
		ldmia	\v!,{x4,x5,x6,x7}
		Addm	x4, x5, x6, x7, x0, x1, x2, x3
		.endif
		Save	\o1,x4, x5, x6, x7, x8, 1, 0, \pre+\end
		.rept	58
		ldmia	\u!,{x0,x1,x2,x3,x4,x5,x6,x7}
		Addm	x0, x1, x2, x3, x4, x5, x6, x7
		ldmia	\v!,{x4,x5,x6,x7}
		Addm	x4, x5, x6, x7, x0, x1, x2, x3
		Save	\o0,x4, x5, x6, x7, x8, 0, 0, 0
		.if		\end>0
		mov		x4, x0
		mov		x5, x1
		mov		x6, x2
		mov		x7, x3
		add		\v, \v, #16
		.else
		ldmia	\v!,{x4,x5,x6,x7}
		Addm	x4, x5, x6, x7, x0, x1, x2, x3
		.endif
		Save	\o1,x4, x5, x6, x7, x8, 0, 0, \pre+\end
		.endr
		ldmia	\u!,{x0,x1,x2,x3,x4,x5,x6,x7}
		Addm	x0, x1, x2, x3, x4, x5, x6, x7
		ldmia	\v!,{x4,x5,x6,x7}
		Addm	x4, x5, x6, x7, x0, x1, x2, x3
		Save	\o0,x4, x5, x6, x7, x8, 0, 1, 0
		.if		\end>0
		mov		x4, x0
		mov		x5, x1
		mov		x6, x2
		mov		x7, x3
		add		\v, \v, #16
		.else
		ldmia	\v!,{x4,x5,x6,x7}
		Addm	x4, x5, x6, x7, x0, x1, x2, x3
		.endif
		Save	\o1,x4, x5, x6, x7, x8, 0, 1, \pre+\end
	.endm
	.text
	.align	4
_t0:.word	_1
_t2:.word	_2
_sp:.word	_0
d6:	.byte	0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,11,11,11,11,11,11,12,12,12,12,12,12,13,13,13,13,13,13,14,14,14,14,14,14,15,15,15,15,15,15,16,16,16,16,16,16,17,17,17,17,17,17,18,18,18,18,18,18,19,19,19,19,19,19,20,20,20,20,20,20,21,21,21,21,21,21,22,22,22,22,22,22,23,23,23,23,23,23,24,24,24,24,24,24,25,25,25,25,25,25,26,26,26,26,26,26,27,27,27,27,27,27,28,28,28,28,28,28,29,29,29,29,29,29,30,30,30,30,30,30,31,31,31,31,31,31
d9:	.byte	0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,19,20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,22,23,23,23,23,23,23,23,23,23,24,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,30,30,30,30,30,30,30,30,30,31,31,31,31,31,31,31,31,31
	.global	myfilter
	.type	myfilter, %function
myfilter:
    stmfd	sp!,{r0-r12,lr}
	ldr		t0,  _t0
	ldr		t1,  _t2
	sub		r2,  t0,  #64
	str		sp, [r2,  #8]
	str		r0, [r2]
	adr		lr,  d9
	mov		x1,  #38
	str		x1, [r2,  #4]
	add		t0,  t0,  #16
	Load	t0
	sub		t0,  t0,  #1904

	Load	t0
	sub		t0,  t0,  #1888
	Load	t1
	sub		t1,  t1,  #1888
	sub		sp,  t0,  #64
	swp		rt0, ori,[sp]
	add		rt1, rt0, #480
	Go		t0,  t1, rt1, rt0, 1, 0
	sub		t0,  t0,  #1904
	sub		t1,  t1,  #1904
	sub		sp,  t0,  #80
	swp		ori, rt1,[sp]

L0:
	Load	t1
	sub		t1,  t1,  #1904
	Load	t0
	sub		t0,  t0,  #1904
	sub		sp,  t0,  #64
	swp		rt0, ori,[sp]
	add		rt1, rt0, #480
	Go		t1,  t0, rt0, rt1, 0, 0
	sub		t0,  t0,  #1920
	sub		t1,  t1,  #1920
	sub		sp,  t0,  #64
	swp		ori, rt1,[sp]

	Load	t0
	sub		t0,  t0,  #1888
	Load	t1
	sub		t1,  t1,  #1888
	sub		sp,  t0,  #64
	swp		rt0, ori,[sp]
	add		rt1, rt0, #480
	Go		t0,  t1, rt1, rt0, 0, 0
	sub		t0,  t0,  #1904
	sub		t1,  t1,  #1904
	sub		sp,  t0,  #80
	swp		ori, rt1,[sp]

	ldr		x0, [sp,  #4]
	subs	x0,  x0,  #1
	str		x0, [sp,  #4]
	bhs		L0

	Load	t1
	sub		t1,  t1,  #1904
	@Load	t0
	sub		t0,  t0,  #16
	sub		sp,  t0,  #64
	swp		rt0, ori,[sp]
	add		rt1, rt0, #480
	Go		t1,  t0, rt0, rt1, 0, 1
	sub		t0,  t0,  #1920
	sub		t1,  t1,  #1920
	sub		sp,  t0,  #64
	swp		ori, rt1,[sp]
exit:
	sub		sp,  t0,  #64
	ldr		sp, [sp,  #8]
	ldmfd	sp!,{r0-r12,lr}
    bx	lr
	.size	myfilter, .-myfilter
	.ident	"GCC: (GNU) 3.3.2"
	.data
	.align	4
_0:	.space	64
_1:	.space	1920
_2:	.space	1920
