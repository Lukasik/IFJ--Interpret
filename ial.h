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
void BSTF_Init(tFunction ** node);
tFunction* BSTF_Search(tFunction * node, char * key);
tFunction* BSTF_Insert(tFunction ** node, char * key);
void BSTF_Dispose(void * node);

void BSTV_Init(tVariable ** node);
tVariable* BSTV_Search(tVariable * node, char * key);
tVariable* BSTV_Insert(tVariable ** node, char * key);
void BSTV_Dispose(void * node);


char * IAL_sort_string(char * str);
int IAL_find_string(char * str, char * substr);

#endif
