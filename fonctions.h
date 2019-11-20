#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readfile(FILE* input);
void chartohex(FILE* input, FILE* output);
int evaluate(char* opcode, char* line);
