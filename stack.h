#ifndef H_STACK
#define H_STACK

#include "structs.h"
#include "debug.h"


void stackInit(tStack *s, int size);
int stackPop(tStack **s);
void stackPush(tStack **s, int data);
int stackTop(tStack **s);
int stackTopTerminal(tStack **s, tStack **tmpStack, bool useTmpStack);
int stackEmpty(tStack *s);
// void printStack(tStack *s);
// void printStack(tStack *s);
void stackVarInit(tStackVar *s, int size);
sVariable * stackVarPop(tStackVar **s);
void stackVarPush(tStackVar **s, sVariable* data);
// int stackTop(tStack **s);
// int stackTopTerminal(tStack **s, tStack **tmpStack, bool useTmpStack);
int stackVarEmpty(tStackVar *s);
int stackFuncEmpty(tStackFunc *s);
void stackFuncPush(tStackFunc **s, sFunction * data);
sFunction * stackFuncPop(tStackFunc **s);
int stackFuncEmpty(tStackFunc *s);
void stackFuncPush(tStackFunc **s, sFunction * data);
sFunction * stackFuncPop(tStackFunc **s);
sFunction * stackFuncTop(tStackFunc **s);
void stackFuncInit(tStackFunc *s, int size);


#endif
