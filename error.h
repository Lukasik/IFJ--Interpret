//HLAVICKA PRO MODUL CHYBOVYCH HLASENI
#ifndef H_ERROR
#define H_ERROR 1

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "garbage.h"

//prototyp funkce
void printError(int errorCode, int returnCode);

extern FILE* f;
// chybove kody -- pro indexy errorMessage
enum errs
{
	ALLOCERROR,
	SOURCECODEERR,
	PARAMSERROR,
	SYNTAXERR,
	LEXICALERR,
	FUNCTIONEXISTS,
	STACKERROR,
	VARIABLENOTEXISTS,
	INCOMPATIBLETYPE,
	ZERODIVISION,
	UNDECLAREDFUNCTION,
	FEWPARAMETERS,
	OTHERSERRS,
	RETYPEERR,
	SAMEPARAM,
};

// navratove kody programu
enum returns
{
	INTERPRETERROR=99,
	SYNTAXERROR=2,
	LEXICALERROR=1,
	FUNCTIONDEFINITIONERROR=3,
	UNDECLAREDVARIABLE=5,
	INCOMPATIBLE=12,
	ZERODIV=10,
	PARAMMISSING=4,
	OTHERS=13,
	RETYPE=11,
};

#endif
