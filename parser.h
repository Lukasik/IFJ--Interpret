#ifndef H_PARSER
#define H_PARSER 1
#define NONTERMINALBORDER 100
#define PRECEDENCEBORDER 200

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "structs.h"
#include "scanner.h"
#include "error.h"
#include "ial.h"
#include "garbage.h"
#include "debug.h"
#include "stack.h"

// enum pro navraty z funkce v parser.c
enum tret
{
	SYNERR=0,
	ISNT=1,
	ISOK=2,
};

enum nonTerminals
{
	NARGUMENT = 100,
	NARGUMENTLIST1,
	NARGUMENTLIST2,
	NBLOCK,
	NCOMMAND,
	NCOMMANDLIST,
	NFUNCTION,
	NFUNCTIONCALLEXPRESSION,
	NPARAMLIST1,
	NPARAMLIST2,
	NPROGRAM,
	NRETURN,
	NSTATEMENT,
	NEXPRESSION,
	NEXPRESSIONPAREN,
	E, // E pro precedenční analýzu
};

enum precedenceValues
{
	NOTHING = 200,
	REDUCE,
	SHIFT,
	EQUALSIGN,
	FINISH,
};

int intMaxChars();

int isFunction (FILE *f, tToken *t);
int isBlock(FILE *f, tToken *t);
int isCommand(FILE *f, tToken *t);
int isWhile(FILE *f, tToken *t);
int isIf(FILE *f,tToken *t);
int isExpression (FILE *f, tToken *t, bool semicolonEnd);
int isAssign (FILE *f, tToken *t);
int isReturn (FILE *f, tToken *t);
int isOperator(int tokenName);
int isOperand(int tokenName);
int isType(tToken *token);
int isComparsionOperator(tToken *token);
int isWhile(FILE *f, tToken *t);
int doOperation(FILE *f, tToken *t, int *parens, bool semicolonEnd);
int isComparsion(FILE *f, tToken *t);
int isFunctionCall(FILE *f, tToken *t);


//funkce pravidel
void argumentString(tStack **s, tToken *t);
void argumentInteger(tStack **s, tToken *t);
void argumentVar(tStack **s, tToken *t);
void argumentNull(tStack **s, tToken *t);
void argumentBoolean(tStack **s, tToken *t);
void argumentDouble(tStack **s, tToken *t);
void semicolon(tStack **s, tToken *t);
void closebrace(tStack **s, tToken *t);
void closeparen(tStack **s, tToken *t);
void argumentList(tStack **s, tToken *t);
void argumentArgumentList1(tStack **s, tToken *t);
void argumentArgumentList2(tStack **s, tToken *t);
void block(tStack **s, tToken *t);
void commandVar(tStack **s, tToken *t);
void commandReturn(tStack **s, tToken *t);
void commandIf(tStack **s, tToken *t);
void commandWhile(tStack **s, tToken *t);
void commandList(tStack **s, tToken *t);
void function(tStack **s, tToken *t);
void functionCall(tStack **s, tToken *t);
void expressionSemicolon(tStack **s, tToken *t);
void argumentArgumentList1(tStack **s, tToken *t);
void paramList1(tStack **s, tToken *t);
void paramList2(tStack **s, tToken *t);
void program(tStack **s, tToken *t);
void returnEnd(tStack **s, tToken *t);
void returnExpression(tStack **s, tToken *t);
void statement(tStack **s, tToken *t);
void statementFunction(tStack **s, tToken *t);
void statementCommand(tStack **s, tToken *t);
void statementEnd(tStack **s, tToken *t);
void expression(tStack **s, tToken *t);
void expressionParen(tStack **s, tToken *t);

void reduce(tStack **s,tStack **tmpStack);
void shift(tStack **s, tStack **tmpStack, tToken *t);
void equalsign(tStack **s, tStack **tmpStack,tToken *t);

char * escapeSequences(char * str);
void shiftString(char * str, unsigned index, unsigned n);

sFunction * actualFunction[2];
sFunction * functionTree;
tStackVar * stackVariables;
tStackFunc * stackFunctions;
extern FILE* f;
extern int precedenceTable[][15];
extern int LLTable[][36];
extern LLFunction *LLRule[];



#endif

//TODO projít fce a podívat co vbude lepší zapsat jako makra
