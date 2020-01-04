all : main.o fonctions.o memory.o register.o
	gcc main.o fonctions.o memory.o register.o -o emul-mips

main.o : main.c
	gcc -c main.c -o main.o -g

fonctions.o : fonctions.c
	gcc -c fonctions.c -o fonctions.o -g

memory.o : memory.c
	gcc -c memory.c -o memory.o -g

register.o : register.c
	gcc -c register.c -o register.o -g

clear : 
	rm *.o