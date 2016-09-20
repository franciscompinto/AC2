	.equ SFR_BASE_HI, 0xBF88 	# 16 MSbits of SFR area
 	.equ TRISE, 0x6100 		# TRISE address is 0xBF886100
 	.equ PORTE, 0x6110 		# PORTE address is 0xBF886110
 	.equ LATE, 0x6120 		# LATE address is 0xBF886120 


	.text
	.globl main

main:	lui $t0,SFR_BASE_HI
	lw $t1,TRISE($t0)
	andi $t1,$t1,0xFFFE
	ori $t1,$t1,0x0040
	sw $t1,TRISE($t0)
	
loop:	lw $t1,PORTE($t0)
	andi $t2,$t1,0x0040
	srl $t2, $t2, 6
	andi $t1, $t1, 0xFFFE
	nor $t1, $t1, $t2
	sw $t1, LATE($t0)
		
	j loop
	jr $ra
