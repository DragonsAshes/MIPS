#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 512
#define DATA_MEM 0x00000000
#define REG_MEM 0x00000100

unsigned char* mem;

void initMemory();

void write_ins_in_Memory(unsigned int addr, unsigned int instruction);

unsigned int readMemory(unsigned int addr);

void printMemory();


#endif