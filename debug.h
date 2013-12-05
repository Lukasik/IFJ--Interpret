#ifndef H_DEBUG
#define H_DEBUG

#include "structs.h"
#include "scanner.h"
#include "stack.h"
#include "parser.h"
#include "ial.h"

extern char* tokenNames[];

void prinsInteger(sInteger *s);
void BSTF_Print(tFunction* TempTree);
void BSTF_Print2(tFunction* TempTree, char* sufix, char fromdir);
void BSTV_Print(tFunction * TempTree);
void BSTV_Print2(tVariable* TempTree, char* sufix, char fromdir);

#define DEBUG(message) printf("%s: %s\n", __PRETTY_FUNCTION__, message);


#endif
