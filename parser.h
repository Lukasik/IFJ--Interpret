#ifndef H_PARSER
#define H_PARSER 1
#define NONTERMINALBORDER 100
#define PRECEDENCEBORDER 200

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "stack.h"
#include "structs.h"
#include "scanner.h"
#include "error.h"
#include "ial.h"
#include "garbage.h"
#include "debug.h"
#include "generator.h"

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

int itFunction (FILE *f, tToken *t);
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
int itFunctionCall(FILE *f, tToken *t);


//funkce pravidel
void argumentString(sInteger **s, tToken *t);
void argumentInteger(sInteger **s, tToken *t);
void argumentVar(sInteger **s, tToken *t);
void argumentNull(sInteger **s, tToken *t);
void argumentBoolean(sInteger **s, tToken *t);
void argumentDouble(sInteger **s, tToken *t);
void semicolon(sInteger **s, tToken *t);
void closebrace(sInteger **s, tToken *t);
void closeparen(sInteger **s, tToken *t);
void argumentList(sInteger **s, tToken *t);
void argumentArgumentList1(sInteger **s, tToken *t);
void argumentArgumentList2(sInteger **s, tToken *t);
void block(sInteger **s, tToken *t);
void commandVar(sInteger **s, tToken *t);
void commandReturn(sInteger **s, tToken *t);
void commandIf(sInteger **s, tToken *t);
void commandWhile(sInteger **s, tToken *t);
void commandList(sInteger **s, tToken *t);
void function(sInteger **s, tToken *t);
void functionCall(sInteger **s, tToken *t);
void expressionSemicolon(sInteger **s, tToken *t);
void argumentArgumentList1(sInteger **s, tToken *t);
void paramList1(sInteger **s, tToken *t);
void paramList2(sInteger **s, tToken *t);
void program(sInteger **s, tToken *t);
void returnExpression(sInteger **s, tToken *t);
void statement(sInteger **s, tToken *t);
void statementFunction(sInteger **s, tToken *t);
void statementCommand(sInteger **s, tToken *t);
void statementEnd(sInteger **s, tToken *t);
void expression(sInteger **s, tToken *t);
void expressionParen(sInteger **s, tToken *t);

void reduce(sInteger **s,sInteger **tmpStack, sVariable **stackVar);
void shift(sInteger **s, sInteger **tmpStack, tToken *t);
void equalsign(sInteger **s, sInteger **tmpStack,tToken *t);

tVariable * generateLiteral(tToken *t);

tFunction * actualFunction[2];
tFunction * functionTree;
sVariable * stackVariables;
sFunction * stackFunctions;
extern FILE* f;
extern int precedenceTable[][15];
extern int LLTable[][36];
extern LLFunction *LLRule[];



#endif

