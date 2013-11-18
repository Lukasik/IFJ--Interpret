#include "parser.h"

//TODO napsat jako makra
int isOperand(int tokenName)
{
	return
		tokenName == VAR ||
		tokenName == INTEGER ||
		tokenName == DOUBLE ||
		tokenName == STRING ||
		tokenName == BOOLEAN ||
		tokenName == NULLV;
}

int isOperator(int tokenName)
{
	return
		tokenName == PLUS ||
		tokenName == MINUS ||
		tokenName == TIMES ||
		tokenName == DOT ||
		tokenName == DIVISION;
}



void argumentString(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, STRING);
}

void argumentInteger(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, INTEGER);
}

void argumentVar(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, VAR);
}

void argumentNull(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NULLV);
}

void argumentBoolean(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, BOOLEAN);
}

void argumentDouble(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, DOUBLE);
}

void semicolon(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, SEMICOLON);
}

void closebrace(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, CLOSEBRACE);
}

void closeparen(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, CLOSEPAREN);
}

void argumentList(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, SEMICOLON);
	stackPush(s, CLOSEPAREN);
}

void argumentArgumentList1(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NARGUMENTLIST2);
	stackPush(s, NARGUMENT);
}

void argumentArgumentList2(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NARGUMENTLIST2);
	stackPush(s, NARGUMENT);
	stackPush(s, COMMA);
}

void block(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NCOMMANDLIST);
	stackPush(s, OPENBRACE);
}

void commandVar(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NFUNCTIONCALLEXPRESSION);
	stackPush(s, ASSIGN);
	stackPush(s, VAR);
}

void commandReturn(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NRETURN);
	stackPush(s, RETURN);
}

void commandIf(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NBLOCK);
	stackPush(s, ELSE);
	stackPush(s, NBLOCK);
	stackPush(s, CLOSEPAREN);
	stackPush(s, NEXPRESSION);
	stackPush(s, OPENPAREN);
	stackPush(s, IF);
}

void commandWhile(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NBLOCK);
	stackPush(s, CLOSEPAREN);
	stackPush(s, NEXPRESSION);
	stackPush(s, OPENPAREN);
	stackPush(s, WHILE);
}

void commandList(tStack *s, tToken *t)
{
	stackPush(s, NCOMMAND);
}

void function(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NBLOCK);
	stackPush(s, NPARAMLIST1);
	stackPush(s, OPENPAREN);
	stackPush(s, ID);
	stackPush(s, FUNCTION);
}

void functionCall(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NARGUMENTLIST1);
	stackPush(s, OPENPAREN);
	stackPush(s, ID);
}

void expressionSemicolon(tStack *s, tToken *t)
{
	// DEBUG("expression vud");
	stackPop(s);
	stackPush(s, SEMICOLON);
	stackPush(s, NEXPRESSION);
}

void paramList1(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NPARAMLIST2);
	stackPush(s, VAR);
}

void paramList2(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NPARAMLIST2);
	stackPush(s, VAR);
	stackPush(s, COMMA);
}

void program(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, NSTATEMENT);
	stackPush(s, BEGIN);
}

void returnEnd(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, SEMICOLON);
}

void returnExpression(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, SEMICOLON);
	stackPush(s, NEXPRESSION);
}

void statementCommand(tStack *s, tToken *t)
{
	stackPush(s, NCOMMAND);
}

void statementFunction(tStack *s, tToken *t)
{
	stackPush(s, NFUNCTION);
}

void statementEnd(tStack *s, tToken *t)
{
	stackPop(s);
	stackPush(s, END);
}

void expression(tStack *s, tToken *t)
{
	DEBUG("expression");
	stackPop(s);

	int top, operation;
	tStack *tmpStack = gmalloc(sizeof(tStack), free);
	stackInit(tmpStack, 25);

	do
	{
		top = stackTopTerminal(s, tmpStack, true);
		operation = precedenceTable[top][isOperand(t->name) ? VALUE : t->name];
		// printf("%d\n",top);
		// printf("%d\n",t->name);
		// printf("%d", SEMICOLON);
		// printf("%d", operation);
		switch(operation)
		{
			case REDUCE: reduce(s,tmpStack);break;
			case SHIFT: shift(s, tmpStack, t);break;
			case EQUALSIGN: equalsign(s,tmpStack, t);break;
			default: printError(SYNTAXERR, SYNTAXERROR);
		}
	// DEBUG(tokenNames[stackTop(s)]);
	// DEBUG(tokenNames[t->name]);
	} while(stackTopTerminal(s, tmpStack, false) != SEMICOLON || t->name != SEMICOLON);

	stackTopTerminal(s, tmpStack, true);
}


void reduce(tStack *s,tStack *tmpStack)
{
	stackPush(s, REDUCE);
	stackPop(s);

	while(!stackEmpty(tmpStack)) stackPush(s, stackPop(tmpStack));

	int top = stackPop(s);

	if(top == VALUE)
	{
		top = stackPop(s);

		if(top == SHIFT)
		{
			stackPush(s, E);
			return;
		}
	}
	else if(top == CLOSEPAREN)
	{
		top = stackPop(s);

		if(top == E)
		{
			top = stackPop(s);

			if(top == OPENPAREN)
			{
				top = stackPop(s);

				if(top == SHIFT)
				{
					stackPush(s, E);
					return;
				}
			}
		}
	}
	else if(top == E)
	{
		top = stackPop(s);

		if(isOperator(top))
		{
			top = stackPop(s);

			if(top == E)
			{
				top = stackPop(s);

				if(top == SHIFT)
				{
					stackPush(s, E);
					return;
				}
			}
		}
	}

	DEBUG("Neexistuje pravidlo pro reduce");
	printError(SYNTAXERR, SYNTAXERROR);

}

void shift(tStack *s, tStack *tmpStack, tToken *t)
{
	// terminal = stackTopTerminal(s, tmpStack, true);

	stackPush(s, SHIFT);

	while(!stackEmpty(tmpStack)) stackPush(s, stackPop(tmpStack));

	stackPush(s, isOperand(t->name) ? VALUE : t->name );
	getToken(f, t);
}

void equalsign(tStack *s,tStack *tmpStack, tToken *t)
{
	while(!stackEmpty(tmpStack)) stackPush(s, stackPop(tmpStack));

	stackPush(s, t->name);
	getToken(f, t);
}

void stackInit(tStack *s, int size)
{
	s->top = -1;
	s->max = size-1;
	s->data = gmalloc(sizeof(int)*size, free);

	if(s->data == NULL)
	{
		DEBUG("init");
		printError(ALLOCERROR,INTERPRETERROR);
	}
}

int stackPop(tStack *s)
{
	if(s->top == -1)
	{
		DEBUG("pop");
		printError(STACKERROR, INTERPRETERROR);
	}
		printStack(s);

	return s->data[s->top--];
}

void stackPush(tStack *s, int data)
{
	if(s->top == s->max)
	{
		DEBUG("push");
		printError(STACKERROR, INTERPRETERROR);
	}
		printStack(s);

	s->data[++(s->top)] = data;
}

int stackTop(tStack *s)
{
	if(s->top == -1)
	{
		DEBUG("top");
		printError(STACKERROR, INTERPRETERROR);
	}

	return s->data[s->top];
}

int stackTopTerminal(tStack *s, tStack *tmpStack, bool useTmpStack)
{
	for(int i = s->top; i > -1; --i)
	{
		if(s->data[i] < NONTERMINALBORDER || s->data[i] >= PRECEDENCEBORDER) return s->data[i];
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

int main (int argc, char *argv[])
{
	bool breakParent = false;
	LLFunction *LLCall;
	// pokud spatny pocet parametru
	if (argc!=2) printError(PARAMSERROR,INTERPRETERROR);

	// pokus o otevreni zdrojaku
	f=fopen(argv[1],"r");
	// pripad nepodareneho otevreni
	if (f==NULL) printError(SOURCECODEERR,INTERPRETERROR);

	// kod otevren

	// pokud nezacina < je to chyba
	int c=fgetc(f);
	if (c!='<') printError(SYNTAXERR,SYNTAXERROR);
	else ungetc (c,f);

	ginit();
	tToken *t = (tToken *) gmalloc(sizeof(tToken), free);
	if(t == NULL) printError(ALLOCERROR, INTERPRETERROR);

	t->content = (char *) gmalloc(40, free);
	if(t->content == NULL) printError(ALLOCERROR, INTERPRETERROR);

	tStack *stack = gmalloc(sizeof(tStack), free);
	if(stack == NULL) printError(ALLOCERROR, INTERPRETERROR);
	stackInit(stack, 40);

	BSTF_Init(&functionTree);
	actualFunction[0] = BSTF_Insert(&functionTree, "1");

	// typ struktury tokenu
	getToken(f, t);
	stackPush(stack, NPROGRAM);

	while(t->name != END && !stackEmpty(stack))
	{
		while(stackTop(stack) < NONTERMINALBORDER)
		{
			DEBUG(tokenNames[t->name]);

			if(stackPop(stack) != t->name)
			{
				DEBUG("break parent konec");
				breakParent = true;
				// getToken(f, t);
				break;
			}
			getToken(f, t);
		}

		if(breakParent) break;
		// printf("%d\n", stackTop(stack)-NONTERMINALBORDER);
		// printf("%d\n", t->name);
		LLCall = LLRule[LLTable[stackTop(stack)-NONTERMINALBORDER][t->name]];

		if(LLCall == NULL)
		{
			DEBUG("není pravidlo ");
			break;
		}

		LLCall(stack, t);
	}

	if(stackEmpty(stack) || t->name != END || stackTop(stack) != END || stack->top != 0)
	{
		DEBUG("špatné ukončení programu");
		printError(SYNTAXERR, SYNTAXERROR);
	}

	gfreeAll();
	fclose(f);

	printf("ok\n");

	return 0;
}
