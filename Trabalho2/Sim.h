#define MEM_SIZE 4096

void load_mem(char* arquivo, int32_t address);
int32_t lw(uint32_t address, int16_t kte);
int32_t lh(uint32_t address, int16_t kte);
int32_t lb(uint32_t adress, int16_t kte);
void sw(uint32_t address, int16_t kte, int32_t dado);
void sh(uint32_t address, int16_t kte, int16_t dado);
void sb(uint32_t address, int16_t kte, int8_t dado);
void advance_pc(int offset);
void fetch();
void decode();
void execute();
void step();
void run();
void analyze_funct();
void dump_reg(char format);
void dump_mem(int start, int end, char format);


int breg[32]; //Register's Base
int32_t mem[MEM_SIZE];
uint32_t pc, hi, lo; //Program Counter Register
uint32_t npc;
uint32_t ri; //Register which yields the instruction to be executed
int8_t opcode, rs, rt, rd, shamt, funct;  
int16_t addconst, k16;
uint32_t k26;

typedef enum{
	EXT = 0x00,  // R -> olhar funct
	LW = 0x23,   // I
	LB = 0x20,   // I
	LBU = 0x24,	 // I
	LH = 0x21,  // I
	LHU = 0x25, // I
	LUI = 0x0F, // I
	SW = 0x2B, // I
	SB = 0x28, // I
	SH = 0x29, // I
	BEQ = 0x04, // I
	BNE = 0x05,	// I
	BLEZ = 0x06, // I
	BGTZ = 0x07, // I
	ADDI = 0x08, // I
	SLTI = 0x0A, // I
	SLTIU = 0x0B, // I
	ANDI = 0x0C, // I
	ORI = 0x0D, // I
	XORI = 0x0E, // I
	J = 0x02, // J
	JAL = 0x03	// J
}OPCODES;


enum FUNCT{
	ADD = 0x20, 
	SUB = 0x22,
	MULT = 0x18,
	DIV = 0x1A, 
	AND = 0x24,
	OR = 0x25, 
	XOR = 0x26,
	NOR = 0x27,
	SLT = 0x2A,
	JR = 0x08,
	SLL = 0x00,
	SRL = 0x02,
	SRA = 0x03,
	SYSCALL = 0x0c,
	MFHI = 0x10,
	MFLO = 0x12
};