#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum tTokens
{
	BEGIN,
	END,

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
	BOOL,
	VAR,

	SEMICOLON,
	DOT,
	COMMA,
	OPENPAREN,
	CLOSEPAREN,
	OPENBRACE,
	CLOSEBRACE,

	WHILE,
	IF,

	INVALIDCHAR,
};

int getToken(FILE *f, char **content);
