.data
str1:		.space 32
str2:		.space 32

.text

###########################################################

readstring:
	la $a0, str1		
	li $a1, 32
	li $v0, 8			#syscall para ler string do teclado
	syscall
	
readstring2:
	la $a0, str2
	li $a1, 32
	li $v0, 8			#syscall para ler string do teclado
	syscall

###########################################################
		
printstring:
	la $a0, str1
	li $v0, 4
	syscall
	
###########################################################
	
#	li $v0, 0 		#inicializa contador
#	li $t1, 10		#inicializa comparador com '\n'
#	la $a0, str1
#strlen:
#	lb $t2, 0($a0)
#	beq $t2, $t1, end   #vai pro final caso o contador encontre um "\n"
#	addi $v0, $v0, 1	#incrementa contador
#	addi $a0, $a0, 1	#incrementa ponteiro da string (1 byte)
#	j strlen	
#
#end:
#	move $a0, $v0
#	li $v0, 1
#	syscall
	
###########################################################

#	la $a0, str1		#coloca o endereço da string 1 em a0
#	la $a1, str2		#coloca o endereço da string 2 em a1
#	li $t1, 10		#move '\n' para o registrador comparador de final de string
#	li $t0, 32
#strcat:
#	lb $t2, 0($a0)
#	beq $t2, $t1, conc	#Se encontrar algum '\n', comecar a concatenação
#	addi $t0, $t0, -1	#Decrementa contador
#	beq  $t0, $zero, result #Se o contador chegar a zero, termina o programa
#	addi $a0, $a0, 1	#incrementa ponteiro da string (1 byte)
#	j strcat
#conc:
#	lb $t2, 0($a1)		#Copia o byte de a1
#	sb $t2, 0($a0)		#salva o byte em a0
#	addi $t0, $t0, -1	#Decrementa contador
#	beq  $t0, $zero, result 
#	addi $a0, $a0,1
#	addi $a1, $a1,1
#	beq $t2, $t1, result #Se encontrar algum '\n', terminar a concatenação
#	j conc
#
#result:
#	la $a0, str1
#	li $v0, 4
#	syscall
############################################################

#	la $a0, str1
#	la $a1, str2
#	li $t2, 32		#Contador
#	li $t3, 10		#Identificador ASCII para '\n'
#strcpy:
#	lb $t1, 0($a1) #le byte da string2
#	sb $t1,0($a0)	#escreve byte lido em string1
#	addi $t2, $t2, -1 #decrementa contador
#	addi $a0, $a0, 1
#	addi $a1, $a1, 1
#	beq $t2, $zero, final
#	j strcpy
#final:
#	la $v0, str1
#	move $a0, $v0
#	li $v0, 4
#	syscall
#	li $v0, 10
#	syscall

#############################################################
#	la $a0, str1 		#endereço da string 1
#	la $a1, str2  		#endereço da string 2
#	li $t3, 32			#Inicializa contador
#	li $t4, 10			#Identificador ASCII para '\n'
#strcmp:
#	lb $t1, 0($a0)
#	lb $t2, 0($a1)
#	sub $t1, $t1, $t2		#Caso t1 == t2, t1 recebe 0 devido a subtração dos dois operandos
#	addi $t3, $t3, -1
#	addi $a0, $a0, 1
#	addi $a1, $a1, 1
#	beq $t2, $t4, comparacao_igual	#Se o conteúdo de t2 chegar ao final, então a comparação é igual
#	beq $t1, $zero, strcmp  #Caso seja igual, prosseguir na comparação
#	
#fimcomp:
#	addi $a0, $a0, -1
#	lb $t1, 0($a0)   #Salva o primeiro caractere diferente
#	addi $a0, $a0, 1
#	lb $t2, 0($a0)	#Salva o caractere seguinte aquele que diferiu pela primeira vez
#	slt $t1, $t2, $t1 #O caractere seguinte é menor que o primeiro?
#	beq $t1,$zero, comparacao_diferente #Se for, retornar -1
#	li $a0, 1 #Retornar 1 em caso contrário
#	li $v0,1
#	syscall
#	li $v0, 10
#	syscall
#	
#comparacao_diferente:
#	li $v0, -1
#	move $a0, $v0
#	li $v0,1
#	syscall
#	li $v0, 10
#	syscall
#	
#comparacao_igual:
#	li $v0, 0
#	move $a0, $v0
#	li $v0,1
#	syscall
#	li $v0, 10
#	syscall


####################################################################

#	la $a0, str1
#	li $t3, 32
#	li $t4, 10
#	li $t5, 0
#	li $t6, 19
#strlwr:
#	lb $t0, 0($a0)
#	beq $t0, $t4, end
#	addi $t5, $t0, -97  #Caso o caractere seja minúsculo, apenas pulá-lo
#	bgez $t5, jumpadress
#	addi $t5, $t0, -47	#Caso o caractere seja especial, apenas pulá-lo
#	blez $t5, jumpadress
#	addi $t0, $t0, 32   #Adiciona-se 32 para tornar o caractere minúsculo
#	sb $t0, 0($a0)
#	addi $t3, $t3, -1
#	beq $t3, $zero, end
#	addi $a0, $a0, 1
#	j strlwr
#	
#jumpadress:
#	addi $a0, $a0, 1
#	j strlwr
#
#end:
#	la $a0, str1
#	li $v0, 4
#	syscall
#
####################################################################
#	la $a0, str1
#	li $t3, 32
#	li $t4, 10
#	li $t5, 0
#	li $t6, 19
#strupr:
#	lb $t0, 0($a0)
#	beq $t0, $t4, end
#	addi $t5, $t0, -90 #Caso o caractere seja Maiúsculo, apenas pulá-lo
#	blez $t5, jumpadress1
#	addi $t5, $t0, -47	#Caso o caractere seja especial, apenas pulá-lo
#	blez $t5, jumpadress
#	addi $t0, $t0, -32 #Adiciona-se -32 para tornar o caractere minúsculo
#	sb $t0, 0($a0)
#	addi $t3, $t3, -1
#	beq $t3, $zero, end
#	addi $a0, $a0, 1
#	j strupr
#	
#jumpadress1:
#	addi $a0, $a0, 1
#	j strupr
#
#end:
#	la $a0, str1
#	li $v0, 4
#	syscall