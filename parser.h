#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "error.h"

// enum pro navraty z funkce v parser.c
enum tret 
{
	SYNERR=0,
	ISNT=1,
	ISOK=2,
};


int isFunction (FILE *f, tToken *t);
int isBlock(FILE *f, tToken *t);
int isCommand(FILE *f, tToken *t);
int isWhile(FILE *f, tToken *t);
int isIf(FILE *f,tToken *t);
int isExpression (FILE *f, tToken *t);
int isAssign (FILE *f, tToken *t);
int isReturn (FILE *f, tToken *t);


