#include "memory.h"

unsigned char* mem;

void initMemory()
{
	mem = (unsigned char*)calloc(MEM_SIZE, sizeof(unsigned char));
}

void write_ins_in_Memory(unsigned int addr, unsigned int instruction)
{
	int i;
	//Peut etre ajouter une vérification de possibilités pour l'accès mémoire
	for( i = 0; i < 4; i++ )
		mem[addr+i] = (char)(instruction >> 8*(3-i));
}

unsigned int readMemory(unsigned int addr)
{
	unsigned int ret = 0;
	int i;
	for( i = 0; i < 4; i++ )
		ret = (ret << 8) + mem[addr+i];
	return ret;
}

void printMemory()
{
	int i;
	printf("\n**** MEMORY STATE ****\nADDR : VALUE (in decimal)\n");
	int tmp = 0;
	for( i = 0; i < MEM_SIZE/2; i+=4 )
	{
		if ( i%16 == 0)
			printf("\n");
		printf("@%08x : %d		", i, readMemory(REG_MEM+i));

	}
	printf("\n");
}