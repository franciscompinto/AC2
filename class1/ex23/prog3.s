#// *************************************************************************
#// Programa 3 – teste dos system calls "getChar()" e "putChar()"
#// *************************************************************************
#int main(void)
#{
#	char c;
#	while (1)
#	{
#		c = getChar();
# 		if (c == '\n')
# 			break;
# 		putChar(c);
# 	}
# 	return 1;
#} 





	.text
	.globl main
main:
while1: bne $0, 0, end	#while(1)


	li $v0, 2 #c=getChar()
	syscall

#if	
	beq $v0, '\n', end #if(c == '\n')


	move $a0, $v0 #putChar(c)
	li $v0, 3
	syscall

	j while1
end:
	li $v0, 1 #return 1
	jr $ra




	
