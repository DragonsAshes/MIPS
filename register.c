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
	regs.pc = data[0];
}

void reg_jal(char* data)
{
	//pas compris
}