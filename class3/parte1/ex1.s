.equ 	SFR_BASE_HI,0xBF88
.equ 	TRISE,0x6100
.equ	PORTE,0X6110
.equ 	LATE,0x6120
	.data
	.text
	.globl main

main:	lui $t0,SFR_BASE_HI
	lw $t1,TRISE($t0)
	andi $t1,$t1,0xFFF4
	ori $t1,$t1,0x0040
	sw $t1,TRISE($t0)
	
loop:	lw $t1,PORTE($t0)
	andi $t2,$t1,0x0040
	srl $t2, $t2, 5
	andi $t1, $t1, 0xFFF0
	or $t1, $t1, $t2
	sw $t1, LATE($t0)
		
	j loop
	jr $ra
