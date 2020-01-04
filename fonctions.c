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
    unsigned int offset = 0;
	while( fgets(line, sizeof line, input ) != NULL)
	{
		compteur = 0;
		tmp = strdup(line);
        while(*tmp == ' ')
            tmp++;
		token = strsep(&tmp, separators);
		instruction = evaluate(token, tmp);
        if(instruction == -1){
            continue;
        }
        printf("%d / %08x\n",i, instruction);
        i++;
		fprintf(output, "%08x\n", instruction);
        write_ins_in_Memory( (DATA_MEM+offset), instruction );
        offset += 4;
	}
    write_ins_in_Memory( (DATA_MEM+offset), 0xffffffff);
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
    res = res & 0x0000ffff;
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
    res = res & 0x0000ffff;
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
    res = res & 0x0000ffff;
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
    res = res & 0x0000ffff;
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
    res = res & 0x0000ffff;
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
    res = res & 0x0000ffff;
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
    res = res & 0x0000ffff;
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
    res = res & 0x0000ffff;
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

    else if(strcmp(opcode, "SY SCALL") == 0)
        res = SYSCALL(line);

    else if(strcmp(opcode, "XOR") == 0)
        res = XOR(line);

    else
        res = -1;

    return res;
}

void decode(unsigned int hexa)
{
    //Réalisation des masques de décodage
    if(hexa == 0)
    {
        printf("{NOP}\n");
        return;
    }
    char type;
    char op = 0, rs = 0, rt = 0, rd = 0, sa = 0;
    short imm = 0;
    if( (hexa & 0xfc000000) == 0 ) //On distingue le type R des deux autres types.
    {
        type = 'R';
        op = hexa & 0x3f;
        sa = (hexa >> 6) & 0x1f;
        rd = (hexa >> 11) & 0x1f;
        rt = (hexa >> 16) & 0x1f;
        rs = (hexa >> 21) & 0x1f; 

        switch(op)
        {
            case 2:
                if( rs == 1 )
                {
                    printf("{ROTR $%d, $%d, $%d}\n", rd, rt, sa);
                    set_reg("ROTR", rd, rt, sa, 0);
                }
                else{
                    printf("{SRL $%d, $%d, $%d}\n", rd, rt, sa);
                    set_reg("SRL", rd, rt, sa, 0);
                }
                break;
            case 32:
                printf("{ADD $%d, $%d, $%d}\n", rd, rs, rt);
                set_reg("ADD", rd, rs, rt, 0);
                break;
            case 36:
                printf("{AND $%d, $%d, $%d}\n", rd, rs, rt);
                set_reg("AND", rd, rs, rt, 0);
                break;
            case 26:
                printf("{DIV $%d, $%d}\n", rs, rt);
                set_reg("DIV", rs, rt, 0, 0);
                break;
            case 8:
                printf("{JR $%d}\n", rs);
                set_reg("JR", rs, 0, 0, 0);
                break;
            case 16:
                printf("{MFHI $%d}\n", rd);
                set_reg("MFHI", rd, 0, 0, 0);
                break;
            case 18:
                printf("{MFLO $%d}\n", rd);
                set_reg("MFLO", rd, 0, 0, 0);
                break;
            case 24:
                printf("{MULT $%d, $%d}\n", rs, rt);
                set_reg("MULT", rs, rt, 0, 0);
                break;
            case 37:
                printf("{OR $%d, $%d, $%d}\n", rd, rs, rt);
                set_reg("OR", rd, rs, rt, 0);
                break;
            case 0:
                printf("{SLL $%d, $%d, $%d}\n", rd, rs, sa);
                set_reg("SLL", rd, rt, sa, 0);
                break;
            case 42:
                printf("{SLT $%d, $%d, $%d}\n", rd, rs, rt);
                set_reg("SLT", rd, rs, rt, 0);
                break;
            case 34:
                printf("{SUB $%d, $%d, $%d}\n", rd, rs, rt);
                set_reg("SUB", rd, rs, rt, 0);
                break;
            case 38:
                printf("{XOR $%d, $%d, $%d}\n", rd, rs, rt);
                set_reg("XOR", rd, rs, rt, 0);
                break;
        }
    }
    //Réaliser un masque pour chaque fonction pour les types I et J
    else
    {
        //Traiter Jump et Jump and link a part
        op = (hexa & 0xfc000000) >> 26;
        rs = (hexa >> 21) & 0x1f;
        rt = (hexa >> 16) & 0x1f;
        imm = hexa & 0xffff;

        switch(op)
        {
            case 8:
                printf("{ADDI $%d, $%d, %d}\n", rt, rs, imm);
                set_reg("ADDI", rt, rs, 0, imm);
                break;
            case 5:
                printf("{BNE $%d, $%d, %d}\n", rs, rt, imm);
                set_reg("BNE", rs, rt, 0, imm);
                break;
            case 4:
                printf("{BEQ $%d, $%d, %d}\n",rs ,rt ,imm);
                set_reg("BEQ", rs, rt, 0, imm);
                break;
            case 7:
                printf("{BGTZ $%d, %d}\n", rs, imm);
                set_reg("BGTZ", rs, 0, 0, imm);
                break;
            case 6:
                printf("{BLEZ $%d, %d}\n", rs, imm);
                set_reg("BLEZ", rs, 0, 0, imm);
                break;
            case 15:
                printf("{LUI $%d, %d}\n", rt, imm);
                set_reg("LUI", rt, 0, 0, imm);
                break;
            case 35:
                printf("{LW $%d; $%d, %d}\n", rt, rs, imm);
                set_reg("LW", rt, rs ,0, imm);
                break;
            case 43:
                printf("{SW $%d, $%d, %d}\n", rt, rs, imm);
                set_reg("SW", rt, rs, 0, imm);
                break;
        }
    }

}