	.data
str:	.asciiz "\n "

	.text
	.globl main

main:	
	li $v0,12	#
	syscall		#resetCoreTimer()
	
	li $t0, 0	#i=0
ciclo: 	
	li $v0,11	#
	syscall		#readCoreTimer()
	blt $v0, 20000000, ciclo


	addi $t0, $t0,1	#i++

	move $a0, $t0	#
	li $a1, 10
	li $v0, 6	#
	syscall		#printInt10(i)


	la $a0, str	#
	li $v0,8	#
	syscall		# PRINT_STR(STR)


	li $v0,12	#
	syscall		#resetCoreTimer()


	j ciclo
	jr $ra
