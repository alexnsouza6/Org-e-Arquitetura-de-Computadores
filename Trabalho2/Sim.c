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

	if((address + (int32_t) kte)%4!=0) printf("Invalid Address \n");
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
	int32_t	word = mem[pos], word_aux = mem[pos];

	switch(res){
		case 0:
			word = word & 0x000000ff;
			word_aux = word >> 7;
			if(word_aux == 1) word = word | 0xffffff00;
			
			break;
		case 1:
			word = word >> 8;
			word = word & 0x000000ff;
			word_aux = word >> 7;
			if(word_aux == 1) word = word | 0xffffff00;
			
			break;
		case 2:
			word = word >> 16;
			word = word & 0x000000ff;
			word_aux = word >> 7;
			if(word_aux == 1) word = word | 0xffffff00;
			
			break;
		case 3:
			word = word >> 24;
			word = word & 0x000000ff;
			word_aux = word >> 7;
			if(word_aux == 1) word = word | 0xffffff00;
		break;
		default:
			printf("Different from expected - Error loading byte");
	}

	return word;
}

//sw $t1,-100($t2)        Store word : Store contents of $t1 into effective memory word address
void sw(uint32_t address, int16_t kte, int32_t dado){
	int32_t pos;

	if((address + (int32_t) kte)%4!=0) printf("Invalid Address \n");
	else pos = (address + (int32_t) kte)/4;
	mem[pos] = dado;
}


//sh $t1,-100($t2)        Store halfword : Store the low-order 16 bits of $t1 into the effective memory halfword address
void sh(uint32_t address, int16_t kte, int16_t dado){
	int32_t pos = (address+(int32_t)kte)/4;
	int32_t res	= (address+(int32_t)kte)%4;
	int32_t word = 0x0;
	word += (int32_t) dado;


	if(res==0){	
		mem[pos] = mem[pos] & 0xffff0000;
		mem[pos] += word;
	}
	else{	
		mem[pos] = mem[pos] & 0x0000ffff;
		word = word << 16;
		mem[pos] += word;
	}
}

//sb $t1,-100($t2)        Store byte : Store the low-order 8 bits of $t1 into the effective memory byte address
void sb(uint32_t address, int16_t kte, int8_t dado){
	int32_t	pos = (address + (int32_t)kte)/4;
	int32_t	res = (address + (int32_t)kte)%4;
	int32_t word = 0x0;

	word += (int32_t) dado;

	switch(res){
		case 0:
			mem[pos] = mem[pos] & 0x000000ff;
			mem[pos] += word;
			break;
		case 1:
			mem[pos] = mem[pos] << 8;
			mem[pos] = mem[pos] & 0x000000ff;
			mem[pos] += word;
			break;
		case 2:
			mem[pos] = mem[pos] << 16;
			mem[pos] = mem[pos] & 0x000000ff;
			mem[pos] += word;
			break;
		case 3:
			mem[pos] = mem[pos] << 24;
			mem[pos] = mem[pos] & 0x000000ff;
			mem[pos] += word;
			break;
		default:
			printf("Different from expected - Error loading byte");
	}

}

void advance_pc(int offset){
	pc = npc;
	npc += offset;
}


void fetch(){
	int32_t pos;
	int32_t word = 0x0;

	/* Pc position is converted to a position in mem Array */
	pos = pc/4;  
	word = mem[pos];
	advance_pc(4);

	/*Then, the instruction is saved in Register Instruction */
	ri = word;

}


void decode(){
	int32_t opmask = 0xfc000000;
	int32_t rsmask = 0x03e00000;
	int32_t rtmask = 0x001f0000;
	int32_t rdmask = 0x0000f800;
	int32_t shamtmask = 0x000007c0;
	int32_t functmask = 0x0000003f;
	int16_t immediatemask = 0x0000ffff;


	opcode = (int8_t)(ri & opmask); 

	switch(opcode){
		
		default:
			printf("Opcode can't be find");

		/*Type R*/
		case 0x0:
			rs = (int8_t) (ri & rsmask);
			rt = (int8_t) (ri & rtmask);
			rd = (int8_t) (ri & rdmask);
			shamt = (int8_t)(ri & shamtmask);
			funct = (int8_t)(ri & functmask);
		break;

		/* Type I */
		case 0x04 ... 0x0F:
			rs = (int8_t)(ri & rsmask);
			rt = (int8_t)(ri & rtmask);
			k16 = (int16_t)(ri & immediatemask);
		break;

		case 0x20 ... 0x2B:
			rs = (int8_t)(ri & rsmask);
			rt = (int8_t)(ri & rtmask);
			k16 = (int16_t)(ri & immediatemask);
		break;


		/* Type J */
		case 0x02 ... 0x03:
			k26 = ri & 0x03ffffff;
		break;

	}
}

void execute(){

	switch(opcode){
		case EXT:
			analyze_funct();
			advance_pc(4);
		break;

		case LW:
			breg[rt] = mem[rs + k16];
			advance_pc(4);
		break;

		case LB:
			breg[rt] = mem[rs + k16];
			advance_pc(4);
		break;

		case LH:
			breg[rt] = mem[rs + k16];
			advance_pc(4);
		break;

		case LHU:
			breg[rt] = mem[rs + k16];
			advance_pc(4);
		break;

		case LUI:
			breg[rt] = k16 << 16;
			advance_pc(4);
		break;

		case SW:
			mem[rs + k16] = breg[rt];
			advance_pc(4);
		break;

		case SB:
			mem[rs + k16] = breg[rt];
			advance_pc(4);
		break;

		case SH:
			mem[rs + k16] = breg[rt];
			advance_pc(4);
		break;

		case BEQ:
			if (breg[rs] == breg[rt])
				advance_pc(k26<<2);
			else
				advance_pc(4);
		break;

		case BNE:
			if (breg[rs] != breg[rt])
				advance_pc(k26<<2);
			else
				advance_pc(4);
		break;

		case BLEZ:
			if (breg[rs] <= 0)
				advance_pc(k26<<2);
			else
				advance_pc(4);
		break;

		case BGTZ:
			if(breg[rs]>0)
				advance_pc(k26<<2);
			else
				advance_pc(4);
		break;

		case ADDI:
			breg[rt] = breg[rs] + k16;
			advance_pc(4);
		break;

		case SLTI:
			if(breg[rs] < k16)
				breg[rt] = 1;
			else
				breg[rt] = 0;
			advance_pc(4);
		break;

		case SLTIU:
			if(breg[rs] < k16)
				breg[rt] = 1;
			else
				breg[rt] = 0;
			advance_pc(4);
		break;

		case ANDI:
			breg[rt] = breg[rs] & k16;
			advance_pc(4);
		break;

		case ORI:
			breg[rt] = breg[rs] | k16;
			advance_pc(4);
		break;

		case XORI:
			breg[rt] = breg[rs] ^ k16;
			advance_pc(4);
		break;

		case J:
			pc = npc;
			npc = (pc & 0xf0000000) | (k26 <<2);
		break;

		case JAL:
			breg[31] = pc + 8;
			pc = npc;
			npc = (pc & 0xf0000000) | (k26 <<2);
		break;
	}	
}

void analyze_funct(){
	switch(funct){
		default:
			printf("Funct Opcode Not Found\n");
		break;

		case ADD:
			breg[rd] = breg[rs] + breg[rt];
		break;

		case SUB:
			breg[rd] = breg[rs] - breg[rt];
		break;

		case MULT:
			lo = breg[rs] * breg[rt];
		break;

		case DIV:
			lo = breg[rs] / breg[rt];
			hi = breg[rs] % breg[rt];
		break;

		case AND:
			breg[rd] = breg[rs] & breg[rt];
		break;

		case OR:
			breg[rd] = breg[rs] | breg[rt];
		break;

		case XOR:
			breg[rd] = breg[rs] ^ breg[rt];
		break;

		case NOR:
			breg[rd] = ~(breg[rs] | breg[rt]);
		break;

		case SLT:
			if(breg[rs] < breg[rt]) breg[rd] = 1;
			else breg[rd] = 0;
		break;

		case JR:
			pc = npc;
			npc = breg[rs];
		break;

		case SLL:
			breg[rd] = breg[rt] << shamt;
		break;

		case SRL:
			breg[rd] = breg[rt] >> shamt;
		break;

		case SRA:
			breg[rd] = breg[rt] >> shamt;
		break;

		case SYSCALL:
			analyze_syscall();
		break;

		case MFHI:
			breg[rd] = hi;
		break;

		case MFLO:
			breg[rd] = lo;
		break;
	}
}

void analyze_syscall(){
	char *c;
	/* Prints integer */
	if(breg[2] == 1)
		printf("%d", breg[4]);
	
	/* Ends program */
	else if(breg[2] == 10)
		exit(0);

	/* Prints string */
	else if(breg[2] == 4)
		sprintf(c,"%d",breg[2]);
}


void step(){
	fetch();
	decode();
	execute();
}

void run(){
	while(pc<4096){
		fetch();
		decode();
		execute();
	}
}

void dump_mem(int start, int end, char format){
	int i;
	if(format == 'h'){
		printf("\n");
		for(i=start;i<end;i++)
			printf("mem[%d] = 0x%x\n", i, mem[i]);
	}
	else{
		printf("\n");
		for(i=start;i<end;i++)
			printf("mem[%d] = %d\n", i, mem[i]);
	}
}

void dump_reg(char format){
	int i;

	if(format == 'h'){
		for(i=0;i<32;i++)
			printf("Registrador %d: %x",i,breg[i]);
		printf("PC Register: %x", pc);
		printf("Hi Register: %x", hi);
		printf("Lo Register: %x", lo);
	}
	else{
		for(i=0;i<32;i++)
			printf("Registrador %d: %d",i,breg[i]);
		printf("PC Register: %d", pc);
		printf("Hi Register: %d", hi);
		printf("Lo Register: %d", lo);
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