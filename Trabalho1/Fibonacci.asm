.data
primos: .half 1, 3, 5, 7, 11, 13, 17, 19
size:   .byte -8, 2, 3, 4, 5, 6
msg:    .asciiz "Os oito primeiros numeros primos sao : "
space:  .ascii " "
  .text
	la $t0,primos		#carrega endereço inicial do array
	la $t1,size		#carrega endereco do tamanho do array
	lb $t1,2($t1)		#carrega o tamanho em t1
	li $v0,4
	la $a0,msg
	syscall
	
loop:	beq $t1, $zero, exit	#se processou todo o array, encerra o programa
	li $v0, 1		#prepara para imprimir inteiro
	lw $a0, 0($t0)		#inteiro a ser exibido
	syscall
	li $v0,4		#prepara para imprimir string
	la $a0,space
	syscall
	addi $t0, $t0, 4	#incremente indice do array	
	addi $t1, $t1, -1	#decrementa contador
	j loop
exit:	li $v0, 10
	syscall