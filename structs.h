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
	union variableValue *value;
	struct sVariable * lptr;
	struct sVariable * rptr;
} sVariable;

typedef struct sFunction
{
	struct sVariable * variables;
	unsigned *elseBranches;
	unsigned *endIfBranches;
	unsigned ifSize; //TODO
	unsigned *whileBranches;
	unsigned whileSize; //TODO
	void *code;
	int codeSize; //TODO
	char *key;
	char **paramNames;
	int paramCount;
	struct sFunction * lptr;
	struct sFunction * rptr;
} sFunction;

typedef struct tStackVar
{
	int top;
	int max;
	sVariable **data;
} tStackVar;

typedef void (LLFunction)(tStack **, tToken*);

#endif
