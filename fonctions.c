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




void encode(FILE* input, FILE* output)
{
	char line[128];
	char* token = NULL;
	char* tmp = NULL;
	char* separators = " ,\n\r";
	int instruction;
	int compteur;
    int i = 0;
	while( fgets(line, sizeof line, input ) != NULL)
	{
		compteur = 0;
		tmp = strdup(line);
        while(*tmp == ' ')
            tmp++;
		token = strsep(&tmp, separators);
        printf("test=%s&\n", token);
		instruction = evaluate(token, tmp);
        if(instruction == -1){
            printf("ligne vide\n");
            continue;
        }
        printf("%d / %08x\n",i, instruction);
        i++;
		fprintf(output, "%08x\n", instruction);
	}
}

int ADD(char* line)
{
	char* token = NULL;
	char* tmp = NULL;
	int i = 0;
	char* data[3];
	int res = 0;
	tmp = strdup(line);
	while( token = strsep(&tmp, ",") )
		data[i++] = token;
	res = 32;
	res += 0 << 6;
	res += atoi(data[0]+1)<<11;
	res += atoi(data[2]+1)<<16;
	res += atoi(data[1]+1)<<21;
    
	return res;
}


int ADDI(char* line) //rajouter une sécurité (nb d'arguments)
{
	char* token = NULL; 
	char* tmp = NULL;
	int i=0;
	char* data[3];
	int res=0;
	tmp = strdup(line);
	while( token = strsep(&tmp, ",") )
		data[i++] = token;
	res = atoi(data[2]);
	res += atoi(data[0]+1)<<16;
	res += atoi(data[1]+1)<<21;
	res += 8<<26;

	return res;

}

int AND(char* line)
{
	char* token = NULL;
	char* tmp = NULL;
	int i=0;
	char* data[3];
	int res=0;
	tmp = strdup(line);
	while( token = strsep(&tmp, ",") )
		data[i++] = token;
	res = 36;
	res += 0<<6;
	res += atoi(data[0]+1)<<11;
	res += atoi(data[2]+1)<<16;
	res += atoi(data[1]+1)<<21;

	return res;
}

int BEQ(char* line)
{
	char* token = NULL;
	char* tmp = NULL;
	int i=0;
	char* data[3];
	int res=0;
	tmp = strdup(line);
	while( token = strsep(&tmp, ",") )
		data[i++] = token;
	res = atoi(data[2]);
	res += atoi(data[1]+1)<<16;
	res += atoi(data[0]+1)<<21;
	res += 4<<26;

	return res;
}

int BGTZ(char* line)
{
	char* token = NULL;
	char* tmp = NULL;
	int i=0;
	char* data[2];
	int res=0;
	tmp = strdup(line);
	while( token = strsep(&tmp, ",") )
		data[i++] = token;
	res = atoi(data[1]);
	res += atoi(data[0]+1)<<21;
	res += 7<<26;

	return res;
}

int BLEZ(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[2];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = atoi(data[1]);
    res += atoi(data[0]+1)<<21;
    res += 6<<26;

    return res;
}

int BNE(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[3];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = atoi(data[2]);
    res += atoi(data[1]+1)<<16;
    res += atoi(data[0]+1)<<21;
    res += 5<<26;

    return res;
}

int DIV(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[2];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 26;
    res += atoi(data[1]+1)<<16;
    res += atoi(data[0]+1)<<21;

    return res;
}

int J(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[1];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = atoi(data[0]);
    res += 2<<26;

    return res;
}

int JAL(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[1];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = atoi(data[0]);
    res += 3<<26;

    return res;
}

int JR(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[1];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 8;
    res += atoi(data[0]+1)<<21;

    return res;
}

int LUI(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[2];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = atoi(data[1]);
    res += atoi(data[0]+1)<<16;
    res += 15<<26;

    return res;
}

int LW(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[2];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = atoi(data[1]);
    res += atoi(data[0]+1)<<16;
    res += 35<<26;

    return res;
}

int MFHI(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[1];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 16;
    res += atoi(data[0]+1)<<11;

    return res;
}

int MFLO(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[1];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 18;
    res += atoi(data[0]+1)<<11;

    return res;
}

int MULT(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[2];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 24;
    res += atoi(data[1]+1)<<16;
    res += atoi(data[0]+1)<<21;

    return res;
}

int NOP(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[1];
    int res;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 0;
    return res;
}

int OR(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[3];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 37;
    res += atoi(data[0]+1)<<11;
    res += atoi(data[2]+1)<<16;
    res += atoi(data[1]+1)<<21;

    return res;
}

int ROTR(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[3];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 2;
    res += atoi(data[2])<<6;
    res += atoi(data[0]+1)<<11;
    res += atoi(data[1]+1)<<16;
    res += 1<<21;

    return res;
}

int SLL(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[3];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 0;
    res += atoi(data[2])<<6;
    res += atoi(data[0]+1)<<11;
    res += atoi(data[1]+1)<<16;

    return res;
}

int SLT(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[3];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 42;
    res += atoi(data[0]+1)<<11;
    res += atoi(data[2]+1)<<16;
    res += atoi(data[1]+1)<<21;

    return res;
}

int SRL(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[3];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 2;
    res += atoi(data[2])<<6;
    res += atoi(data[0]+1)<<11;
    res += atoi(data[1]+1)<<16;

    return res;
}

int SUB(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[3];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 34;
    res += atoi(data[0]+1)<<11;
    res += atoi(data[2]+1)<<16;
    res += atoi(data[1]+1)<<21;

    return res;
}

int SW(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[2];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = atoi(data[1]);
    res += atoi(data[0]+1)<<16;
    res += 43<<26;

    return res;
}

int SYSCALL(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[1];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 12;

    return res;
}

int XOR(char* line)
{
    char* token = NULL;
    char* tmp = NULL;
    int i=0;
    char* data[3];
    int res=0;
    tmp = strdup(line);
    while( token = strsep(&tmp, ",") )
        data[i++] = token;
    res = 38;
    res += atoi(data[0]+1)<<11;
    res += atoi(data[2]+1)<<16;
    res += atoi(data[1]+1)<<21;

    return res;
}

int evaluate(char* opcode, char* line)
{
	char* data = malloc(2);
	int res;
	if(strcmp(opcode, "ADD") == 0)
		res = ADD(line);

    else if(strcmp(opcode, "ADDI") == 0)
    	res = ADDI(line);

    else if(strcmp(opcode, "AND") == 0)
    	res = AND(line);

    else if(strcmp(opcode, "BEQ") == 0)
    	res = BEQ(line);

    else if(strcmp(opcode, "BGTZ") == 0)
    	res = BGTZ(line);

    else if(strcmp(opcode, "BLEZ") == 0)
        res = BLEZ(line);

    else if(strcmp(opcode, "BNE") == 0)
        res = BNE(line);

    else if(strcmp(opcode, "DIV") == 0)
        res = DIV(line);

    else if(strcmp(opcode, "J") == 0)
        res = J(line);

    else if(strcmp(opcode, "JAL") == 0)
        res = JAL(line);

    else if(strcmp(opcode, "JR") == 0)
        res = JR(line);

    else if(strcmp(opcode, "LUI") == 0)
        res = LUI(line);

    else if(strcmp(opcode, "LW") == 0)
        res = LW(line);

    else if(strcmp(opcode, "MFHI") == 0)
        res = MFHI(line);

    else if(strcmp(opcode, "MFLO") == 0)
        res = MFLO(line);

    else if(strcmp(opcode, "MULT") == 0)
        res = MULT(line);

    else if(strcmp(opcode, "NOP") == 0)
        res = NOP(line);

    else if(strcmp(opcode, "OR") == 0)
        res = OR(line);

    else if(strcmp(opcode, "ROTR") == 0)
        res = ROTR(line);

    else if(strcmp(opcode, "SLL") == 0)
        res = SLL(line);

    else if(strcmp(opcode, "SLT") == 0)
        res = SLT(line);

    else if(strcmp(opcode, "SRL") == 0)
        res = SRL(line);

    else if(strcmp(opcode, "SUB") == 0)
        res = SUB(line);

    else if(strcmp(opcode, "SW") == 0)
        res = SW(line);

    else if(strcmp(opcode, "SYSCALL") == 0)
        res = SYSCALL(line);

    else if(strcmp(opcode, "XOR") == 0)
        res = XOR(line);

    else
        res = -1;

    return res;
}