#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum tTokens
{
	BEGIN,
	END,

	KEYWORD,
	BOOL,
	NULLV,

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
	TYPEEQUAL,
	TYPENOTEQUAL,

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
};


void insertChar(int *index, char **content, int c);
int getToken(FILE *f, char **content);
int is_paren_brace(int c);
int isDotSmcComma(int c);
int isArithmetic (int c);
int isEquating (FILE *f, int c);
int reallocation (char **str);
int comments_and_whtspc(FILE *f);
int isNotEqual(FILE *f,int c);
int isBigger(FILE *f, int c);
int is_begin_or_lesser(FILE *f, int c);
int isVariable(FILE *f,int c, char **content);
int isString (FILE *f, int c, char **content);
int isKeyWord(char *str);


