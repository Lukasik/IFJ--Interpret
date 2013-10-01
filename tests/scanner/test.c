#include "../../scanner.h"
#include "../../error.h"

char* tokenNames[] = {
	[BEGIN] = "BEGIN",
	[END] = "END",

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
	[INT] = "INT",
	[DOUBLE] = "DOUBLE",
	[STRING] = "STRING",
	[VAR] = "VAR",

	[SEMICOLON] = "SEMICOLON",
	[DOT] = "DOT",
	[COMMA] = "COMMA",
	[OPENPAREN] = "OPENPAREN",
	[CLOSEPAREN] = "CLOSEPAREN",
	[OPENBRACE] = "OPENBRACE",
	[CLOSEBRACE] = "CLOSEBRACE",

	[KEYWORD] = "KEYWORD",
	[BOOL] = "BOOL",
	[NULLV] = "NULLV",


	[INVALIDCHAR] = "INVALIDCHAR"
};

int main (int argc, char * argv[])
{
	if(argc != 2) exit(1);
	FILE *f=fopen(argv[1],"rw");

	int token;
	char *content=malloc(40);

	while ((token=getToken(f,&content))!=END)
	{
		printf ("%s",tokenNames[token]);

		if(*content!='\0') {
			printf("[%s]", content);
		}
		printf("\n");
	}

	printf("%s\n", tokenNames[token]);

	return 0;
}
