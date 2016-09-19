#// *************************************************************************
#// String length
#// *************************************************************************
#//
#int strlen(char *s)
#{
#	int len;
# 	for(len = 0; *s != 0; len++, s++);
# 	return len;
#} 

	.text
	.globl strlen
	
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

