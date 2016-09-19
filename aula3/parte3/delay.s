#// Geracao de um atraso programável:
#// - valor mínimo: 1 ms (para n_intervals = 1)
#// - valor máximo: (232-1) * 1ms (para n_intervals = 0xFFFFFFFF)
#// (aproximadamente 4294967 s, i.e., 49.7 dias :) )
#//
#void delay(unsigned int n_intervals)
#{
# volatile unsigned int i;

# for(; n_intervals != 0; n_intervals--)
#	 for(i = CALIBRATION_VALUE; i != 0; i--)
#} 

	.text
	.globl delay
delay:

	li $t1, 10000 #CALIBRATION_VALUE
for:
	beq $a0, 0, endfor	#for(; n_intervals != 0; n_intervals--) 
for2:
	beq $t1, 0, endfor2	#for(i = CALIBRATION_VALUE; i != 0; i--) 

	addi $t1, $t1, -1	#i--
	j for2

endfor2:
	addi $a0, $a0, -1	# n_intervals--
	j for
endfor:
	jr $ra
