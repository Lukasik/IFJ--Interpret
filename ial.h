/* Struktura uzlu binárního stromu */

#ifndef H_IAL
#define H_IAL 1

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
	variableValue value;
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

#include "garbage.h"
#include "stack.h"
#include "debug.h"




/* Prototypy funkcí */
void BSTF_Init(sFunction ** node);
sFunction* BSTF_Search(sFunction * node, char * key);
sFunction* BSTF_Insert(sFunction ** node, char * key);
void BSTF_Dispose(void * node);

void BSTV_Init(sVariable ** node);
sVariable* BSTV_Search(sVariable * node, char * key);
sVariable* BSTV_Insert(sVariable ** node, char * key);
void BSTV_Dispose(void * node);


char * sort_string(char * str);
int find_string(char * str, char * substr);

#endif
