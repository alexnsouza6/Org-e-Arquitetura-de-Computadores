#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MEM_SIZE 4096


//lw $t1,-100($t2)        Load word : Set $t1 to contents of effective memory word address
	/* 	adress - endereço equivalente ao registrador
		kte - offset	*/
int32_t lw(uint32_t address, int16_t kte){
	/* Lê um inteiro alinhado - endereços múltiplos de 4 */
	int32_t pos = (address + kte)/4;
	return MEM[pos];

}
//lh $t1,($t2)            Load Halfword : Set $t1 to sign-extended 16-bit value from effective memory halfword address
int32_t lh(uint32_t address, int16_t kte){
	int32_t pos = (address + kte)/4;
	int32_t res	= (address+kte)%4;
	int32_t word = MEM[pos];

	if(res==0)	word = word & 0x0000ffff;
	else	word = word << 16;

	return word;

}



int32_t lb(uint32_t adress, int16_t kte){
	int32_t	pos = (address + kte)/4;
	int32_t	res = (address + kte)%4;
	int32_t	word = MEM[pos];

	switch(res){
		case 0:
			word = word & 0x000000ff;
			break;
		case 1:
			word = word << 8;
			word = word & 0x000000ff;
			break;
		case 2:
			word = word << 12;
			word = word & 0x000000ff;
			break;
		case 3:
			word = word << 16;
			word = word & 0x000000ff;
		break;
		default:
			printf("Different from expected - Error loading byte");
	}

	return word;
}

void sw(uint32_t address, int16_t kte, int32_t dado){
	int32_t pos = (address + kte)/4;
	MEM[pos] = dado;
}

void sh(uint32_t address, int16_t kte, int16_t dado){
	int32_t pos = (address+kte)/4;
	int32_t res	= (address+kte)%4;

	if(res==0){	
		dado = dado & 0x0000ffff;
		MEM[pos] = dado;
	}
	else{	
		word = word << 16;
		MEM[pos] = dado;
	}
}

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
			dado = dado << 12;
			dado = dado & 0x000000ff;
			break;
		case 3:
			dado = dado << 16;
			dado = dado & 0x000000ff;
			break;
		default:
			printf("Different from expected - Error loading byte");
	}

}