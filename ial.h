/* Struktura uzlu binárního stromu */

#ifndef H_IAL
#define H_IAL 1

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"
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


char * IAL_sort_string(char * str);
int IAL_find_string(char * str, char * substr);

#endif
