#include "stack.h"

void stackInit(tStack *s, int size)
{
	s->top = -1;
	s->max = size;
	s->data = gmalloc(sizeof(int)*size, free);

	if(s->data == NULL)
	{
		DEBUG("init");
		printError(ALLOCERROR,INTERPRETERROR);
	}
}

int stackPop(tStack **s)
{
	if((*s)->top == -1)
	{
		DEBUG("pop");
		printError(STACKERROR, INTERPRETERROR);
	}
		// printStack(*s);

	return (*s)->data[(*s)->top--];
}

void stackPush(tStack **s, int data)
{
	if((*s)->top == (*s)->max-1)
	{
		// DEBUG("Před realokací:");
		// printf("velikost %d\n", (*s)->max);
		// printStack(*s);
		grealloc((void **) &((*s)->data), &((*s)->max), sizeof(int));
		// DEBUG("PO realokaci:");
		// printf("velikost %d\n", (*s)->max);
		// printStack(*s);
		// DEBUG("push");
		// printError(STACKERROR, INTERPRETERROR);
	}
		// printStack(*s);

	(*s)->data[++((*s)->top)] = data;
}

int stackTop(tStack **s)
{
	if((*s)->top == -1)
	{
		DEBUG("top");
		printError(STACKERROR, INTERPRETERROR);
	}

	return (*s)->data[(*s)->top];
}

int stackTopTerminal(tStack **s, tStack **tmpStack, bool useTmpStack)
{
	for(int i = (*s)->top; i > -1; --i)
	{
		// DEBUG(tokenNames[s->data[i]]);
		if((*s)->data[i] < NONTERMINALBORDER || (*s)->data[i] >= PRECEDENCEBORDER) return (*s)->data[i];
		if(useTmpStack) stackPush(tmpStack, stackPop(s));
	}

	DEBUG("nenašel terminál v zásobníku");
	printError(SYNTAXERR, SYNTAXERROR);
	return 0;
}


int stackEmpty(tStack *s)
{
	return s->top == -1;
}

void printStack(tStack *s)
{
	int i = 0;

	while(s->top - i >= 0) printf("%s ", tokenNames[s->data[i++]]);
	printf("\n");
}

void stackVarInit(tStackVar *s, int size)
{
	s->top = -1;
	s->max = size;
	s->data = gmalloc(sizeof(sVariable*)*size, free);

	if(s->data == NULL)
	{
		DEBUG("init");
		printError(ALLOCERROR,INTERPRETERROR);
	}
}

sVariable * stackVarPop(tStackVar **s)
{
	if((*s)->top == -1)
	{
		DEBUG("pop");
		printError(STACKERROR, INTERPRETERROR);
	}
		// printStack(*s);

	return (*s)->data[(*s)->top--];
}

void stackVarPush(tStackVar **s, sVariable * data)
{
	if((*s)->top == (*s)->max-1)
	{
		// DEBUG("Před realokací:");
		// printf("velikost %d\n", (*s)->max);
		// printStack(*s);
		grealloc((void **) &((*s)->data), &((*s)->max), sizeof(sVariable*));
		// DEBUG("PO realokaci:");
		// printf("velikost %d\n", (*s)->max);
		// printStack(*s);
		// DEBUG("push");
		// printError(STACKERROR, INTERPRETERROR);
	}
		// printStack(*s);

	(*s)->data[++((*s)->top)] = data;
}

int stackVarEmpty(tStackVar *s)
{
	return s->top == -1;
}

void stackFuncInit(tStackFunc *s, int size)
{
	s->top = -1;
	s->max = size;
	s->data = gmalloc(sizeof(sFunction)*size, free);

	if(s->data == NULL)
	{
		DEBUG("init");
		printError(ALLOCERROR,INTERPRETERROR);
	}
}

sFunction * stackFuncPop(tStackFunc **s)
{
	if((*s)->top == -1)
	{
		DEBUG("pop");
		printError(STACKERROR, INTERPRETERROR);
	}
		// printStack(*s);

	return (*s)->data[(*s)->top--];
}

void stackFuncPush(tStackFunc **s, sFunction * data)
{
	if((*s)->top == (*s)->max-1)
	{
		// DEBUG("Před realokací:");
		// printf("velikost %d\n", (*s)->max);
		// printStack(*s);
		grealloc((void **) s, &((*s)->max), sizeof(int));
		// DEBUG("PO realokaci:");
		// printf("velikost %d\n", (*s)->max);
		// printStack(*s);
		// DEBUG("push");
		// printError(STACKERROR, INTERPRETERROR);
	}
		// printStack(*s);

	(*s)->data[++((*s)->top)] = data;
}

sFunction * stackFuncTop(tStackFunc **s)
{
	if ((*s)->top==-1) printError(STACKERROR,INTERPRETERROR);
	return (*s)->data[(*s)->top];
}

int stackFuncEmpty(tStackFunc *s)
{
	return s->top == -1;
}

