// CHYBOVA HLASENI

#include <stdio.h>
#include <stdlib.h>


// chybove hlasky
char *errorMessage[]=
{
	"(Re)alokace se nezdarila! \n",
	"Nepodarilo se otevrit zdrojovy kod ! \n",
	"Chyba v zadani parametru \n",
	"Syntakticka chyba v kodu"
};

// vypise chybove hlaseni
// prvni parametr je kod hlasky
// druhy parametr je navratovy kod ukonceni programu
void printError(int errorCode, int returnCode)
{
	printf("CHYBA %d: %s\n",returnCode,errorMessage[errorCode]);
	exit(returnCode);
}