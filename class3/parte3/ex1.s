	.data
space:  .asciiz "\r\n"	

	.text
	.globl main

main:
	li $v0, 12	#
	syscall		#resetCoreTimer[]

	li $a0, 1	#
	jal delay	# delay(1)
	
	li $t1, 10
	srl $t1, $t0,16	  #(10<<16)
	addi $t1, $t1, 10 #10+(10<<16)

	li $v0, 11	#
	syscall		#ReadCoreTimer[]	

	move $a0, $v0 	#
	move $a1, $t1	# 
	li $v0, 6	#
	syscall		#

	la $a0, space
	li $v0, 8
	syscall
	
	j main

	jr $ra
	
	
