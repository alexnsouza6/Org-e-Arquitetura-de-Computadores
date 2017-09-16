#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Sim.h"
#define MEM_SIZE 4096
#define init_text 0x00000000
#define init_data 0x00002000
int32_t mem[MEM_SIZE];

int main(){
	char text[] = "text.bin", data[] = "data.bin";
	int32_t r, address=0, dado, offset=0, limit_inf, limit_sup;
	int contador = 0, i=0, opcao, arquivo;

	printf("-------------------\n");
	printf("Carregando Arquivos\n");
	printf("-------------------\n");
	printf("Simulador MIPS\n");
	printf("-------------------\n");
	printf("\nArquivo para leitura:\n");
	printf("(1) - Text.bin\n");
	printf("(2) - Data.bin\n");
	printf("Arquivo para leitura:\n");
	scanf("%d",&arquivo);
	if(arquivo == 1){
		limit_inf = 0x0;
		limit_sup = 0x44;
	}
	else{
		limit_inf = 0x2000;
		limit_sup = 0x204c;

	}

	/* text.bin memory load */
	load_mem(text,init_text);
	
	printf("\n");	

	/*data.bin memory load */
	load_mem(data,init_data);
	
	while(opcao!=0){
		printf("\n*******************\n");
		printf("(0) - Exit\n");
		printf("(1) - Load Word\n");
		printf("(2) - Load Half\n");
		printf("(3) - Load Byte\n");
		printf("(4) - Store Word\n");
		printf("(5) - Store Half\n");
		printf("(6) - Store Byte\n");
		printf("\n*******************\n");
		printf("Opcao desejada: ");
		scanf("%d", &opcao);
		switch(opcao){
		case 1:
			address = limit_inf;
			/* Loop referente ao teste da funçao LW para text.bin */
			while(address <= limit_sup){
				r = lw(address,0);
				printf("mem[%d]=0x%x\t", address/4,r);
				address += 4;
				contador++;
				if(contador%4==0) printf("\n");
			}
		break;
		case 2:
			address = limit_inf;
			/* Loop referente ao teste da função LH para text.bin */
			while(address <= limit_sup){
				r = lh(address,0);
				printf("mem[%d]=0x%x\t", address/4,r);
				address += 2;
				contador++;
				if(contador%8==0) printf("\n");
			}
		break;
		
		case 3:
				address = limit_inf;
		/* Loop referente ao teste da função LB para text.bin*/
			while(address <= limit_sup){
				r = lb(address,0);
				printf("mem[%d]=0x%x\t", address/4,r);
				address += 1;
				contador++;
				if(contador%16==0) printf("\n");		
		 }
		 break;
	
			case 4:
				address = limit_inf;
			/* Loop referente ao testa função SW para text.bin*/
				while(address <= limit_sup){
					sw(address,0,address);
					printf("mem[%i]=0x%x\t", address/4,mem[address/4]);
					address += 4;
					contador++;
					if(contador%4==0) printf("\n");	
				}
			break;
	
			case 5:
				address = limit_inf;
			/* Loop referente ao teste da função SH para text.bin*/
				while(address <= limit_sup){
					sh(address,0,address);
					printf("mem[%i]=0x%x\t", address/4,mem[address/4]);
					address += 2;
					contador++;
					if(contador%8==0) printf("\n");	
				}
			break;
	
			case 6:
				address = limit_inf;
			/* Loop referente ao teste da função SB para text.bin*/
				while(address <= limit_sup){
					sh(address,0,address);
					printf("mem[%i]=0x%x\t", address/4,mem[address/4]);
					address++;
					contador++;
					if(contador%16==0) printf("\n");	
				}
			break;
			}
	}
	return 0;
}