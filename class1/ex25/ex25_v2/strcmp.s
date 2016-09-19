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

	.text
	.globl strcmp

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



