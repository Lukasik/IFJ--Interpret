#ifndef H_PARSER
#define H_PARSER 1
#define NONTERMINALBORDER 100
#define PRECEDENCEBORDER 200

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

typedef struct tStack
{
	int top;
	int max;
	int *data;
} tStack;

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
	E, // E pro precedenční analýzu
};

enum precedenceValues
{
	NOTHING = 200,
	REDUCE,
	SHIFT,
	EQUALSIGN
};

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
void argumentString(tStack *s, tToken *t);
void argumentInteger(tStack *s, tToken *t);
void argumentVar(tStack *s, tToken *t);
void argumentNull(tStack *s, tToken *t);
void argumentBoolean(tStack *s, tToken *t);
void argumentDouble(tStack *s, tToken *t);
void semicolon(tStack *s, tToken *t);
void closebrace(tStack *s, tToken *t);
void closeparen(tStack *s, tToken *t);
void argumentList(tStack *s, tToken *t);
void argumentArgumentList1(tStack *s, tToken *t);
void argumentArgumentList2(tStack *s, tToken *t);
void block(tStack *s, tToken *t);
void commandVar(tStack *s, tToken *t);
void commandReturn(tStack *s, tToken *t);
void commandIf(tStack *s, tToken *t);
void commandWhile(tStack *s, tToken *t);
void commandList(tStack *s, tToken *t);
void function(tStack *s, tToken *t);
void functionCall(tStack *s, tToken *t);
void expressionSemicolon(tStack *s, tToken *t);
void argumentArgumentList1(tStack *s, tToken *t);
void paramList1(tStack *s, tToken *t);
void paramList2(tStack *s, tToken *t);
void program(tStack *s, tToken *t);
void returnEnd(tStack *s, tToken *t);
void returnExpression(tStack *s, tToken *t);
void statement(tStack *s, tToken *t);
void statementFunction(tStack *s, tToken *t);
void statementCommand(tStack *s, tToken *t);
void statementEnd(tStack *s, tToken *t);
void expression(tStack *s, tToken *t);

void stackInit(tStack *s, int size);
int stackPop(tStack *s);
void stackPush(tStack *s, int data);
int stackTop(tStack *s);
int stackTopTerminal(tStack *s, tStack *tmpStack, bool useTmpStack);
int stackEmpty(tStack *s);
void printStack(tStack *s);

void reduce(tStack *s,tStack *tmpStack);
void shift(tStack *s, tStack *tmpStack, tToken *t);
void equalsign(tStack *s, tStack *tmpStack,tToken *t);

#define SHOW_DEBUG

#ifndef SHOW_DEBUG
	#define DEBUG(message);
#else
	#define DEBUG(message) printf("%s: %s\n", __PRETTY_FUNCTION__, message);
#endif

sFunction * actualFunction[2];
sFunction * functionTree;
extern FILE* f;

typedef void (LLFunction)(tStack *, tToken*);

int precedenceTable[][15] =
{
	{REDUCE,REDUCE,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{REDUCE,REDUCE,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{REDUCE,REDUCE,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,EQUALSIGN,SHIFT,NOTHING},
	{REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,NOTHING,REDUCE,NOTHING,REDUCE},
	{REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,NOTHING,REDUCE,NOTHING,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,NOTHING,SHIFT,NOTHING}
};

LLFunction *LLRule[] =
{
	NULL,
	argumentString,
	argumentInteger,
	argumentVar,
	argumentNull,
	argumentBoolean,
	argumentDouble,
	argumentList,
	argumentArgumentList1,
	argumentArgumentList2,
	argumentList,
	block,
	semicolon,
	commandVar,
	commandReturn,
	commandIf,
	commandWhile,
	closebrace,
	commandList,
	function,
	functionCall,
	expressionSemicolon,
	closeparen,
	paramList1,
	closeparen,
	paramList2,
	program,
	returnEnd,
	returnExpression,
	statementCommand,
	statementFunction,
	statementEnd,
	expression
};

/* @var tabulka která vrací pravidlo, to se použije pro indexaci funkcí LL tabulky */
int LLTable[][36] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,5,2,6,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,13,0,0,0,0,0,16,14,15,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,0,18,0,0,0,0,0,18,18,18,0,0,0,0,0,17,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,21,0,0,0,20,21,21,21,21,21,21,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,22,0,0,0,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,26,0},
	{0,0,0,0,0,0,0,0,0,0,0,28,0,0,27,0,28,28,28,28,28,28,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,29,0,29,0,0,0,0,0,29,29,29,0,30,0,0,0,0,0,0,0,31},
	{0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,0,32,32,32,32,32,32,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

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
};

#endif

//TODO projít fce a podívat co vbude lepší zapsat jako makra
