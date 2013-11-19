#include "garbage.h"

int gArraySize = 1000;

void ginit()
{
	gArray = (gPointer **) malloc(sizeof(gPointer)*gArraySize);

	if(gArray == NULL)
	{
		printError(ALLOCERROR, INTERPRETERROR);
	}

	for(int i = 0; i < gArraySize; ++i)
	{
		gArray[i] = NULL;
	}
}

void * gmalloc(unsigned bytes, void (*f)(void *))
{
	void * pointer = (gPointer *) malloc(bytes);

	if(pointer == NULL)
	{
		printError(ALLOCERROR, INTERPRETERROR);
	}

	gadd(pointer, f);
	return pointer;
}

void grealloc(void **pointer, int* size, int elementSize)
{
	*size *= 2;

	void *new = gmalloc((*size)*elementSize, free);

	if (new == NULL)
	{
		printError(ALLOCERROR,INTERPRETERROR);
	}

	memcpy(new, *pointer, ((*size)*elementSize)/2);
	gfree(*pointer);

	*pointer = new;
	return;
}

void gadd(void * pointer, void (*f)(void *))
{
	for(int i = 0; i < gArraySize; ++i)
	{
		if(gArray[i] == NULL)
		{
			gArray[i] = (gPointer *) malloc(sizeof(gPointer));

			if(gArray[i] == NULL)
			{
				printError(ALLOCERROR, INTERPRETERROR);
			}

			gArray[i]->pointer = pointer;
			gArray[i]->f = f;
			return;
		}
	}

	gArraySize *= 2;

	gPointer ** gArrayNew = (gPointer **) realloc(gArray, sizeof(gPointer)*gArraySize);

	if(gArrayNew != gArray)
	{
		free(gArray);

	}

	gArray = gArrayNew;

	if(gArray == NULL)
	{
		printError(ALLOCERROR, INTERPRETERROR);
	}

	for (int i = gArraySize/2; i < gArraySize; ++i)
	{
		gArray[i] = NULL;
	}

	gadd(pointer, f);
}


void gfree(void * pointer)
{
	for(int i = 0; i < gArraySize; ++i)
	{
		if(gArray[i] != NULL && gArray[i]->pointer == pointer)
		{
			gArray[i]->f(pointer);
			free(gArray[i]);
			gArray[i] = NULL;
		}
	}
}

void gfreeAll()
{
	for(int i = 0; i < gArraySize; ++i)
	{
		if(gArray[i] == NULL) continue;
		gArray[i]->f(gArray[i]->pointer);
		free(gArray[i]);
	}

	free(gArray);
	gArraySize = 0;
}
