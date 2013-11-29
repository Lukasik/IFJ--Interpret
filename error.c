#include "error.h"


// chybove hlasky
char *errorMessage[]=
{
	"(Re)alokace se nezdarila! \n",
	"Nepodarilo se otevrit zdrojovy kod ! \n",
	"Chyba v zadani parametru \n",
	"Syntakticka chyba v kodu\n",
	"Lexikalni chyba v kodu\n",
	"Funkce již existuje\n",
	"Chyba při práci se zásobníkem\n",
	"Nedeklarováná proměnná\n",
	"Typova nekompatibilita\n",
	"Deleni nulou\n",
	"Nedeklarovana funkce\n",
	"funkce byla volana s malo parametry\n",
	"Ostatní běhové chyby\n",
};
// vypise chybove hlaseni
// prvni parametr je kod hlasky
// druhy parametr je navratovy kod ukonceni programu
void printError(int errorCode, int returnCode)
{
	// fprintf(stderr, "CHYBA %d: %s",returnCode,errorMessage[errorCode]);
	gfreeAll();
	fclose(f);
	exit(returnCode);
}

