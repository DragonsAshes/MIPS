#include "register.h"
#include "memory.h"


static registers regs; //On définit une variable global pour que toutes les fonctions y aient accès.

void initialize_regs()
{
	for(int i = 0; i < 32; i++)
		regs.allreg[i] = 0;
	regs.pc = 0;
	regs.hi = 0;
	regs.lo = 0;
}

void print_regs()
{
	for(int i = 0; i < 32; i++)
		printf("r%d : %d\n", i, regs.allreg[i]);
	printf("pc : %d\nhi : %d\nlo : %d", regs.pc, regs.hi, regs.lo);
}

void reg_add(char* data)
{
	regs.allreg[(data[0]+1)] = regs.allreg[(data[1]+1)] + regs.allreg[(data[2]+1)];	
	//Vérifier l'overflow
}

void reg_addi(char* data)
{
	regs.allreg[(data[0]+1)] = regs.allreg[(data[1]+1)] + regs.allreg[data[2]];	
	//Vérifier l'overflow
}

void reg_and(char* data)
{
	regs.allreg[(data[0]+1)] = regs.allreg[(data[1]+1)] & regs.allreg[(data[2]+1)];	
}

void reg_beq(char* data)
{

}

void reg_bgtz(char* data)
{
	if( regs.allreg[(data[0]+1)] > 0 )
		regs.pc += data[1]<<2;
}

void reg_blez(char* data)
{
	if( regs.allreg[(data[0]+1)] <= 0 )
		regs.pc += data[1]<<2;
}

void reg_bne(char* data)
{
	if( regs.allreg[(data[0]+1)] != regs.allreg[(data[1]+1)] )
		regs.pc += data[2]<<2;
}

void reg_div(char* data)
{
	regs.hi = regs.allreg[(data[0]+1)]/regs.allreg[(data[1]+1)];
	regs.lo = regs.allreg[(data[0]+1)]%regs.allreg[(data[1]+1)];
	//Vérifier les calculs
}

void reg_j(char* data)
{
	regs.pc = data[0]<<2;
}

void reg_jal(char* data)
{
	regs.allreg[31] = regs.pc+8;
	regs.pc += data[0]<<2;
}

void reg_jr(char* data)
{
	regs.pc = regs.allreg[(data[0]+1)];
}

void reg_lui(char* data)
{
	regs.allreg[(data[0]+1)] = data[1]<<16;
}

void reg_lw(char* data)
{

}

void reg_mfhi(char* data)
{
	regs.allreg[(data[0]+1)] = regs.hi;
}

void reg_mflo(char*data)
{
	regs.allreg[(data[0]+1)] = regs.lo;	
}

void reg_mult(char* data) //A vérifier
{
	regs.lo = ( regs.allreg[(data[0]+1)]*regs.allreg[(data[1]+1)] )&&0x00ff;
	regs.hi = ( regs.allreg[(data[0]+1)]*regs.allreg[(data[1]+1)] )>>16;
}

void reg_or(char* data)
{
	regs.allreg[(data[0]+1)] = regs.allreg[(data[1]+1)] | regs.allreg[(data[1]+1)];
}

void reg_rotr(char* data)
{
	regs.allreg[(data[0]+1)] = regs.allreg[(data[1]+1)] >> regs.allreg[(data[2]+1)];
} //A vérifier

void reg_sll(char* data)
{
	regs.allreg[(data[0]+1)] = regs.allreg[(data[1]+1)] << regs.allreg[data[2]];
}

void reg_slt(char *data)
{
	regs.allreg[(data[0]+1)] = regs.allreg[(data[1]+1)] < regs.allreg[(data[2]+1)];
}

void reg_srl(char* data)
{
	regs.allreg[(data[0]+1)] = regs.allreg[(data[1]+1)] >> regs.allreg[data[2]];
}

void reg_sub(char* data)
{
	regs.allreg[(data[0]+1)] = regs.allreg[(data[1]+1)] - regs.allreg[data[2]];
}

void reg_sw(char* data)
{

}

//Syscall ??

void reg_xor(char* data)
{
	regs.allreg[(data[0]+1)] = regs.allreg[(data[1]+1)] ^ regs.allreg[(data[1]+1)];
}