#ifndef REGISTER_H
#define REGISTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_REGS 32

typedef struct {
	int general[NB_REGS];
	int pc;
	int hi;
	int lo;
} registers;

void initRegisters();

int alias_to_nbr(char* reg_name);

void set_reg(char* instruction, char r1, char r2, char r3, short imm);

void print_reg();

void print_one_reg(char index);

int get_pc();

void set_pc();

#endif