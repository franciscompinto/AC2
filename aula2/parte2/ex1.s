	.data
out1: .asciiz "\nTimer Value: "
out2: .asciiz	"\nTimer Value [hex]: "


	.text
	.globl main
main:
	bne $0, 0, end #while(1)
	
	li $v0, 11
	syscall
	move $t0, $v0	#readCoreTimer();

	la $a0, out1	#
	li $v0, 8	#
	syscall		#printStr(out1)

	move $a0, $t0
	li $a1, 10
	li $v0, 6
	syscall
	
	la $a0, out2	#
	li $v0, 8	#
	syscall		#printStr(out2)

 	move $a0, $t0
	li $a1, 16
	li $v0, 6
	syscall

	li $t0, 0
for:	beq $t0, 10000, end
	add $t0, $t0, 1
	j for
end:
	j main
	jr $ra
#************************************
#int main(void){
#	while(1){
#		int val = readCoreTimer();
#		printStr("\nTimer Value: ");
#		printInt(val, 10);
#		printStr("\nTimer Value [hex]: ");
#		printInt(val, 16);
#	}
#}
