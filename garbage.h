#ifndef H_GARBAGE
#define H_GARBAGE 1

#include <stdlib.h>
#include <string.h>
#include "error.h"

typedef struct gPointer
{
	void * pointer;
	void (*f)(void *);
} gPointer;

gPointer ** gArray;
extern int gArraySize;

void * gmalloc(unsigned bytes, void (*f)(void *));
void grealloc(void **pointer, int* size, int elementSize);
void gadd(void * pointer, void (*f)(void *));
void gfree(void * pointer);
void gfreeAll();
void ginit();

#endif
