// CHYBOVA HLASENI

#include <stdio.h>
#include <stdlib.h>


// chybove hlasky
char *errorMessage[]=
{
	[ALLOCERROR] = "(re)alokace se nezdarila!",
};

// vypise chybove hlaseni
// prvni parametr je kod hlasky
// druhy parametr je navratovy kod ukonceni programu
void printError(int errorCode, int returnCode)
{
	printf("CHYBA %d: %s\n",returnCode,errorMessage[errorCode]);
	exit(returnCode);
}