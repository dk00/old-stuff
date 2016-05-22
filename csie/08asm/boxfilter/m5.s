ret	.req	r0
ori	.req	r1
s	.req	r2
t	.req	r3
	.macro	dc		o
	and		t,  \o, #0x3E0
	bic		\o, \o, #0x3E0
	add		\o, \o, t, lsl #16
	.endm
	.macro	Sav		o
	.endm
	.text						@ 7600/5048
	.align	2
	.global	myfilter
	.type	myfilter, %function
myfilter:
    stmfd	sp!,{r0-r12,lr}
	adr		s,  _t
	ldr		r4,[ori], #4
	.rept	30
	ldmia	ori!,{r9-r12}
	mov		r5, r9, lsr #16
	bic		r6, r9, r5, lsl #16
	mov		r7, r10,lsr #16
	bic		r8, r10,r7, lsl #16
	mov		r9, r11,lsr #16
	bic		r10,r11,r9, lsl #16
	mov		r11,r12,lsr #16
	bic		r12,r12,r11, lsl #16
	Dc		r5
	Dc		r6
	Dc		r7
	Dc		r8
	Dc		r9
	Dc		r10
	Dc		r11
	Dc		r12
	add		t, r11,r12
	add		r5, r5, r4
	add		r6, r6, r5
	add		r7, r7, r6
	add		r8, r8, r7
	add		r9, r9, r8
	add		r10,r10,r9
	add		r11,r11,r10
	add		r12,r12,r11
	sub		r12,r12,r9
	sub		r11,r11,r8
	sub		r10,r10,r7
	sub		r9, r9, r6
	sub		r8, r8, r5
	sub		r7, r7, r4
	mov		r4, r3
	stmia	ret!,{r5-r12}
	.endr
	sub		s,  s,  #960
exit:
	ldmfd	sp!,{r0-r12,lr}
    bx	lr
	.size	myfilter, .-myfilter
	.ident	"GCC: (GNU) 3.3.2"
	.data
	.align	2
_t:	.space	960
