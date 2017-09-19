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

int32_t lhu(uint32_t address, int16_t kte){
	int32_t pos = (address + kte)/4;
	int32_t res	= (address + kte)%4;
	int32_t word_aux = mem[pos], word = mem[pos];


	if(res==0){	
		word_aux = word_aux & 0x0000ffff;
		word = word & 0x0000ffff;
	}

	else{
		word_aux = word_aux >> 16;
		word = word >> 16;
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

int32_t lbu(uint32_t address, int16_t kte){
	int32_t	pos = (address + kte)/4;
	int32_t	res = (address + kte)%4;
	int32_t	word = mem[pos], word_aux = mem[pos];

	switch(res){
		case 0:
			word = word & 0x000000ff;
			word_aux = word >> 7;
			break;

		case 1:
			word = word >> 8;
			word = word & 0x000000ff;			
			break;

		case 2:
			word = word >> 16;
			word = word & 0x000000ff;	
			break;

		case 3:
			word = word >> 24;
			word = word & 0x000000ff;		
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


void fetch(){
	ri = mem[pc/4];
	pc = pc + 4;
}


void decode(){
	int32_t opmask = 0xfc000000;
	int32_t rsmask = 0x03e00000;
	int32_t rtmask = 0x001f0000;
	int32_t rdmask = 0x0000f800;
	int32_t shamtmask = 0x000007c0;
	int32_t functmask = 0x0000003f;
	int32_t immediatemask = 0x0000ffff;

	opcode = (ri & opmask);
	opcode = opcode >> 26; 

	switch(opcode){
		
		default:
			printf("Opcode can't be find");

		/*Type R*/
		case 0x0:
			rs =  (ri & rsmask);
			rs = rs >> 21;
			rt =  (ri & rtmask);
			rt = rt >> 16;
			rd =  (ri & rdmask);
			rd = rd >> 11;
			shamt = (ri & shamtmask);
			shamt = shamt >> 6;
			funct = (ri & functmask);
		break;

		/* Type I */
		case 0x04 ... 0x0F:
			rs = (ri & rsmask);
			rs = rs >> 21;
			rt = (ri & rtmask);
			rt = rt >> 16;
			k16 = (ri & immediatemask);
		break;

		case 0x20 ... 0x2B:
			rs = (ri & rsmask);
			rs = rs >> 21;
			rt = (ri & rtmask);
			rt = rt >> 16;
			k16 = (ri & immediatemask);
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
		break;

		case LW:
			breg[rt] = lw(breg[rs],k16);
		break;

		case LBU:
			breg[rt] = lbu(breg[rs],k16);
		break;

		case LB:
			breg[rt] = lb(breg[rs],k16);
		break;

		case LH:
			breg[rt] = lh(breg[rs],k16);

		break;

		case LHU:
			breg[rt] = lhu(breg[rs],k16);
		break;

		case LUI:
			breg[rt] = (int32_t) (k16 << 16);
		break;

		case SW:
			sw(breg[rs],k16,breg[rt]);
		break;

		case SB:
			sb(breg[rs],k16,breg[rt]);
		break;

		case SH:
			sh(breg[rs],k16,breg[rt]);
		break;

		case BEQ:
			if (breg[rs] == breg[rt]) pc += k16 << 2;
		break;

		case BNE:
			if (breg[rs] != breg[rt]) pc += k16 << 2;
		break;

		case BLEZ:
			if (breg[rs] <= 0) pc += k16 << 2;
		break;

		case BGTZ:
			if(breg[rs]>0) pc += k16 << 2;
		break;

		case ADDI:
			breg[rt] = breg[rs] + k16;
		break;

		case SLTI:
			if(breg[rs] < k16)
				breg[rt] = 1;
			else
				breg[rt] = 0;

		break;

		case SLTIU:
			if(breg[rs] < k16)
				breg[rt] = 1;
			else
				breg[rt] = 0;

		break;

		case ANDI:
			breg[rt] = breg[rs] & k16;

		break;

		case ORI:
			breg[rt] = breg[rs] | k16;

		break;

		case XORI:
			breg[rt] = breg[rs] ^ k16;

		break;

		case ADDIU:
			breg[rt] = breg[rs] + k16;
		break;

		case J:
			pc = k26 << 2;
		break;

		case JAL:
			breg[31] = pc;
			pc = k26 << 2;
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
			pc = breg[rs];
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
	int32_t str;
    int i=0;                                                      
	/* Prints integer */
	if(breg[2] == 1)
		printf("%d", breg[4]);
	
	/* Ends program */
	else if(breg[2] == 10) exit(0);

	/* Prints string */
	else if(breg[2] == 4){
		str = lw(breg[4],0);                                           
        while(str != 0){                                              
          str = lb(breg[4],i);                                         
          i++;                                                        
          printf("%c", str);                                          
        }
	}
		

}


void step(){
	fetch();
	decode();
	execute();
}

void run(){
	int i = 0;
	pc = 0;
	while(pc<0x2000/4 || i<4096) {
		step();
		i++;
	}
}

void dump_mem(int start, int end, char format){
	int i;
	if(format == 'h'){
		printf("\n");
		for(i=start;i<end;i++)
			printf("mem[%d] = 0x%x\n", i, mem[i]);
	}
	else if(format == 'd'){
		printf("\n");
		for(i=start;i<end;i++)
			printf("mem[%d] = %d\n", i, mem[i]);
	}
	else printf("Incorrect Format\n");
}

void dump_reg(char format){
	int i;

	if(format == 'h'){
		for(i=0;i<32;i++) printf("Register %d: %x\n",i,breg[i]);
		printf("PC Register: %x\n", pc);
		printf("Hi Register: %x\n", hi);
		printf("Lo Register: %x\n", lo);
	}
	else{
		for(i=0;i<32;i++) printf("Registrador %d: %d\n",i,breg[i]);
		printf("PC Register: %d\n", pc);
		printf("Hi Register: %d\n", hi);
		printf("Lo Register: %d\n", lo);
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