#ifndef H_STRUCTS
#define H_STRUCTS
#include <stdbool.h>

typedef struct tToken
{
	int name;
	char *content;
} tToken;


typedef struct tStack
{
	int top;
	int max;
	int *data;
} tStack;

typedef struct gPointer
{
	void * pointer;
	void (*f)(void *);
} gPointer;

typedef union variableValue
{
	int intv;
	double doublev;
	char *stringv;
	bool boolv;
} variableValue;


typedef struct sVariable
{
	bool defined;
	char *key;
	unsigned type;
	variableValue *value;
	struct sVariable * lptr;
	struct sVariable * rptr;
} sVariable;

typedef void (instructionFunction) (char *, char *);

typedef struct tInstruction
{
	instructionFunction *f;
	char *variable;
	int destination;
	char *functionName; //název volané funkce
} tInstruction;

typedef struct tStackInstruction
{
	int top;
	int max;
	tInstruction **data;
} tStackInstruction;

typedef struct tStackString
{
	int top;
	int max;
	char **data;
} tStackString;

typedef struct sFunction
{
	struct sVariable * variables;
	bool defined;
	tStackInstruction *code;
	unsigned codePosition;
	char *key;
	tStackString *paramNames;
	struct sFunction * lptr;
	struct sFunction * rptr;
} sFunction;

typedef struct tStackVar
{
	int top;
	int max;
	sVariable **data;
} tStackVar;

typedef struct tStackFunc
{
	int top;
	int max;
	sFunction **data;
} tStackFunc;

typedef struct tIf
{
	int type;
	int *destination;
} tIf;

typedef struct tStackIf
{
	int top;
	int max;
	int counter;
	tIf **data;
} tStackIf;

typedef void (LLFunction)(tStack **, tToken*);



#endif
