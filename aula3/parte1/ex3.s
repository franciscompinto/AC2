	.equ SFR_BASE_HI, 0xBF88 	# 16 MSbits of SFR area
 	.equ TRISE, 0x6100 		# TRISE address is 0xBF886100
 	.equ PORTE, 0x6110 		# PORTE address is 0xBF886110
 	.equ LATE, 0x6120 		# LATE address is 0xBF886120 


	.text
	.globl main

main:	lui $t0,SFR_BASE_HI
	lw $t1,TRISE($t0)
	andi $t1,$t1,0xFFF0
	ori $t1,$t1,0x00C0
	sw $t1,TRISE($t0)
	
loop:

	lw $t1,PORTE($t0)		#load PORTE bits


	andi $t2,$t1,0x0040		#get bit 6 -> $t2=RE6
	srl $t2, $t2, 6

	andi $t3,$t1,0x0080		#get bit 6 -> $t3=RE6
	srl $t3, $t3, 7


	li $t4, 0

	nor $t4, $t2, $t3
	or  $t5, $t5, $t4
	sll $t5, $t5, 1

	xor $t4, $t2, $t3
	or  $t5, $t5, $t4
	sll $t5, $t5, 1

	or  $t4, $t2, $t3
	or  $t5, $t5, $t4
	sll $t5, $t5, 1

	and $t4, $t2, $t3
	or  $t5, $t5, $t4


	andi $t1, $t1, 0xFFF0
	or $t1, $t1, $t5
	sw $t1, LATE($t0)


	j loop


	jr $ra
