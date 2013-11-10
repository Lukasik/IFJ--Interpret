#ifndef H_PARSER
#define H_PARSER 1

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "scanner.h"
#include "error.h"
#include "ial.h"
#include "garbage.h"

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
int isExpression (FILE *f, tToken *t, bool semicolonEnd);
int isAssign (FILE *f, tToken *t);
int isReturn (FILE *f, tToken *t);
int isOperator(tToken *token);
int isOperand(tToken *token);
int isType(tToken *token);
int isComparsionOperator(tToken *token);
int isWhile(FILE *f, tToken *t);
int doOperation(FILE *f, tToken *t, int *parens, bool semicolonEnd);
int isComparsion(FILE *f, tToken *t);
int isFunctionCall(FILE *f, tToken *t);

#define SHOW_DEBUG

#ifndef SHOW_DEBUG
	#define DEBUG(message);
#else
	#define DEBUG(message) printf("%s: %s\n", __PRETTY_FUNCTION__, message);
#endif

sFunction * actualFunction[2];
sFunction * functionTree;
extern FILE* f;

#endif
