	.equ N_INT, 5
	.equ TRUE, 1
	.equ FALSE, 0

.data
lista:	.space 20
str1:	.asciiz "\nLeitura e ordenaçao de inteiros em base 10\n"
str2:	.asciiz "Introduza 5 inteiros: "
str3:	.asciiz "\nNumero de trocas realizado: "
str4:	.asciiz "\nResultado da ordenaçao: "

	.text
	.globl main

main:	addi $sp,$sp,-4
	sw $ra,0($sp)

	la $a0,str1	#
	li $v0,8	#
	syscall		#print str1

	la $a0,str2	#
	li $v0,8	#
	syscall		#print str2

	la $s0, lista	#s0-> lista[0]
	li $t0, 0 	#i=0 
forM1:
	bge $t0, N_INT,endforM1

	li $v0, 4
	li $a0, 10
	syscall
	
	sll $t1, $t0, 2
	addu $t2, $s0, $t1
	sw $v0, 0($t2) #lista[i]=readInt(10);


	la $a0,' '	#
	li $v0,3	#
	syscall		#putChar(' ')

	addi $t0, $t0, 1 #i++
	j forM1

endforM1:

	
	

	lA $a0, N_INT	
	la $a1, lista	
	jal sequentialSort
	move $t3, $v0	#n_trocas = sequentialSort( N_INT, lista ); 

	la $a0,str3	#
	li $v0,8	#
	syscall		#print str3
	
	move $a0,$t3	#
	li $a1,10	#
	li $v0,6	#
	syscall		#printInt(n_trocas,10)

	la $a0,str4	#
	li $v0,8	#
	syscall		#print str4


	la $t2,lista
	addi $t3,$t2,20

forP:	
	bge $t2, $t3, endforP	#for( ptr = lista; ptr < lista + N_INT; ptr++ ) 

	lb $a0, 0($t2)	#
	li $a1, 10	#
	li $v0, 6	#
	syscall		#printInt(*ptr, 10); // system call 

	la $a0,' '	#
	li $v0,3	#
	syscall		#putChar(' ')
	
	addiu $t2, $t2, 4 #p++
	j forP
endforP:


	lw $ra,0($sp)
	addiu $sp,$sp,4

	li $v0, 0 #return 0

	jr $ra


###################### int sequentialSort(uint n_val, uint *array)##############################
#$s0 -> n_trocas
#$s1 -> i
#$s2 -> j
#$s3 -> n_val
#$s4 -> *array
sequentialSort:
	addi $sp, $sp, -24
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)
	sw $s3, 20($sp)
	

	move $s3, $a0 	#n_val
	move $s4, $a1 	#*array
	li $s1, 0 	# i =0
	li $s2, 0 	#j =0
	li $s0, 0	#n_trocas= 0

	
for_SS:

	addi $t0,$s3,-1	#n_val-1	#n_val-1
	bge $s1, $t0, endfor_SS		# for( i = 0; i < n_val - 1; i++ ) 


	add $s2, $s1, 1			#j = i + 1
for2:	bge $s2, $s3, endfor2		#for( j = i + 1; j < n_val; j++ ) 

#if:
	sll $t1, $s1, 2
	addu $t1, $s4, $t1
	lw $t2, 0($t1)			#(array[i])= $t1

	sll $t3, $s2, 2
	addu $t3, $s4, $t3
	lw $t4, 0($t3)			#(array[J])= $t4


	bge $t2, $t4, endif


	move $a0,$t1			#
	move $a1,$t3			#
	jal troca			#troca(&array[i], &array[j]); 

	addi $s0, $s0, 1		#n_trocas++

endif:
	addi $s2, $s2, 1
	j for2
endfor2:
		
	addi $s1, $s1, 1
	j for_SS
endfor_SS:
	

	move $v0, $s0 #return n_tracas

	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	lw $s3, 20($sp)
	addiu $sp, $sp, 24
	jr $ra

#####################################################################33
troca:
	#$a0<*c1
	#$a1<*c2


	addi $sp, $sp, -4
	sw $ra, 0($sp)


	
	
	lw $t4, 0($a0)
	lw $t5, 0($a1)
	sw $t4, 0($a1)
	sw $t5, 0($a0)
	
	lw $ra, 0($sp)
	addiu $sp, $sp, 4

	jr $ra
	
