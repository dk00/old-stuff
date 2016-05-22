ret	.req	r0
ori	.req	r1
i	.req	r2
j	.req	r3
k	.req	r4
x	.req	r5					
				@r6-r11
t	.req	r12
	.macro	ldc		o
	ldrh	\o, [ori], #2
	and		t,  \o, #0x3E0
	bic		\o, \o, #0x3E0
	add		\o, \o, t, lsl #16
	.endm
	.macro	Sav		o, d
	str		\o,[\d],#4
	.endm
	.macro	go		o
	sub		x,  x,  \o
	Ldc		\o
	add		x,  x,	\o
	Sav		x,  ret
	.endm
	.text						@ 7104/5888
	.align	2
	.global	myfilter
	.type	myfilter, %function
myfilter:
    stmfd	sp!,{r0-r12,lr}
	Ldc		j
	Ldc		k
	add		x,  j,  k
	Sav		x,  ret
	.rept 79 
	Go		i
	Go		j
	Go		k
	.endr
	Go		i
	sub		x,  x,  j
	Sav		x,  ret
exit:
	ldmfd	sp!,{r0-r12,lr}
    bx	lr
	.size	myfilter, .-myfilter
	.ident	"GCC: (GNU) 3.3.2"
	.data
	.align	2
