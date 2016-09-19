	.equ SFR_BASE_HI, 0xBF88 	# 16 MSbits of SFR area
 	.equ TRISE, 0x6100 		# TRISE address is 0xBF886100
 	.equ PORTE, 0x6110 		# PORTE address is 0xBF886110
 	.equ LATE, 0x6120 		# LATE address is 0xBF886120 
	.equ clock, 20000000/4
	


	.text
	.globl main

main:	lui $t0,SFR_BASE_HI
	lw $t1,TRISE($t0)
	andi $t1,$t1,0xFFF0
	sw $t1,TRISE($t0)
	
reset:

	lw $t1, PORTE($t0)
	li $t9, 0	#cont=0

	andi $t1,$t1,0xFFF0
	or $t1, $t1, $t9
	sw $t1,LATE($t0)
	

	li $v0,12	#
	syscall		#resetCoreTimer()
ciclo: 	
	li $v0,11	#
	syscall		#readCoreTimer()
	
	blt $v0,clock, ciclo	

	addiu $t9, $t9, 1


#output:
	andi $t1,$t1,0xFFF0
	or $t1, $t1, $t9
	sw $t1,LATE($t0)

	li $v0,12	#
	syscall		#resetCoreTimer()

	bgt $t9, 15, reset

	j ciclo

	jr $ra



