#ifndef H_SCANNER
#define H_SCANNER 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "error.h"
#include "garbage.h"

extern FILE* f;


enum tTokenNames
{
	PLUS,
	MINUS,
	TIMES,
	DIVISION,
	DOT,
	BIGGER,
	LESSER,
	BIGGEREQUAL,
	LESSEREQUAL,
	EQUAL,
	NOTEQUAL,
	OPENPAREN,
	CLOSEPAREN,
	VALUE,
	SEMICOLON,
	ID,
	VAR,

	BOOLEAN,
	INTEGER,
	DOUBLE,
	STRING,
	NULLV,

	WHILE,
	RETURN,
	IF,
	ELSE,
	FUNCTION,

	ASSIGN,
	COMMA,
	OPENBRACE,
	CLOSEBRACE,
	INVALIDCHAR,

	UNINITIALIZED,
	BEGIN,
	END,
};

typedef struct tToken
{
	int name;
	char *content;
} tToken;

void getToken(FILE *f, tToken *t);
bool findToken(FILE *f, tToken *t);
void insertChar(int *index, char **content, int c);
int isParenBrace(int c);
int isDotSmcComma(int c);
int isArithmetic (int c);
int isEquating (FILE *f, int c);
int reallocation (char **str);
int CommentsAndWhitespaces(FILE *f);
int isNotEqual(FILE *f,int c);
int isBigger(FILE *f, int c);
int isBeginOrLesser(FILE *f, int c);
int isVariable(FILE *f,int c, char **content);
int isString (FILE *f, int c, char **content);
int isKeyWord(char *str);
bool exponent(int *index, char** content, int c);
int digits(int *index, char** content, int c);

#endif
