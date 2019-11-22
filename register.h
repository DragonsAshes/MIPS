#include <stdlin.h>
#include <stdio.h>
#include <string.h>

typedef struct //On définit une structure contenant tout les registres
{
	int allreg[32];
	int pc;
	int hi;
	int lo;
} registers;

