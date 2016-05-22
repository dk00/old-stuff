	.file	"myfilter.c"
	.text
	.align	2
	.global	myfilter
	.type	myfilter, %function
myfilter:
    stmfd	sp!,{r0-r12,lr}			@60800(15200) 573040(307040)
	mov		r2, #76800
loop:
@	ldr		r3,[r1]
@	str		r3,[r0]
	ldrneh	r5, [r0, #-1]			@
	subs	r2, r2, #40
	bne		loop
exit:
	ldmfd	sp!,{r0-r12,lr}	
    bx	lr
	.size	myfilter, .-myfilter
	.ident	"GCC: (GNU) 3.3.2"
