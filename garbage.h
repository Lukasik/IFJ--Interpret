#ifndef H_GARBAGE
#define H_GARBAGE 1

#include <stdlib.h>
#include "error.h"

typedef struct gPointer
{
	void * pointer;
	void (*f)(void *);
} gPointer;

gPointer ** gArray;
extern int gArraySize;

void * gmalloc(unsigned bytes, void (*f)(void *));
void gadd(void * pointer, void (*f)(void *));
void gfree(void * pointer);
void gfreeAll();
void ginit();

#endif
