#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "register.h"
#include "memory.h"

void readfile(FILE* input);
void encode(FILE* input, FILE* output);
int evaluate(char* opcode, char* line);


int ADD(char* line);
int ADDI(char* line);
int AND(char* line);
int BEQ(char* line);
int BGTZ(char* line);
int BNE(char* line);
int DIV(char* line);
int J(char* line);
int JAL(char* line);
int JR(char* line);
int LUI(char* line);
int LW(char* line);
int MFHI(char* line);
int MFLO(char* line);
int MULT(char* line);
int NOP(char* line);
int OR(char* line);
int ROTR(char* line);
int SLL(char* line);
int SLT(char* line);
int SRL(char* line);
int SUB(char* line);
int SW(char* line);
int SYSCALL(char* line);
int XOR(char* line);