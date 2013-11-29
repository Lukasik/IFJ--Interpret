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

	return (*s)->data[(*s)->top--];
}

void stackPush(tStack **s, int data)
{
	if((*s)->top == (*s)->max-1)
	{
		grealloc((void **) &((*s)->data), &((*s)->max), sizeof(int));
	}

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

	while(s->top - i >= 0) printf("%d ", s->data[i++]);
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

	return (*s)->data[(*s)->top--];
}

void stackVarPush(tStackVar **s, sVariable * data)
{
	if((*s)->top == (*s)->max-1)
	{
		grealloc((void **) &((*s)->data), &((*s)->max), sizeof(sVariable*));
	}

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
		grealloc((void **) s, &((*s)->max), sizeof(int));
	}

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

void stackInstructionInit(tStackInstruction *s, int size)
{
	s->top = -1;
	s->max = size;
	s->data = gmalloc(sizeof(tInstruction)*size, free);

	if(s->data == NULL)
	{
		DEBUG("init");
		printError(ALLOCERROR,INTERPRETERROR);
	}
}

tInstruction * stackInstructionPop(tStackInstruction **s)
{
	if((*s)->top == -1)
	{
		DEBUG("pop");
		printError(STACKERROR, INTERPRETERROR);
	}

	return (*s)->data[(*s)->top--];
}

tInstruction * stackInstructionTop(tStackInstruction **s)
{
	if((*s)->top == -1)
	{
		DEBUG("top");
		printError(STACKERROR, INTERPRETERROR);
	}

	return (*s)->data[(*s)->top];
}

void stackInstructionPush(tStackInstruction **s, tInstruction* data)
{
	if((*s)->top == (*s)->max-1)
	{
		grealloc((void **) &((*s)->data), &((*s)->max), sizeof(tInstruction));
	}

	(*s)->data[++((*s)->top)] = data;
}

int stackInstructionEmpty(tStackInstruction *s)
{
	return s->top == -1;
}

void printInstructionStack(tStackInstruction *s)
{
	int i = 0;
	char *name;

	while(s->top - i >= 0)
	{
		if(s->data[i]->f == pushSVar) name = "push";
		else if(s->data[i]->f == iReturn) name = "return";
		else if(s->data[i]->f == concatenate) name = "concat";
		else if(s->data[i]->f == add) name = "add";
		else if(s->data[i]->f == sub) name = "sub";
		else if(s->data[i]->f == division) name = "division";
		else if(s->data[i]->f == mul) name = "mul";
		else if(s->data[i]->f == assign) name = "assign";
		else if(s->data[i]->f == iFunctionCall) name = "functionCall";
		else if(s->data[i]->f == jmp) name = "jmp";
		else if(s->data[i]->f == jmpFalse) name = "jmpFalse";
		else if(s->data[i]->f == bigger) name = "bigger";
		else if(s->data[i]->f == lesser) name = "lesser";
		else if(s->data[i]->f == biggerEqual) name = "biggerEqual";
		else if(s->data[i]->f == lesserEqual) name = "lesserEqual";
		else if(s->data[i]->f == equal) name = "equal";
		else if(s->data[i]->f == notEqual) name = "notEqual";
		else name = "undefined";

		if(s->data[i]->f == jmp || s->data[i]->f == jmpFalse)
		{
			printf("%d: %s cíl: %d\n", i, name, s->data[i]->destination);
		}
		else
		{
			printf("%d: %s\n", i, name);
		}

		i++;
	}
	printf("\n");
}

void stackStringInit(tStackString *s, int size)
{
	s->top = -1;
	s->max = size;
	s->data = gmalloc(sizeof(char*)*size, free);

	if(s->data == NULL)
	{
		DEBUG("init");
		printError(ALLOCERROR,INTERPRETERROR);
	}
}

void stackStringPush(tStackString **s, char* data)
{
	if((*s)->top == (*s)->max-1)
	{
		grealloc((void **) &((*s)->data), &((*s)->max), sizeof(char*));
	}

	char *new = gmalloc(strlen(data)+1, free);

	(*s)->data[++((*s)->top)] = new;
	strcpy(new, data);
}

void stackIfInit(tStackIf *s, int size)
{
	s->top = -1;
	s->max = size;
	s->counter = 0;
	s->data = gmalloc(sizeof(tIf*)*size, free);

	if(s->data == NULL)
	{
		DEBUG("init");
		printError(ALLOCERROR,INTERPRETERROR);
	}
}

void stackIfPop(tStackIf **s)
{
	if((*s)->top == -1)
	{
		DEBUG("pop");
		printError(STACKERROR, INTERPRETERROR);
	}

	(*s)->top -= 2;
	(*s)->counter--;
}

void stackIfPush(tStackIf **s, int type, int *destination)
{
	if((*s)->top == (*s)->max-1)
	{
		grealloc((void **) &((*s)->data), &((*s)->max), sizeof(tIf));
	}
	(*s)->data[++((*s)->top)] = gmalloc(sizeof(tIf), free);
	(*s)->data[(*s)->top]->type = (*s)->counter++ * type;
	(*s)->data[(*s)->top]->destination = destination;
}

int * stackIfTop(tStackIf **s)
{
	if((*s)->top == -1)
	{
		DEBUG("top");
		printError(STACKERROR, INTERPRETERROR);
	}

	return (*s)->data[(*s)->top]->destination;
}
