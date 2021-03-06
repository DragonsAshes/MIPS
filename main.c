#include "fonctions.h"
#include "memory.h"
#include "register.h"

void interactif_mode()
{
	initMemory();
	char command[50] = "\0";
	int instruction;
	while( strcmp(command, "EXIT")){
		printf("\nEnter Instruction. Enter 'EXIT' if it's over : ");
		fgets(command, 50, stdin); //Récupération de ce qui est écrit par l'utilisateur

		//On procède directement à l'exécution, ceci est possible car on traite seulement les instructions en séquences
		instruction = encode_instruction(command);
		if( instruction == -1 )
			continue;
		decode(instruction);
		print_reg();
		printMemory();
	}

}

void non_interactif_mode(char* input_file, char* output_file, int pas)
{
	FILE *input = fopen(input_file, "r");
	if( input == NULL )
	{
		printf("Erreur lors de l'ouverture du fichier lecture\n");
		exit(EXIT_FAILURE);
	}

	FILE *output = fopen(output_file, "w");
	if( output == NULL )
	{
		printf("Erreur lors de l'ouverture du fichier écriture\n");
		exit(EXIT_FAILURE);
	}

	readfile(input);
	printf("\nEncodage...\n");
	initMemory();

	encode(input, output);
	printf("Le code hexadécimal a été généré\n");


	int hex;
	char letter[2];
	while( (hex = readMemory(DATA_MEM+get_pc())) != 0xffffffff ) //On traite chaque instruction en mémoire jusqu"à l'instruction EXIT
	{
		printf("\nPC = %d \n", get_pc());
		printf("Processing instruction:\n%08x	", hex);
		set_pc();  //On incrémente le PC
		decode(hex);
		if( pas )
		{
			do{
				printf("Press [c] to continue, [r] to print registers or [m] to print memory\n");
				scanf("%s", letter);
				if( letter[0] == 'r' )
					print_reg();
				else if( letter[0] == 'm' )
					printMemory();
				else if ( letter[0] == 'c' )
					printf("\nNext instruction : \n");
				else
					printf("Wrong command\n");
			}while( letter[0] != 'c' );
		}
	}
	print_reg();
	printMemory();	
	fclose(input);
	fclose(output);
}


int main(int argc, char** argv)
{

	printf("--------------------------- COMPILATEUR MIPS MILHEIRO PEUBLE Mélissa, FOUCHER Sébastien ---------------------------\n");

	if( argc > 4 || argc == 2)
	{
		printf("Erreur lors de l'exécution: format : ./emul-mips ['input file' 'output file' [-pas] ]\n");
		return -1;
	}

	if ( argc == 1 )
		interactif_mode(0);

	else if ( argc == 3 )
		non_interactif_mode(argv[1], argv[2], 0);
	else if ( argc == 4 )
	{
		if( !strcmp( argv[3], "-pas") )
			non_interactif_mode(argv[1], argv[2], 1);
		else
		{
			printf("Erreur lors de l'exécution: format : ./emul-mips ['input file' 'output file' [-pas] ]\n");
			return -1;
		}
	}

	
	free(mem);
	return 0; 
}