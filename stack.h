#ifndef H_STACK
#define H_STACK

typedef struct tStack
{
	int top;
	int max;
	int *data;
} tStack;


#include "debug.h"


void stackInit(tStack *s, int size);
int stackPop(tStack **s);
void stackPush(tStack **s, int data);
int stackTop(tStack **s);
int stackTopTerminal(tStack **s, tStack **tmpStack, bool useTmpStack);
int stackEmpty(tStack *s);
// void printStack(tStack *s);
// void printStack(tStack *s);


#endif
