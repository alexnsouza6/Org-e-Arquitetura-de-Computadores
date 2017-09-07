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
	int32_t r, address=0;
	int contador = 0;


	/* text.bin memory load */
	load_mem(text,init_text);
	
	printf("\n\n\n\n");	

	/*data.bin memory load */
	load_mem(data,init_data);

	
	/* Loop referente ao teste da funçao LW para text.bin */
	// while(address <= 0x44){
	// 	r = lw(address,0);
	// 	address += 4;
	// 	printf("%x\t", r);
	// 	contador++;
	// 	if(contador%4==0) printf("\n");
	// }

	/* Loop referente ao testa da função LH para text.bin */
	while(address <= 0x44){
		r = lh(address,0);
		address += 2;
		printf("%x\t",r);
	}

	return 0;
}