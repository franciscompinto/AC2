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
	ori $t1,$t1,0x00C0
	sw $t1,TRISE($t0)

	

	li $t8, 0xF0F0F0F0	#inicializaçao do contador de johnson
	li $t9, 0		#inicializaçao do contador normal
	
	li $v0,12	#
	syscall		#resetCoreTimer()
	
readPort:

	lw $t1, 

	
	andi $t2,$t1,0x0040		#get bit 6 -> $t2=RE6
	srl $t2, $t2, 6

	andi $t3,$t1,0x0080		#get bit 7 -> $t3=RE6
	srl $t3, $t3, 7


	bne  $t2, 0, johnson		#if(RE6 == 0)


####################################################################33
count:	li $v0,11			#
	syscall				#readCoreTimer()
	
	blt $v0,clock, readPort	
	
	bne $t3, 0, decres		#if(RE7 == 0)		
					
	addiu $t9, $t9, 1		#i++
	j endif

decres:					#else =>RE7==1
	addiu $t9, $t9,-1		#i--
endif:

	andi $t1,$t1,0xFFF0
	or $t1, $t1, $t9
	sw $t1,LATE($t0)

	li $v0,12			#
	syscall				#resetCoreTimer()

	

	j readPort
###########################################################################
	
johnson: 		#	else	=>RE6==1

	li $v0,11	#
	syscall		#readCoreTimer()
	
	blt $v0,clock, readPort	

	
	bne $t3, 0, decres_j		#if(RE7 == 0)		
					
	rol $t8, $t8, 1			#rotacacao
	j endif_j

decres_j:					#else =>RE7==1
	ror $t8, $t8, 1

endif_j:
	


	andi $t1,$t1,0xFFF0
	or $t1, $t1, $t8
	sw $t1,LATE($t0)

	li $v0,12	#
	syscall		#resetCoreTimer()


	j readPort

	jr $ra


