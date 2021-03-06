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

#################################################################################################33
#// *************************************************************************
#// String length
#// *************************************************************************
#int strlen(char *s)
#{
#	int len;
# 	for(len = 0; *s != 0; len++, s++);
# 	return len;
#} 


	
strlen:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	

	li $v0, 0	#$v0=len
for:	lb $t0, 0($a0)
	beq $t0, 0 ,end #for(len = 0; *s != 0; len++, s++); 

	addiu $v0, $v0, 1
	addu  $a0,$a0,  1	#incrementar a posiçao do ponteiro
	j for 

end:	

	lw $ra, 0($sp)
	addiu $sp, $sp, 4
	jr $ra


##############################################################################################3
#// *************************************************************************
#// String copy
#// ************************************************************************* 
#char *strcpy(char *dst, char *src) 
#{
#	char *rp = dst;
#	for(; (*dst = *src) != 0; dst++, src++);
#	return rp;
#} 


	

strcpy:

	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	move $t0, $a0 		#*rp=dst
	
for_sc:	
	lb $t1,0($a1)		#*dst	
	sb $t1,0($a0)		#*dst = *src;


	beqz $t1,endfor_sc	#for(;(*dst = *src) !=0; dst++, src++)

	
	

	addu $a0,$a0, 1		#src++
	addu $a1,$a1, 1		#dst++
	
	
	j for_sc
endfor_sc:		
	
	move $v0, $t0		#return dst;
	

	
	lw $ra, 0($sp)
	addiu $sp, $sp, 4
	jr $ra
##############################################################################################3

#// *************************************************************************
#// String concatenate
#// *************************************************************************
#// char *strcat(char *dst, char *src) 
#{	char *rp = dst;
#	for(; *dst != 0; dst++);
#	strcpy(dst, src);
#	return rp;
#} 


strcat:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $s0, 4($sp)

	move $s0, $a0 		# char *rp=dst

for2:	lb $t1, 0($a0)

	beq $t1, 0, endf2 	#for(; *dst != 0; dst++); 
	
 	addiu $a0, $a0, 1
	j for2
endf2:	
	jal strcpy
	
	move $v0, $s0
	
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	addiu $sp, $sp, 8
	jr $ra


##############################################################################################3
#// *************************************************************************
#// String compare (alphabetically).
#// Returned value is:
#// < 0 string "s1" is less than string "s2"
#// = 0 string "s1" is equal to string "s2"
#// > 0 string "s1" is greater than string "s2"
#// *************************************************************************
#//
#int strcmp(char *s1, char *s2)
#{
#	for(; (*s1 == *s2) && (*s1 != 0); s1++, s2++);
#	return(*s1 - *s2);


strcmp:

for3:	lb $t0, 0($a0)		#*s1
	lb $t1, 0($a1)		#*s2

	bne $t0, $t1, endf3	#
	beqz $t0, endf3		#(*s1 == *s2) && (*s1 != 0)


	addiu $a0, $a0, 1	# s1++
	addiu $a1, $a1, 1	# s2++
	
	j for3
endf3:
	sub $v0, $t0, $t1	#return(*s1 - *s2);

	jr $ra



#} 
