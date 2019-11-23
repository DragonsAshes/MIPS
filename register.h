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

void initialize_regs();
void print_regs();

void reg_add();
void reg_addi();
void reg_and();
void reg_beq();
void reg_bgtz();
void reg_blez();
void reg_bne();
void reg_div();
void reg_j();
void reg_jal();
void reg_jr(char* data);
void reg_lui(char* data);
void reg_lw(char* data);
void reg_mfhi(char* data);
void reg_mflo(char*data);
void reg_mult(char* data);
void reg_or(char* data);
void reg_rotr(char* data);
void reg_sll(char* data);
void reg_slt(char *data);
void reg_srl(char* data);
void reg_sub(char* data);
void reg_sw(char* data);
void reg_xor(char* data);
