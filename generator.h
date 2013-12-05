#ifndef H_GENERATOR
#define H_GENERATOR 1

#include "ial.h"
#include "scanner.h"
#include "stack.h"
#include "structs.h"
#include "debug.h"
#include "inbuilt_functions.h"


extern tFunction * functionTree;

void duplicateFunction (tFunction *f);
bool isInt (tVariable *var);
bool isDouble (tVariable *var);
bool twoInts (tVariable *par1,tVariable *par2);
bool twoDoubles (tVariable *par1,tVariable *par2);
bool intDouble (tVariable *par1,tVariable *par2);
bool doubleInt (tVariable *par1,tVariable *par2);
void add (char * param, char * function);
void sub (char * param, char * function);
void mul (char * param, char * function);
void division(char * param, char * function);
void concatenate (char * param, char * function);
void equal (char * param, char * function);
void notEqual (char * param, char * function);
void bigger (char * param, char * function);
void lesser (char * param, char * function);
void lesserEqual (char * param, char * function);
void biggerEqual (char * param, char * function);
void iFunctionCall (char * param, char * function);
void pushSVar(char * param, char * function);
void iReturn (char * param, char * function);
void assign (char * param, char * function);
void jmpFalse (char * param, char * function);
void jmp(char * param, char * function);
void generateInstruction(instructionFunction *f, char *var, char * name);

int maxChars(int num);
void interpret(void);

#endif
