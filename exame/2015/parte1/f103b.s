.equ 	SFR_BASE_HI,0xBF88
.equ 	TRISE,0x6100
.equ	PORTE,0X6110
.equ 	LATE,0x6120

.equ 	TRISD,0x60C0
.equ	PORTD,0X60D0
.equ 	LATD,0x60E0
	
	.data
str:	.asciiz "\ninput numero[-7, 7]: "
str2:	.asciiz "\nso valores entre [-7, 7]: "

	.text
	.globl main

main:	lui $t0,SFR_BASE_HI 	#declaracao dos portos

	lw $t5,TRISD($t0)	#porto de saida
	andi $t5,$t5,0xF00f
	sw $t5,TRISD($t0)

	andi $t5,$t5,0xF00F	#imprimeir nos leds
	sw $t5, LATD($t0)
loop:
	lw $t5,PORTD($t0)
	
	la $a0, str
	li $v0, 8
	syscall

	li $v0, 5
	syscall
	move $t2, $v0 
	move $t3, $v0

	andi $t2,$t2,0xF	#forcamento da leitura	
	srl $t4, $t2, 3		#ficar com os bit mais sig para saber o sinal
	andi $t4, $t4,0x0001
#if:
	
	bge $t3, -7, else


	la $a0, str2
	li $v0, 8
	syscall
	j loop
else:
	ble $t3, 7, endif

	la $a0, str2
	li $v0, 8
	syscall
	j loop
endif:


if_not:
	beq $t4,0, endif_not		#if(valor<0)
	not $t2, $t2
	add $t2, $t2, 1
	andi $t2,$t2,0x7
	
endif_not:


	li $t7,0 	#int i		#SABER O VALOR NO em decimal
	li $t6,1 	#mul=1
for:		
	beq $t7, $t2, endfor		#fot(; i<=7;i++)

	mul $t6, $t6, 2		#mul *=2
	add $t7, $t7, 1		#i++
	j for
endfor:

	
	addi $t6, $t6, -1	#mul= mul -1
	#esto e devido a ser usado o porto D4 a D11
	sll $t6, $t6, 4		#mul<< 4	
 
if2:	
	beq $t4, 0,endif2	#add o bit de sinal

	
	ori $t6, $t6,0x0800

endif2:
	

		
	
	andi $t5,$t5,0xF00F	#imprimeir nos leds
	or  $t5, $t5, $t6
	sw $t5, LATD($t0)
	
	j loop
	jr $ra



