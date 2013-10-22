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


	[INVALIDCHAR] = "INVALIDCHAR"
};

int main (int argc, char * argv[])
{
	if(argc != 2) exit(1);
	FILE *f=fopen(argv[1],"rw");

	tToken *t = malloc(sizeof(tToken));
	t->content = malloc(40);

	while ((getToken(f,t) && t->name != END))
	{
		printf ("%s",tokenNames[t->name]);

		if(*(t->content)!='\0') {
			printf("[%s]", t->content);
			*(t->content) = '\0';
		}
		printf("\n");
	}

	printf("%s\n", tokenNames[t->name]);

	return 0;
}
