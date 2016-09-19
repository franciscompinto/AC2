


	.equ STR_MAX_SIZE, 20


.data
out1:	.asciiz "intruduza 2 strings: \n"
out2:	.asciiz "\nResultado:\n"
str1:	.space 1+STR_MAX_SIZE*4
str2:	.space 1+STR_MAX_SIZE*4
str3:	.space 1+STR_MAX_SIZE*8




	.text
	.globl main
main:	
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	la $a0, out1 	#printStr("Introduza 2 strings: "); 
	li $v0, 8
	syscall


	la $a0, str1 	#readStr( str1, STR_MAX_SIZE ); 
	li $a1, STR_MAX_SIZE
	li $v0, 9
	syscall
		

	la $a0, '-' 	#separacao
	li $v0, 3
	syscall 

	la $a0, str2 	#readStr( str1, STR_MAX_SIZE ); 
	li $a1, STR_MAX_SIZE
	li $v0, 9
	syscall

	la $a0, out2 	#printStr("\nResultado:\n"); 
	li $v0, 8
	syscall


	la $a0, str1	#
	jal strlen	#strlen(str1)


	move $a0, $v0 	#prinInt( strlen(str1), 10 );
	li $a1, 10
	li $v0,  6
	syscall

	la $a0, '-'	#
	li $v0, 3	#
	syscall 	#separacao

	la $a0, str2	#
	jal strlen	#strlen(str2)

	move $a0, $v0	#	
	li $a1, 10	#
	li $v0,  6	#
	syscall		#prinInt(strlen(str2), 10 ); 

	la $a0, '\n'	#
	li $v0, 3	#
	syscall 	#separacao

	la $a0, str3	#
	la $a1, str1	#
	jal strcpy	#strcpy(str3, str1)
	

	la $a0, str3	#
	la $a1, str2	#
	jal strcat	#strcat(str3, str2)

	move $a0, $v0	#
	li $v0, 8	#
	syscall		#printStr(strcat(str3, str2))

	la $a0, '\n'	#
	li $v0, 3	#
	syscall 	#separacao


	la $a0, str1	#
	la $a1, str2	#
	jal strcmp	#strcmp(str1, str2)

	move $a0, $v0	#
	li $v0, 7	#
	syscall		#printStr(strcmp(str1, str2))	



	lw $ra, 0($sp)
	addiu $sp, $sp, 4
	li $v0, 0 #return 0
	jr $ra




