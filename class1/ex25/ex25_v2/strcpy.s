#char *strcpy(char *dst, char *src) 
#{
#	char *rp = dst;
#	for(; (*dst = *src) != 0; dst++, src++);
#	return rp;
#} 
	.text
	.globl strcpy
	

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
