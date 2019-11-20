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
	char* token = NULL;
	char* tmp = NULL;
	char* separators = " ,\n";
	char* opcode;
	int compteur;
	while( fgets(line, sizeof line, input ) != NULL)
	{
		compteur = 0;
		tmp = strdup(line);
		token = strsep(&tmp, separators);
		printf("%s ", token);
		opcode = evaluate(token);
		printf("%d, %d ", opcode[0], opcode[1]);

		


		while((token = strsep(&tmp, separators)) != NULL)
		{
			printf("%s", token);
			compteur++;
		}
		printf("cpt : %d\n", compteur);
		printf("\n");
	}
}

char* evaluate(char* opcode)
{
	char* data = malloc(2);
	if(strcmp(opcode, "ADD") == 0)
	{
        data[0] = 0x20;
    	data[1] = 3;
    }
    else if(strcmp(opcode, "ADDI") == 0)
    {
        data[0] = 0x8;
        data[1] = 3;
    }
    else if(strcmp(opcode, "AND") == 0)
    {
        data[0] = 0x24;
        data[1] = 3;
    }
    else if(strcmp(opcode, "BEQ") == 0)
    {
        data[0] = 0x4;
        data[1] = 3;
    }
    else if(strcmp(opcode, "BGTZ") == 0)
    {
        data[0] = 0x7;
        data[1] = 2;
    }
    else if(strcmp(opcode, "BLEZ") == 0)
    {
        data[0] = 0x6;
        data[1] = 2;
    }
    else if(strcmp(opcode, "BNE") == 0)
    {
        data[0] = 0x5;
        data[1] = 3;
    }
    else if(strcmp(opcode, "DIV") == 0)
    {
        data[0] = 0x1a;
        data[1] = 2;
    }
    else if(strcmp(opcode, "J") == 0)
    {
        data[0] = 0x2;
        data[1] = 1;
    }
    else if(strcmp(opcode, "JAL") == 0)
    {
        data[0] = 0x3;
        data[1] = 1;
    }
    else if(strcmp(opcode, "JR") == 0)
    {
        data[0] = 0x8;
        data[1] = 1;
    }
    else if(strcmp(opcode, "LUI") == 0)
    {
        data[0] = 0xf;
        data[1] = 2;
    }
    else if(strcmp(opcode, "LW") == 0)
    {
        data[0] = 0x23;
        data[1] = 2;
    }
    else if(strcmp(opcode, "MFHI") == 0)
    {
        data[0] = 0x10;
        data[1] = 1;
    }
    else if(strcmp(opcode, "MFLO") == 0)
    {
        data[0] = 0x12;
        data[1] = 1;
    }
    else if(strcmp(opcode, "MULT") == 0)
    {
        data[0] = 0x18;
        data[1] = 2;
    }
    else if(strcmp(opcode, "NOP") == 0)
    {
        data[0] = 0;
        data[1] = 0;
    }
    else if(strcmp(opcode, "OR") == 0)
    {
        data[0] = 0x25;
        data[1] = 3;
    }
    else if(strcmp(opcode, "ROTR") == 0)
    {
        data[0] = 0x2;
        data[1] = 3;
    }
    else if(strcmp(opcode, "SLL") == 0)
    {
        data[0] = 0;
        data[1] = 3;
    }
    else if(strcmp(opcode, "SLT") == 0)
    {
        data[0] = 0x2a;
        data[1] = 3;
    }
    else if(strcmp(opcode, "SRL") == 0)
    {
        data[0] = 0x2;
        data[1] = 3;
    }
    else if(strcmp(opcode, "SUB") == 0)
    {
        data[0] = 0x22;
        data[1] = 3;
    }
    else if(strcmp(opcode, "SW") == 0)
    {
        data[0] = 0x2b;
        data[1] = 2;
    }
    else if(strcmp(opcode, "SYSCALL") == 0)
    {
        data[0] = 0xc;
        data[1] = 0;
    }
    else if(strcmp(opcode, "XOR") == 0)
    {
        data[0] = 0x26;
        data[1] = 3;
    }
    else
    {
    	data[0] = 0xff;
    	data[1] = 0;
    }
    return data;
}