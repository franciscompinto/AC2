.equ 	SFR_BASE_HI,0xBF88
.equ 	TRISE,0x6100
.equ	PORTE,0X6110
.equ 	LATE,0x6120

.equ 	TRISD,0x60C0
.equ	PORTD,0X60D0
.equ 	LATD,0x60E0
	
	.data
	.text
	.globl main

main:	lui $t0,SFR_BASE_HI 	#declaracao dos portos
	lw $t1,TRISE($t0)	#porto de estada
	ori $t1,$t1,0x00F0
	sw $t1,TRISE($t0)

	lw $t5,TRISD($t0)	#porto de saida
	andi $t5,$t5,0xF00f
	sw $t5,TRISD($t0)


loop:	lw $t1,PORTE($t0)	#LEITURA DO PORTO DE ENTREADA
	lw $t5,PORTD($t0)


	andi $t2,$t1,0x00F0	#forcamento da leitura	
	srl $t3, $t2, 4		#ficar com os bit menos sig 
	srl $t4, $t2, 7		#ficar com os bit mais sig para saber o sinal
	andi $t3, $t3,0x0007	#mascaras
	andi $t4, $t4,0x0001

if:	
	beq $t4, 0,endif	# para se saber se o valor e negativo se for inverte o

	not $t3, $t3
	andi $t3, $t3,0x0007

endif:
	

	li $t7,0 	#int i		#SABER O VALOR NO em decimal
	li $t6,1 	#mul=1
for:		
	beq $t7, $t3, endfor

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
