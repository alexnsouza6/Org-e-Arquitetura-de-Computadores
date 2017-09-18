#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Sim.h"
#define MEM_SIZE 4096
#define init_text 0x00000000
#define init_data 0x00002000
uint32_t pc; //Program Counter Register
uint32_t ri;
uint32_t opcode, rs, rt, rd, shamt, funct; 
int16_t addconst;
int32_t mem[MEM_SIZE];

int main(){
	char text[] = "text.bin", data[] = "data.bin";
	int32_t r, address=0, dado, offset=0, limit_inf, limit_sup;
	int contador = 0, i=0, opcao, arquivo;

	/* Starts the pc position and the next position of pc */
	pc = 0;

	/* text.bin memory load */
	load_mem(text,init_text);
	
	printf("\n");	

	/*data.bin memory load */
	load_mem(data,init_data);
	
	run();
	 
	return 0;
}