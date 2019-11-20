all : main.o fonctions.o
	gcc main.o fonctions.o -o main

main.o : main.c
	gcc -c main.c -o main.o -g

fonctions.o : fonctions.c
	gcc -c fonctions.c -o fonctions.o -g

clear : 
	rm *.o