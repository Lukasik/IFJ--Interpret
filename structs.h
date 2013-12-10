#ifndef H_STRUCTS
#define H_STRUCTS
#include <stdbool.h>

typedef struct tToken
{
	int name;
	char *content;
} tToken;


typedef struct sInteger
{
	int top;
	int max;
	int *data;
} sInteger;

typedef struct gPointer
{
	void * pointer;
	void (*f)(void *);
} gPointer;

typedef union tVariableValue
{
	int intv;
	double doublev;
	char *stringv;
	bool boolv;
} tVariableValue;


typedef struct tVariable
{
	bool defined;
	char *key;
	unsigned type;
	tVariableValue *value;
	struct tVariable * lptr;
	struct tVariable * rptr;
	bool usable;
} tVariable;

typedef void (instructionFunction) (char *, char *);

typedef struct tInstruction
{
	instructionFunction *f;
	char *variable;
	int destination;
	char *functionName; //název volané funkce
} tInstruction;

typedef struct sInstruction
{
	int top;
	int max;
	tInstruction **data;
} sInstruction;

typedef struct sString
{
	int top;
	int max;
	char **data;
} sString;

typedef void (inbuiltFunction)(void);

typedef struct tFunction
{
	struct tVariable * variables;
	bool defined;
	sInstruction *code;
	unsigned codePosition;
	char *key;
	sString *paramNames;
	inbuiltFunction * function;
	struct tFunction * lptr;
	struct tFunction * rptr;
} tFunction;

typedef struct sVariable
{
	int top;
	int max;
	tVariable **data;
} sVariable;

typedef struct sFunction
{
	int top;
	int max;
	tFunction **data;
} sFunction;

typedef struct tIf
{
	int type;
	int *destination;
} tIf;

typedef struct sIf
{
	int top;
	int max;
	int counter;
	tIf **data;
} sIf;

typedef void (LLFunction)(sInteger **, tToken*);



#endif
