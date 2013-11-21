#ifndef H_DEBUG
#define H_DEBUG

#include "structs.h"
#include "scanner.h"
#include "stack.h"
#include "parser.h"
#include "ial.h"

extern char* tokenNames[];

void printStack(tStack *s);
void BSTF_Print(sFunction* TempTree);
void BSTF_Print2(sFunction* TempTree, char* sufix, char fromdir);
void BSTV_Print(sFunction * TempTree);
void BSTV_Print2(sVariable* TempTree, char* sufix, char fromdir);

#define DEBUG(message) printf("%s: %s\n", __PRETTY_FUNCTION__, message);


#endif
