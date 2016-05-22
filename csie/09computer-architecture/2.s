.data
o:	.asciiz "1: A -> B\n"
.text
.globl		__start
.globl		main
__start:
main:
	li		$v0,5
	syscall
	addi	$s0,$v0,1
	la		$a0,o
	li		$v0,4
	la		$ra, exit
	li		$s1,65
	li		$s2,66
	li		$s3,67
go:
	addi	$s0,-1
	ble		$s0,$zero,ret
	addi	$sp,$sp,-4
	sw		$ra,0($sp)
	move	$s4,$s3
	move	$s3,$s2
	move	$s2,$s4
	jal		go
	move	$s4,$s3
	move	$s3,$s2
	move	$s2,$s4
	jal		print
	move	$s4,$s1
	move	$s1,$s2
	move	$s2,$s4
	jal		go
	move	$s4,$s1
	move	$s1,$s2
	move	$s2,$s4
	lw		$ra,0($sp)
	addi	$sp,$sp,4
ret:
	addi	$s0,1
	jr		$ra
print:
	add		$s4,$s0,48
	sb		$s4,0($a0)
	sb		$s1,3($a0)
	sb		$s3,8($a0)
	syscall
	jr		$ra
exit:
	li		$v0, 10
	syscall
