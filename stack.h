#ifndef H_STACK
#define H_STACK

#include "structs.h"
#include "debug.h"


void stackInit(sInteger *s, int size);
int stackPop(sInteger **s);
void stackPush(sInteger **s, int data);
int stackTop(sInteger **s);
int stackTopTerminal(sInteger **s, sInteger **tmpStack, bool useTmpStack);
int stackEmpty(sInteger *s);
void prinsInteger(sInteger *s);
void stackVarInit(sVariable *s, int size);
tVariable * stackVarPop(sVariable **s);
void stackVarPush(sVariable **s, tVariable * data);
tVariable * stackVarTopUsable(sVariable **s);
int stackVarEmpty(sVariable *s);
void stackFuncInit(sFunction *s, int size);
tFunction * stackFuncPop(sFunction **s);
void stackFuncPush(sFunction **s, tFunction * data);
tFunction * stackFuncTop(sFunction **s);
int stackFuncEmpty(sFunction *s);
void stackInstructionInit(sInstruction *s, int size);
tInstruction * stackInstructionPop(sInstruction **s);
tInstruction * stackInstructionTop(sInstruction **s);
void stackInstructionPush(sInstruction **s, tInstruction* data);
int stackInstructionEmpty(sInstruction *s);
void printInstructionStack(sInstruction *s);
void stackStringInit(sString *s, int size);
void stackStringPush(sString **s, char* data);
void stackIfInit(sIf *s, int size);
void stackIfPop(sIf **s);
void stackIfPush(sIf **s, int type, int *destination);
int * stackIfTop(sIf **s);


#endif
