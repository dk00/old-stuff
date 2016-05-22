t	.req	r0
ret	.req	r1
ori	.req	r1
x0	.req	r2
x1	.req	r3
x2	.req	r4
x3	.req	r5
x4	.req	r6
x5	.req	r7
x6	.req	r8
x7	.req	r9
x8	.req	r10
x9	.req	r11
dt	.req	r12
tmp .req	lr
	.macro 	div 	i,o,a,d
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
	.macro	divm	a,b,c,d,e,f,da,db,dc
	Div		\d, \f, \e, \dc
	Div		\c, \e, \d, \db
	Div		\b, \d, \c, \db
	Div		\a, \c, \b, \da
	orr		\a, \c, \d, lsl #16
	orr		\b, \e, \f, lsl #16
	.endm
	.macro	div6m1	a,b,c,d,e,f
	Div4	\d, \f, \e
	Div		\c, \e, \d, t
	Div		\b, \d, \c, t
	Div		\a, \c, \b, t
	orr		\a, \c, \d, lsl #16
	orr		\b, \e, \f, lsl #16
	.endm
	.macro	div6m0	a,b,c,d,e,f
	Div 	\d, \f, \e, t
	Div		\c, \e, \d, t
	Div		\b, \d, \c, t
	Div4	\a, \c, \b
	orr		\a, \c, \d, lsl #16
	orr		\b, \e, \f, lsl #16
	.endm
	.macro	dec		o
	and		t,  \o, #0x3E0
	bic		\o, \o, #0x3E0
	orr		\o, \o, t,  lsl #16
	.endm
	.macro	extr	a,b,i
	mov		\b, \i, lsr #16
	bic		\a, \i, \b, lsl #16
	Dec		\a
	Dec		\b
	.endm
	.macro	comb	a,b,c,d
	add		\b, \b, \c
	add		\a, \a, \b
	add		\b, \b, \d
	.endm
	.macro	dc7		a,b,c,d,e,f,g,h
	Extr	\g, \h, \e
	Extr	\e, \f, \d
	Extr	\c, \d, \c
	Comb	\a, \b, \c, \d
	Comb	\c, \d, \e, \f
	Comb	\e, \f, \g, \h
	.endm
	.macro	dcm		a,b,c,d,e,f,g,h,i,j
	Extr	\i, \j, \f
	Dc7		\a, \b, \c, \d, \e, \f, \g, \h
	Comb	\g, \h, \i, \j
	.endm
	.macro	loadr	a,b,c,d,e,f,g,h,i,j
@	ldmia	ori!,{\c,\d,\e,\f}
@	Dcm		\a, \b, \c, \d, \e, \f, \g, \h, \i, \j
	ldrh	\c,[ori],#2
	ldrh	\d,[ori],#2
	ldrh	\e,[ori],#2
	ldrh	\f,[ori],#2
	ldrh	\g,[ori],#2
	ldrh	\h,[ori],#2
	ldrh	\i,[ori],#2
	ldrh	\j,[ori],#2
	Dec		\c
	Dec		\d
	Dec		\e
	Dec		\f
	Dec		\g
	Dec		\h
	Dec		\i
	Dec		\j
	Comb	\a, \b, \c, \d
	Comb	\c, \d, \e, \f
	Comb	\e, \f, \g, \h
	Comb	\g, \h, \i, \j
	.irp	dat	\a,\b,\c,\d,\e,\f,\g,\h
	stmia	tmp!,{\dat}
	.endr
@	stmia	tmp!,{\a,\b,\c,\d,\e,\f,\g,\h}
	.endm
	.macro	load
	ldr		x0, [ori],#4
	Extr	x0,  x1,  x0
	add		x2,  x0,  x1
	str		x2, [tmp],#4
	.rept	14
	Loadr	x0,  x1,  x4,  x5,  x6,  x7,  x8,  x9,  x2,  x3
	Loadr	x2,  x3,  x4,  x5,  x6,  x7,  x8,  x9,  x0,  x1
	.endr
	Loadr	x0,  x1,  x4,  x5,  x6,  x7,  x8,  x9,  x2,  x3
	ldmia	ori!,{x4,x5,x6}
	Dc7		x2,  x3,  x4,  x5,  x6,  x7,  x8,  x9
	add		x8,  x8,  x9
	stmia	tmp!,{x2-x8}
	.endm
	.macro	addm	a,b,c,d,e,f,g,h
	add		\a, \a, \e
	add		\b, \b, \f
	add		\c, \c, \g
	add		\d, \d, \h
	.endm
	.macro	go1	next
	ldmia	tmp,{x0-x3}
	add		tmp, tmp, \next			@ tmp[i+1]
	ldmia	tmp,{x4-x7}
	Addm	x0, x1, x2, x3, x4, x5, x6, x7
	.endm
	.macro	go3
	add		tmp, tmp, #960			@ tmp[i+2]
	ldmia	tmp,{x4-x7}
	Addm	x4, x5, x6, x7, x0, x1, x2, x3
	.endm
	.macro	go2
	add		ret, ret, #480			@ ret[i+1]
	stmia	ret,{x4,x5}
	sub		ret, ret, #480
	.endm
	.macro	go0		pre
	add		tmp, tmp, \pre			@ tmp[i-1]
	ldmia	tmp!,{x4-x7}
	add		tmp, tmp, #960
	Addm	x4, x5, x6, x7, x0, x1, x2, x3
	.endm
	.macro	go		pre,next,d0,d1,d2
	Go1		\next
	Go3
	Divm	x4, x5, x6, x7, x8, x9, \d0,\d1,\d2
	Go2
	Go0		\pre
	Divm	x4, x5, x6, x7, x8, x9, \d0,\d1,\d2
	stmia	ret!,{x4,x5}			@ ret[i]
	.endm
	.macro	gos		pre,next
	Go1		\next
	Go3
	Divm	x4, x5, x6, x7, x8, x9, dt, dt, dt
	Go2
	Go0		\pre
	Divm	x4, x5, x6, x7, x8, x9, t,  t,  t
	stmia	ret!,{x4,x5}			@ ret[i]
	.endm
	.macro	got		pre,next
	Go1		\next
	add		tmp, tmp, #960			@ tmp[i+2]
	mov		x4, x0
	mov		x5, x1
	mov		x6, x2
	mov		x7, x3
	Divm	x4, x5, x6, x7, x8, x9, t,  t,  t
	Go2
	Go0		\pre
	Divm	x4, x5, x6, x7, x8, x9, dt,  dt,  dt
	stmia	ret!,{x4,x5}			@ ret[i]
	.endm
	.macro	first	pre,next,d6p
	swp		ret, ori,[sp]
	add		t,   tmp, \d6p
	add		tmp, tmp, \pre
	Go1		\next
	Go3
	Divm	x4, x5, x6, x7, x8, x9, t, dt, dt
	Go2
	Go0		\pre
	Div6m0	x4, x5, x6, x7, x8, x9
	stmia	ret!,{x4,x5}			@ ret[i]
	.rept	58
	Gos		\pre, \next
	.endr
	Go1		\next
	Go3
	Divm	x4, x5, x6, x7, x8, x9, dt, dt, t
	Go2
	Go0		\pre
	Div6m1	x4, x5, x6, x7, x8, x9
	stmia	ret!,{x4,x5}			@ ret[i]
	add		ret, ret, #480
	swp		ori, ret,[sp]
	sub		tmp, tmp, #1920
	.endm
	.macro	proc	pre,next,d6p
	swp		ret, ori,[sp]
	add		t,   tmp, \d6p
	add		tmp, tmp, \pre
	Go		\pre, \next, t,   dt,  dt
	.rept	58
	Go		\pre, \next, dt,  dt,  dt
	.endr
	Go		\pre, \next, dt,  dt,  t
	add		ret, ret, #480
	swp		ori, ret,[sp]
	sub		tmp, tmp, #1920
	.endm
	.macro	final	pre,next,d6p
	swp		ret, ori,[sp]
	add		t,   tmp, \d6p
	add		tmp, tmp, \pre
	Go1		\next
	add		tmp, tmp, #960			@ tmp[i+2]
	mov		x4, x0
	mov		x5, x1
	mov		x6, x2
	mov		x7, x3
	Div6m0	x4, x5, x6, x7, x8, x9
	Go2
	Go0		\pre
	Divm	x4, x5, x6, x7, x8, x9, t,  dt,  dt
	stmia	ret!,{x4,x5}			@ ret[i]
	.rept	58
	Got		\pre, \next
	.endr
	Go1		\next
	add		tmp, tmp, #960			@ tmp[i+2]
	mov		x4, x0
	mov		x5, x1
	mov		x6, x2
	mov		x7, x3
	Div6m1	x4, x5, x6, x7, x8, x9
	Go2
	Go0		\pre
	Divm	x4, x5, x6, x7, x8, x9, dt,  dt,  t
	stmia	ret!,{x4,x5}			@ ret[i]
	add		ret, ret, #480
	swp		ori, ret,[sp]
	sub		tmp, tmp, #1920
	.endm
	.text
	.align 2
t1:	.word	_t+960
d9:	.byte	0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,19,20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,22,23,23,23,23,23,23,23,23,23,24,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,30,30,30,30,30,30,30,30,30,31,31,31,31,31,31,31,31,31
	.align	2
	.global	boxfilter
	.type	boxfilter, %function
boxfilter:
    stmfd	sp!,{r0-r12,lr}
	str		r0, [sp,  #-4]!
	ldr		tmp, t1
	adr		dt,  d9
	Load
	Load
	Load
	First	#-2880,#960,#0
	mov		x0,  #39
L0:
	strh	x0, [sp,  #-8]
	Load
	Load
	Proc	#960,#-2880,#1920
	Load
	Load
	Proc	#-2880,#960,#0
	ldrh	x0, [sp,  #-8]
	subs	x0,  x0,  #1
	bne		L0
	Load
	add		tmp, tmp, #960
	Final	#960,#-2880,#1920
exit:
	add		sp,  sp,  #4
	ldmfd	sp!,{r0-r12,lr}
    bx	lr
	.size	boxfilter, .-boxfilter
	.ident	"GCC: (GNU) 3.3.2"
	.data
	.align	2
_t:	.space	3840
d6:	.byte	0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,11,11,11,11,11,11,12,12,12,12,12,12,13,13,13,13,13,13,14,14,14,14,14,14,15,15,15,15,15,15,16,16,16,16,16,16,17,17,17,17,17,17,18,18,18,18,18,18,19,19,19,19,19,19,20,20,20,20,20,20,21,21,21,21,21,21,22,22,22,22,22,22,23,23,23,23,23,23,24,24,24,24,24,24,25,25,25,25,25,25,26,26,26,26,26,26,27,27,27,27,27,27,28,28,28,28,28,28,29,29,29,29,29,29,30,30,30,30,30,30,31,31,31,31,31,31

