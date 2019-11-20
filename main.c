#include "fonctions.h"

int main(int argc, char** argv)
{

	printf("--------------------------- COMPILATEUR MIPS MILHEIRO PEUBLE Mélissa, FOUCHER Sébastien ---------------------------\n");

	if( argc != 3 )
	{
		printf("Erreur lors de l'exécution: format : ./main 'input file' 'output file'\n");
		return -1;
	}

	FILE *input = fopen(argv[1], "r");
	if( input == NULL )
	{
		printf("Erreur lors de l'ouverture du fichier lecture\n");
		return -1;
	}

	FILE *output = fopen(argv[2], "wb");
	if( output == NULL )
	{
		printf("Erreur lors de l'ouverture du fichier écriture\n");
		return -1;
	}

	readfile(input);
	printf("passage à la fonction chartohex\n");
	chartohex(input, output);

	printf("Tout s'est bien passé\n");




	return 0; 
}