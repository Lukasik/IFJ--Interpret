#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

enum tTokenNames
{
	BEGIN,
	END,

	KEYWORD,

	PLUS,
	MINUS,
	TIMES,
	DIVISION,

	BIGGER,
	LESSER,
	BIGGEREQUAL,
	LESSEREQUAL,
	EQUAL,
	NOTEQUAL,
	ASSIGN,

	ID,
	INT,
	DOUBLE,
	STRING,
	VAR,

	SEMICOLON,
	DOT,
	COMMA,
	OPENPAREN,
	CLOSEPAREN,
	OPENBRACE,
	CLOSEBRACE,

	INVALIDCHAR,
	UNINITIALIZED,
};

typedef struct tToken
{
	unsigned name;
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


