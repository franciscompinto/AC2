#// *************************************************************************
#// Programa 2 – teste do system call "inkey()"
#// *************************************************************************
#int main(void)
#{
# 	char c;
#	while (1)
#	{
#		while ((c = inkey()) == 0);
# 			if (c == '\n')
# 				break;
# 		printStr("Key pressed\n");
#	 }
# 	return 0;
#} 	


	.data
str: .asciiz "key pressed\n"

	.text
	.globl main
main:
while1:	bne $0, 0, end	#while(1)

while:	li $v0, 1 #c=inkey()
	syscall

	#c=$v0


	beq $v0, 0, while
	
	beq $v0, '\n', end #if (c == '\n')
	
	la $a0, str #printStr("Key pressed\n");
	li $v0,8
	syscall

 	j while1
end:
	li $v0, 0
	jr $ra



