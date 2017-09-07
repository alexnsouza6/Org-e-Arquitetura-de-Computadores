#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Sim.h"



/* 
	adress - endereço equivalente ao registrador
	kte - offset
*/


//lw $t1,-100($t2)        Load word : Set $t1 to contents of effective memory word address
int32_t lw(uint32_t address, int16_t kte){
	/* Lê um inteiro alinhado - endereços múltiplos de 4 */
	int32_t pos;

	if(address%4!=0) printf("Invalid Address \n");
	else pos = (address + (int32_t) kte)/4;
	return mem[pos];
	
}

//lh $t1,($t2)            Load Halfword : Set $t1 to sign-extended 16-bit value from effective memory halfword address
int32_t lh(uint32_t address, int16_t kte){
	int32_t pos = (address + kte)/4;
	int32_t res	= (address + kte)%4;
	int32_t word_aux = mem[pos], word = mem[pos];


	if(res==0){	
		word_aux = word_aux & 0x0000ffff;
		word = word & 0x0000ffff;
		word_aux = word_aux >> 15;
		if(word_aux == 1) word = word | 0xffff0000;
	}

	else{
		word_aux = word_aux >> 16;
		word = word >> 16;
		word_aux = word_aux >> 15;
		if(word_aux == 1) word = word | 0xffff0000;
	}
	return word;

}


//lb $t1,-100($t2)        Load byte : Set $t1 to sign-extended 8-bit value from effective memory byte address
int32_t lb(uint32_t address, int16_t kte){
	int32_t	pos = (address + kte)/4;
	int32_t	res = (address + kte)%4;
	int32_t	word = mem[pos];
	int8_t	*byte;

	switch(res){
		case 0:
			word = word & 0x000000ff;
			*byte = word & 0x000000f0;
			if(*byte>0x7) word = word | 0xffffffff;
			break;
		case 1:
			word = word << 8;
			word = word & 0x000000ff;
			*byte = word & 0x000000f0;
			if(*byte>0x7) word = word | 0xffffffff;
			break;
		case 2:
			word = word << 16;
			word = word & 0x000000ff;
			*byte = word & 0x000000f0;
			if(*byte>0x7) word = word | 0xffffffff;
			break;
		case 3:
			word = word << 24;
			word = word & 0x000000ff;
			*byte = word & 0x000000f0;
			if(*byte>0x7) word = word | 0xffffffff;
		break;
		default:
			printf("Different from expected - Error loading byte");
	}

	return word;
}

//sw $t1,-100($t2)        Store word : Store contents of $t1 into effective memory word address
void sw(uint32_t address, int16_t kte, int32_t dado){
	int32_t pos = (address + kte)/4;
	mem[pos] = dado;
}


//sh $t1,-100($t2)        Store halfword : Store the low-order 16 bits of $t1 into the effective memory halfword address
void sh(uint32_t address, int16_t kte, int16_t dado){
	int32_t pos = (address+kte)/4;
	int32_t res	= (address+kte)%4;
	int32_t word = mem[pos];

	if(res==0){	
		dado = dado & 0x0000ffff;
		mem[pos] = dado;
	}
	else{	
		word = word << 16;
		mem[pos] = dado;
	}
}

//sb $t1,-100($t2)        Store byte : Store the low-order 8 bits of $t1 into the effective memory byte address
void sb(uint32_t address, int16_t kte, int8_t dado){
	int32_t	pos = (address + kte)/4;
	int32_t	res = (address + kte)%4;

	switch(res){
		case 0:
			dado = dado & 0x000000ff;
			break;
		case 1:
			dado = dado << 8;
			dado = dado & 0x000000ff;
			break;
		case 2:
			dado = dado << 16;
			dado = dado & 0x000000ff;
			break;
		case 3:
			dado = dado << 24;
			dado = dado & 0x000000ff;
			break;
		default:
			printf("Different from expected - Error loading byte");
	}

}	

void load_mem(char* arquivo, int32_t address){
	/* Ler todas as palavras dos arquivos .bin*/
	FILE *fp;

	fp = fopen(arquivo,"rb");
	if(!fp) printf("File can't be opened");

	if(address%4 != 0) printf("Address not valid");
	address = address/4;
	fread(&mem[address],4,1,fp);

	while(!feof(fp)){
		address++;
		fread(&mem[address],4,1,fp);
	}
	fclose(fp);
}