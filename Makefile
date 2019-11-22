all : main.o fonctions.o
	gcc main.o fonctions.o -o main

main.o : main.c
	gcc -c main.c -o main.o -g

fonctions.o : fonctions.c
	gcc -c fonctions.c -o fonctions.o -g

register.o : register.c
	gcc -c register.c -o register.o -g

memory.o : memory.c
	gcc -c memory.c -o memory.o -g

clear : 
	rm *.o