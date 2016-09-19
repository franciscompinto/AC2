#// *************************************************************************
#// String concatenate
#// *************************************************************************
#// char *strcat(char *dst, char *src) 
#{	char *rp = dst;
#	for(; *dst != 0; dst++);
#	strcpy(dst, src);
#	return rp;
#} 
	
	.text
	.globl strcat

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
