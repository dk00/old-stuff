.data
jmp:		.word	Mul,Add,Add,Sub,Sub,Div
.text
.globl		main
main:
	li		$v0, 5
	syscall
	slti	$s0, $v0, 0
	bne		$s0, $zero, exit
	move	$s0, $v0
	li		$v0, 8
	move	$a0, $sp
	li		$a1, 3
	syscall
	li		$v0, 5
	syscall
	lb		$a0, 0($sp)
	la		$a1, jmp
	addi	$a0, $a0, -42
	sll		$a0, $a0, 2
	add		$a0, $a0, $a1
	ld		$a0, 0($a0)
	jr		$a0
Add:
	add		$a0, $s0, $v0
	j		print
Sub:
	sub		$a0, $s0, $v0
	j		print
Mul:
	mult	$s0, $v0
	j		post
Div:
	div		$s0, $v0
	j		post
post:
	mflo	$a0
print:
	li		$v0, 1
	syscall
	j		main
exit:
	li		$v0, 10
	syscall
