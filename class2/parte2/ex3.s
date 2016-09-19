	.data
str:	.asciiz "\nIntroduza uma hora(HH:MM:SS): "

	.text
	.globl main

main:	
	li $v0,12	#
	syscall		#resetCoreTimer()
	
	li $t0, 0	#sec=0
	li $t1, 0	#min=0
	li $t2, 0	#horas=0

	la $a0, str	#
	li $v0,8	#
	syscall		# PRINT_STR(STR)
	

	li $v0, 5	#
	syscall		#
	move $t2, $v0	# horas = readInt10()

	la $a0,':'	#
	li $v0,3	#
	syscall		#putChar(':')

	li $v0, 5	#
	syscall		#
	move $t1, $v0	# min = readInt10()

	la $a0,':'	#
	li $v0,3	#
	syscall		#putChar(':')

	li $v0, 5	#
	syscall		#
	move $t0, $v0	# sec = readInt10()


	la $a0, '\n'	#
	li $v0,3	#
	syscall		# putChar('\n')
	

ciclo: 	
	li $v0,11	#
	syscall		#readCoreTimer()
	blt $v0, 20000000, ciclo	#20000000


	addi $t0, $t0,1	#sec++


	
if:
	bne $t0, 60,else	#if(sec==60)
	li $t0, 0		#sec=0	
	addiu $t1, $t1, 1	#min++


if2:
	bne $t1, 60,else	#if(min==24)
	li $t0, 0		#sec=0	
	li $t1, 0		#min=0
	addiu $t2, $t2, 1	#horas++
 	
else:
	
	move $a0, $t2	#
	li $a1, 10	#
	li $v0, 6	#
	syscall		#printInt10(horas)

	la $a0,':'	#
	li $v0,3	#
	syscall		#putChar(':')

	move $a0, $t1	#
	li $a1, 10	#
	li $v0, 6	#
	syscall		#printInt10(min)

	la $a0,':'	#
	li $v0,3	#
	syscall		#putChar(':')

	move $a0, $t0	#
	li $a1, 10	#
	li $v0, 6	#
	syscall		#printInt10(sec)



	la $a0, '\r'	#
	li $v0,3	#
	syscall		# putChar('\n')


	li $v0,12	#
	syscall		#resetCoreTimer()


	j ciclo

	jr $ra
