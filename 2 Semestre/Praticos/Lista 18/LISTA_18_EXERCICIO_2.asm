
.data
	# Mensagem de entrada
	msg_entrada_base: .asciiz "Entre com a base:"
	msg_entrada_expoente: .asciiz "Entre com o expoente:"
	
	# Mensagem de saida
	msg_saida: .asciiz "Resultado:"
	
.text
	main:
		# Realizar a leitura da base
		la $a0, msg_entrada_base
		addi $v0, $zero, 4
		syscall
		addi $v0, $zero, 5
		syscall
		add $s0, $zero, $v0	# $s0 = base
		
		# Realizar a leitura do expoente
		la $a0, msg_entrada_expoente
		addi $v0, $zero, 4
		syscall
		addi $v0, $zero, 5
		syscall
		add $s1, $zero, $v0	# $s1 = expoente
		
		# Calcular a potencia
		add $a0, $zero, $s0
		add $a1, $zero, $s1
		
		jal potencia
		
		add $t0, $zero, $v0
		
		# Imprimir o resultado
		la $a0, msg_saida
		addi $v0, $zero, 4
		syscall
		add $a0, $zero, $t0
		addi $v0, $zero, 1
		syscall
		
		# Encerrar programa
		addi $v0, $zero, 10
		syscall
	
	potencia:
		# Ajustar pilha
		addi $sp, $sp, -4
		sw $ra, 0($sp)
		
		bne $a1, $zero, else
		addi $v0, $zero, 1
		j return
		
		else:
			addi $a1, $a1, -1
			jal potencia
			
			mul $v0, $a0, $v0
		
		return:
			# Restaurar pilha
			lw $ra, 0($sp)
			addi $sp, $sp, 4
			
			jr $ra
