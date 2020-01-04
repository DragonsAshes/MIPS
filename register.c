#include "register.h"
#include "memory.h"

static registers regs;

void initRegisters()
{
	int i;
	for( i = 0; i < NB_REGS; i++)
		regs.general[i] = 0;
	regs.pc = REG_MEM;
	regs.hi = 0;
	regs.lo = 0;
}

int alias_to_nbr(char* reg_name)
{
	int nbr;
	if (!strcmp(reg_name, "zero"))
		nbr = 0;
	else if (!strcmp(reg_name, "at"))
		nbr = 1;
	else if (!strcmp(reg_name, "gp"))
		nbr = 28;
	else if (!strcmp(reg_name, "sp"))
		nbr = 29;
	else if (!strcmp(reg_name, "fp"))
		nbr = 30;
	else if (!strcmp(reg_name, "ra"))
		nbr = 31;
	else if (reg_name[0] == 'v')
		nbr = 2+atoi(reg_name+1);
	else if (reg_name[0] == 'a')
		nbr = 4+atoi(reg_name+1);
	else if (reg_name[0] == 't')
		nbr = 8+(atoi(reg_name+1) < 8 ? atoi(reg_name+1) : (8+atoi(reg_name+1)));
	else if (reg_name[0] == 's')
		nbr = 16+atoi(reg_name+1);
	else if (reg_name[0] == 'k')
		nbr = 26+atoi(reg_name+1);
	else
		nbr = atoi(reg_name);

	return nbr;
}


//Faire la sécurité en cas d'overflow
void set_reg(char* instruction, char r1, char r2, char r3, short imm)
{
	if( !strcmp(instruction, "ROTR") )
		regs.general[r1] = (regs.general[r2] << regs.general[r3]); //Erreur ici
	else if ( !strcmp(instruction, "ADDI") )
		regs.general[r1] = regs.general[r2] + imm;
	else if ( !strcmp(instruction, "ADD") )
		regs.general[r1] = regs.general[r2] + regs.general[r3];
	else if ( !strcmp(instruction, "BNE") )
		regs.pc = ( regs.general[r1] != regs.general[r2] ? (regs.pc+(imm << 2)) : regs.pc);
	else if ( !strcmp(instruction, "AND") )
		regs.general[r1] = regs.general[r2] & regs.general[r3];
	else if ( !strcmp(instruction, "BEQ") )
		regs.pc = ( regs.general[r1] == regs.general[r2] ? (regs.pc+(imm << 2)) : regs.pc);
	else if ( !strcmp(instruction, "BGTZ") )
		regs.pc = ( regs.general[r1] > 0 ? (regs.pc+(imm << 2)) : regs.pc);
	else if ( !strcmp(instruction, "BLEZ") )
		regs.pc = (regs.general[r1] <= 0 ? (regs.pc+(imm << 2)) : regs.pc);
	else if ( !strcmp(instruction, "DIV") ) //Cas ou regs.general[r2] == 0
	{
		regs.lo = regs.general[r1] / regs.general[r2];
		regs.hi = regs.general[r1] % regs.general[r2];
	}
	else if ( !strcmp(instruction, "JR") )
	{
		print_reg();
		regs.pc = regs.general[r1] + 4;
	}
	else if ( !strcmp(instruction, "LUI") )
		regs.general[r1] = ( imm << 16 );
	else if ( !strcmp(instruction, "LW") )
		regs.general[r1] = readMemory(REG_MEM+(unsigned int)regs.general[r2]+(unsigned int)imm);
	else if ( !strcmp(instruction, "MFHI") )
		regs.general[r1] = regs.hi;
	else if ( !strcmp(instruction, "MFLO") )
		regs.general[r1] = regs.lo;
	else if ( !strcmp(instruction, "MULT") )
	{
		long prod = regs.general[r1] * regs.general[r2];
		regs.lo = prod & 0xffffffff;
		regs.hi = (prod & 0xffffffff00000000) >> 32;
	}
	else if ( !strcmp(instruction, "OR") )
		regs.general[r1] = regs.general[r2] | regs.general[r3];
	else if ( !strcmp(instruction, "SLL") )
		regs.general[r1] = regs.general[r2] << r3;
	else if ( !strcmp(instruction, "SLT") )
		regs.general[r1] = ( regs.general[r2] < regs.general[r3] );
	else if ( !strcmp(instruction, "SRL") )
		regs.general[r1] = ( regs.general[r2] >> r3 );
	else if ( !strcmp(instruction, "SUB") )
		regs.general[r1] = regs.general[r2] - regs.general[r3];
	else if ( !strcmp(instruction, "SW") )
		write_ins_in_Memory( (REG_MEM+(unsigned int)regs.general[r2]+(unsigned int)imm), regs.general[r1]);
	else if ( !strcmp(instruction, "XOR") )
		regs.general[r1] = regs.general[r2] ^ regs.general[r3];

}

void print_reg()
{
	int i;
	printf("************ REGISTERS STATES ************ \n");
	for ( i = 0; i < NB_REGS; i++)
	{
		if( i%4 == 0)
			printf("\n");
		printf("$%d = %d           ", i, regs.general[i]);

	}
	printf("\n");
	printf("pc = %d || hi = %d || lo = %d \n\n", regs.pc, regs.hi, regs.lo);	
}

void print_one_reg(char index)
{
	printf("\n\nr%d = %d\n\n", index, regs.general[index]);
}

int get_pc()
{
	return regs.pc;
}

void set_pc()
{
	regs.pc += 4;
}