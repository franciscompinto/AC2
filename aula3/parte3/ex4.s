.equ 	SFR_BASE_HI,0xBF88
.equ 	TRISE,0x6100
.equ	PORTE,0X6110
.equ 	LATE,0x6120


	.data
	.text
	.globl main

main:	lui $t0,SFR_BASE_HI
	lw $t1,TRISE($t0)
	andi $t1,$t1,0xFFF7
	sw $t1,TRISE($t0)
	
	li $t2, 1
loop:	lw $t1,PORTE($t0)
	
	

	li $a0, 100	#
	jal delay 	#


	andi $t1, $t1, 0xFFF7
	or $t1, $t1, $t2
	sw $t1, LATE($t0)
	

	not $t2, $t2	
	j loop
	jr $ra
