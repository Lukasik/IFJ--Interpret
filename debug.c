#include "debug.h"

char* tokenNames[256] = {
	[BEGIN] = "BEGIN",
	[END] = "END",
	[NULLV] = "NULLV",
	[BOOLEAN] = "BOOLEAN",
	[WHILE] = "WHILE",
	[RETURN] = "RETURN",
	[IF] = "IF",
	[ELSE] = "ELSE",
	[FUNCTION] = "FUNCTION",

	[PLUS] = "PLUS",
	[MINUS] = "MINUS",
	[TIMES] = "TIMES",
	[DIVISION] = "DIVISION",

	[BIGGER] = "BIGGER",
	[LESSER] = "LESSER",
	[BIGGEREQUAL] = "BIGGEREQUAL",
	[LESSEREQUAL] = "LESSEREQUAL",
	[EQUAL] = "EQUAL",
	[NOTEQUAL] = "NOTEQUAL",

	[ASSIGN] = "ASSIGN",

	[ID] = "ID",
	[INTEGER] = "INTEGER",
	[DOUBLE] = "DOUBLE",
	[STRING] = "STRING",
	[VAR] = "VAR",
	[VALUE] = "VALUE",
	[E] = "E",

	[SEMICOLON] = "SEMICOLON",
	[DOT] = "DOT",
	[COMMA] = "COMMA",
	[OPENPAREN] = "OPENPAREN",
	[CLOSEPAREN] = "CLOSEPAREN",
	[OPENBRACE] = "OPENBRACE",
	[CLOSEBRACE] = "CLOSEBRACE",

	[INVALIDCHAR] = "INVALIDCHAR",
	[NARGUMENT] = "NARGUMENT",
	[NARGUMENTLIST1] = "NARGUMENTLIST1",
	[NARGUMENTLIST2] = "NARGUMENTLIST2",
	[NBLOCK] = "NBLOCK",
	[NCOMMAND] = "NCOMMAND",
	[NCOMMANDLIST] = "NCOMMANDLIST",
	[NFUNCTION] = "NFUNCTION",
	[NFUNCTIONCALLEXPRESSION] = "NFUNCTIONCALLEXPRESSION",
	[NPARAMLIST1] = "NPARAMLIST1",
	[NPARAMLIST2] = "NPARAMLIST2",
	[NPROGRAM] = "NPROGRAM",
	[NRETURN] = "NRETURN",
	[NSTATEMENT] = "NSTATEMENT",
	[NEXPRESSION] = "NEXPRESSION",
	[NOTHING] = "NOTHING",
	[REDUCE] = "REDUCE",
	[SHIFT] = "SHIFT",
	[EQUALSIGN] = "EQUALSIGN",
	[NEXPRESSIONPAREN] = "NEXPRESSIONPAREN",
};

void BSTF_Print2(sFunction* TempTree, char* sufix, char fromdir)
{
     if (TempTree != NULL)
     {
	char* suf2 = (char*) malloc(strlen(sufix) + 4);
	strcpy(suf2, sufix);
        if (fromdir == 'L')
	{
	   suf2 = strcat(suf2, "  |");
	   printf("%s\n", suf2);
	}
	else
	   suf2 = strcat(suf2, "   ");
	BSTF_Print2(TempTree->rptr, suf2, 'R');
        printf("%s  +-[%s]\n", sufix, TempTree->key);
	strcpy(suf2, sufix);
        if (fromdir == 'R')
	   suf2 = strcat(suf2, "  |");
	else
	   suf2 = strcat(suf2, "   ");
	BSTF_Print2(TempTree->lptr, suf2, 'L');
	if (fromdir == 'R') printf("%s\n", suf2);
	free(suf2);
    }
}

void BSTF_Print(sFunction* TempTree)
{
  printf("Struktura binarního stromu funkcí:\n");
  printf("\n");
  if (TempTree != NULL)
     BSTF_Print2(TempTree, "", 'X');
  else
     printf("Strom funkcí je prázdný\n");
  printf("\n");
  printf("=================================================\n");
}

void BSTV_Print2(sVariable* TempTree, char* sufix, char fromdir)
{
     if (TempTree != NULL)
     {
	char* suf2 = (char*) malloc(strlen(sufix) + 4);
	strcpy(suf2, sufix);
        if (fromdir == 'L')
	{
	   suf2 = strcat(suf2, "  |");
	   printf("%s\n", suf2);
	}
	else
	   suf2 = strcat(suf2, "   ");
	BSTV_Print2(TempTree->rptr, suf2, 'R');
        printf("%s  +-[%s]\n", sufix, TempTree->key);
	strcpy(suf2, sufix);
        if (fromdir == 'R')
	   suf2 = strcat(suf2, "  |");
	else
	   suf2 = strcat(suf2, "   ");
	BSTV_Print2(TempTree->lptr, suf2, 'L');
	if (fromdir == 'R') printf("%s\n", suf2);
	free(suf2);
    }
}

void BSTV_Print(sFunction * TempTree)
{
  printf("%s: struktura binarního stromu proměnných:\n", TempTree->key);
  printf("\n");
  if (TempTree != NULL)
     BSTV_Print2(TempTree->variables, "", 'X');
  else
     printf("%s: strom proměnných je prázdný\n", TempTree->key);
  printf("\n");
  printf("=================================================\n");
}
