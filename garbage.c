#include "garbage.h"

int gArraySize = 1000;
int gArrayIndex = 0;

void ginit()
{
	gArray = (gPointer **) malloc(sizeof(gPointer*)*gArraySize);

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

	if(gArraySize == gArrayIndex)
	{

		gArraySize *= 2;

		gPointer ** gArrayNew = (gPointer **) realloc(gArray, sizeof(gPointer*)*gArraySize);

		if(gArrayNew == NULL)
		{
			printError(ALLOCERROR, INTERPRETERROR);
		}

		gArray = gArrayNew;

		for (int i = gArraySize/2; i < gArraySize; ++i)
		{
			gArray[i] = NULL;
		}

		gadd(pointer, f);
	}
	else
	{
		gArray[gArrayIndex] = (gPointer *) malloc(sizeof(gPointer));
		gArray[gArrayIndex]->pointer = pointer;
		gArray[gArrayIndex++]->f = f;
	}

	return pointer;
}

void grealloc(void **pointer, int* size, int elementSize)
{
	*size += 20;

	void *new = realloc(*pointer, (*size)*elementSize);

	if (new == NULL)
	{
		printError(ALLOCERROR,INTERPRETERROR);
	}

	if(*pointer != new)
	{
		for(int i = 0; i < gArraySize; ++i)
		{
			if(gArray[i] != NULL && gArray[i]->pointer == *pointer)
			{
				gArray[i]->pointer = new;
			}
		}

		*pointer = new;
	}

	return;
}

void gadd(void * pointer, void (*f)(void *))
{
	// for(int i = 0; i < gArraySize; ++i)
	// {
	// 	if(gArray[i] == NULL)
	// 	{
	// 		gArray[i] = (gPointer *) malloc(sizeof(gPointer));

	// 		if(gArray[i] == NULL)
	// 		{
	// 			printError(ALLOCERROR, INTERPRETERROR);
	// 		}

	// 		gArray[i]->pointer = pointer;
	// 		gArray[i]->f = f;
	// 		return;
	// 	}
	// }

	if(gArraySize == gArrayIndex)
	{

		gArraySize *= 2;

		gPointer ** gArrayNew = (gPointer **) realloc(gArray, sizeof(gPointer*)*gArraySize);

		if(gArrayNew == NULL)
		{
			printError(ALLOCERROR, INTERPRETERROR);
		}

		gArray = gArrayNew;

		for (int i = gArraySize/2; i < gArraySize; ++i)
		{
			gArray[i] = NULL;
		}

		gadd(pointer, f);
	}
	else
	{
		gArray[gArrayIndex] = (gPointer *) malloc(sizeof(gPointer));
		gArray[gArrayIndex]->pointer = pointer;
		gArray[gArrayIndex++]->f = f;
	}
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
}
