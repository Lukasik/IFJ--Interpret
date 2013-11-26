#ifndef H_GENERATOR
#define H_GENERATOR 1

#include "ial.h"
#include "scanner.h"


extern sFunction * functionTree;

void duplicateFunction (sFunction *f);
bool isInt (sVariable *var);
bool isDouble (sVariable *var);
bool twoInts (sVariable *par1,sVariable *par2);
bool twoDoubles (sVariable *par1,sVariable *par2);
bool intDouble (sVariable *par1,sVariable *par2);
bool doubleInt (sVariable *par1,sVariable *par2);
void add (sVariable * param, char * function);
void sub (sVariable * param, char * function);
void mul (sVariable * param, char * function);
void division(sVariable * param, char * function);
void concatenate (sVariable * param, char * function);
void equal (sVariable * param, char * function);
void notEqual (sVariable * param, char * function);
void bigger (sVariable * param, char * function);
void lesser (sVariable * param, char * function);
void lesserEqual (sVariable * param, char * function);
void biggerEqual (sVariable * param, char * function);
void iFunctionCall (sVariable * param, char * function);
void pushSVar(sVariable * param, char * function);
void iReturn (sVariable * param, char * function);
void assign (sVariable * param, char * function);
void jmpIfFalseIF (sVariable * param, char * function);
void jmpIfFalseWHILE (sVariable * param, char * function);
void jmpIF (sVariable * param, char * function);
void jmpWHILE (sVariable * param, char * function);
void generateInstruction(instructionFunction *f, sVariable *var, char * name);

#endif
