#include "fonctions.h"


void readfile(FILE* input)
{
	char line[128];
	int i = 1;

	while( fgets ( line, sizeof line, input ) != NULL)
	{
		printf("Instruction %d : %s", i, line);
		i++;
	}
	fseek(input, 0, SEEK_SET);
}


void chartohex(FILE* input, FILE* output)
{
	char line[128];
	char* instruction;
	char* svptr;
	while( fgets(line, sizeof line, input ) != NULL)
	{
		instruction = strtok_r(instruction, line, &svptr);
		printf("%s\n", instruction);
	}
}