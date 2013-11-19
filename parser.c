#include "parser.h"

int precedenceTable[][15] =
{
	{REDUCE,REDUCE,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{REDUCE,REDUCE,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{REDUCE,REDUCE,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,REDUCE,REDUCE,SHIFT,REDUCE,SHIFT,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,EQUALSIGN,SHIFT,NOTHING},
	{REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,NOTHING,REDUCE,NOTHING,REDUCE},
	{REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,REDUCE,NOTHING,REDUCE,NOTHING,REDUCE},
	{SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,SHIFT,FINISH,SHIFT,NOTHING}
};

LLFunction *LLRule[] =
{
	NULL,
	argumentString,
	argumentInteger,
	argumentVar,
	argumentNull,
	argumentBoolean,
	argumentDouble,
	argumentList,
	argumentArgumentList1,
	argumentArgumentList2,
	argumentList,
	block,
	semicolon,
	commandVar,
	commandReturn,
	commandIf,
	commandWhile,
	closebrace,
	commandList,
	function,
	functionCall,
	expressionSemicolon,
	closeparen,
	paramList1,
	closeparen,
	paramList2,
	program,
	returnEnd,
	returnExpression,
	statementCommand,
	statementFunction,
	statementEnd,
	expression,
	expressionParen
};

/* @var tabulka která vrací pravidlo, to se použije pro indexaci funkcí LL tabulky */
int LLTable[][36] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,5,2,6,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,13,0,0,0,0,0,16,14,15,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,0,18,0,0,0,0,0,18,18,18,0,0,0,0,0,17,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,21,0,0,0,20,21,21,21,21,21,21,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,22,0,0,0,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,26,0},
	{0,0,0,0,0,0,0,0,0,0,0,28,0,0,27,0,28,28,28,28,28,28,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,29,0,29,0,0,0,0,0,29,29,29,0,30,0,0,0,0,0,0,0,31},
	{0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,0,32,32,32,32,32,32,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,33,0,0,0,0,33,33,33,33,33,33,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

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
		tokenName == DIVISION ||
		tokenName == DOT ||
		tokenName == BIGGER ||
		tokenName == LESSER ||
		tokenName == BIGGEREQUAL ||
		tokenName == LESSEREQUAL ||
		tokenName == EQUAL ||
		tokenName == NOTEQUAL;
}



void argumentString(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, STRING);
}

void argumentInteger(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, INTEGER);
}

void argumentVar(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, VAR);
}

void argumentNull(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NULLV);
}

void argumentBoolean(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, BOOLEAN);
}

void argumentDouble(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, DOUBLE);
}

void semicolon(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, SEMICOLON);
}

void closebrace(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, CLOSEBRACE);
}

void closeparen(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, CLOSEPAREN);
}

void argumentList(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, SEMICOLON);
	stackPush(s, CLOSEPAREN);
}

void argumentArgumentList1(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NARGUMENTLIST2);
	stackPush(s, NARGUMENT);
}

void argumentArgumentList2(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NARGUMENTLIST2);
	stackPush(s, NARGUMENT);
	stackPush(s, COMMA);
}

void block(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NCOMMANDLIST);
	stackPush(s, OPENBRACE);
}

void commandVar(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NFUNCTIONCALLEXPRESSION);
	stackPush(s, ASSIGN);
	stackPush(s, VAR);
}

void commandReturn(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NRETURN);
	stackPush(s, RETURN);
}

void commandIf(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NBLOCK);
	stackPush(s, ELSE);
	stackPush(s, NBLOCK);
	stackPush(s, CLOSEPAREN);
	stackPush(s, NEXPRESSIONPAREN);
	stackPush(s, OPENPAREN);
	stackPush(s, IF);
}

void commandWhile(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NBLOCK);
	stackPush(s, CLOSEPAREN);
	stackPush(s, NEXPRESSIONPAREN);
	stackPush(s, OPENPAREN);
	stackPush(s, WHILE);
}

void commandList(tStack **s, tToken *t)
{
	stackPush(s, NCOMMAND);
}

void function(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NBLOCK);
	stackPush(s, NPARAMLIST1);
	stackPush(s, OPENPAREN);
	stackPush(s, ID);
	stackPush(s, FUNCTION);
}

void functionCall(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NARGUMENTLIST1);
	stackPush(s, OPENPAREN);
	stackPush(s, ID);
}

void expressionSemicolon(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, SEMICOLON);
	stackPush(s, NEXPRESSION);
}

void paramList1(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NPARAMLIST2);
	stackPush(s, VAR);
}

void paramList2(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NPARAMLIST2);
	stackPush(s, VAR);
	stackPush(s, COMMA);
}

void program(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, NSTATEMENT);
	stackPush(s, BEGIN);
}

void returnEnd(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, SEMICOLON);
}

void returnExpression(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, SEMICOLON);
	stackPush(s, NEXPRESSION);
}

void statementCommand(tStack **s, tToken *t)
{
	stackPush(s, NCOMMAND);
}

void statementFunction(tStack **s, tToken *t)
{
	stackPush(s, NFUNCTION);
}

void statementEnd(tStack **s, tToken *t)
{
	stackPop(s);
	stackPush(s, END);
}

void expressionParen(tStack **s, tToken *t)
{
	// DEBUG("expressionParen");
	// exit(1);
	stackPop(s);
	stackPush(s, SEMICOLON); //zarážka pro výrazy se závorkou
	stackPush(s, NEXPRESSION);
	expression(s, t);
	stackPop(s);
}

void expression(tStack **s, tToken *t)
{
	stackPop(s);

	int top, operation;
	tStack *tmpStack = gmalloc(sizeof(tStack), free);
	stackInit(tmpStack, 8);

	do
	{
		top = stackTopTerminal(s, &tmpStack, true);
		operation = precedenceTable[top][isOperand(t->name) ? VALUE : t->name];
		// printf("%d\n",top);
		// printf("%d\n",t->name);
		// printf("%d", SEMICOLON);
		// printf("%d", operation);
		switch(operation)
		{
			case REDUCE: reduce(s, &tmpStack);break;
			case SHIFT: shift(s, &tmpStack, t);break;
			case EQUALSIGN: equalsign(s, &tmpStack, t);break;
			case FINISH:
				stackTopTerminal(s, &tmpStack, true);
				return;

			default: printError(SYNTAXERR, SYNTAXERROR);
		}
	// DEBUG(tokenNames[stackTop(s)]);
	// DEBUG(tokenNames[t->name]);
	} while(stackTopTerminal(s, &tmpStack, false) != SEMICOLON || t->name != SEMICOLON);

	stackTopTerminal(s, &tmpStack, true);
	gfree(tmpStack);
}


void reduce(tStack **s,tStack **tmpStack)
{
	stackPush(s, REDUCE);
	stackPop(s);

	while(!stackEmpty(*tmpStack)) stackPush(s, stackPop(tmpStack));

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

void shift(tStack **s, tStack **tmpStack, tToken *t)
{
	// terminal = stackTopTerminal(s, tmpStack, true);

	stackPush(s, SHIFT);

	while(!stackEmpty(*tmpStack)) stackPush(s, stackPop(tmpStack));

	stackPush(s, isOperand(t->name) ? VALUE : t->name );
	getToken(f, t);
}

void equalsign(tStack **s,tStack **tmpStack, tToken *t)
{
	while(!stackEmpty(*tmpStack)) stackPush(s, stackPop(tmpStack));

	stackPush(s, t->name);
	getToken(f, t);
}

int main (int argc, char *argv[])
{
	bool breakParent = false;
	int innerBraces;
	LLFunction *LLCall;

	if (argc!=2) printError(PARAMSERROR,INTERPRETERROR);
	f=fopen(argv[1],"r");
	if (f==NULL) printError(SOURCECODEERR,INTERPRETERROR);

	// pokud nezacina < je to chyba
	int c=fgetc(f);
	if (c!='<') printError(SYNTAXERR,SYNTAXERROR);
	else ungetc (c,f);

	ginit();
	tToken *t = (tToken *) gmalloc(sizeof(tToken), free);
	t->content = (char *) gmalloc(40, free);
	tStack *stack = gmalloc(sizeof(tStack), free);
	stackInit(stack, 40);

	BSTF_Init(&functionTree);
	actualFunction[0] = BSTF_Insert(&functionTree, "1");
	BSTF_Print(functionTree);
	gadd(functionTree, BSTF_Dispose);

	// typ struktury tokenu
	getToken(f, t);
	stackPush(&stack, NPROGRAM);

	while(t->name != END && !stackEmpty(stack))
	{
		while(stackTop(&stack) < NONTERMINALBORDER)
		{

			if(stackPop(&stack) != t->name)
			{
				DEBUG("break parent konec");
				breakParent = true;
				// getToken(f, t);
				break;
			}

			if(LLCall == commandVar && t->name == VAR)
			{
				printf("přidávám proměnnou: %s do funkce %s\n", t->content, actualFunction[0]->key);
				BSTV_Insert(&(actualFunction[0]->variables), t->content);
				BSTV_Print(actualFunction[0]);
			}
			else if(LLCall == function && t->name == ID)
			{
				actualFunction[1] = actualFunction[0];
				actualFunction[0] = BSTF_Insert(&functionTree, t->content);
				BSTF_Print(functionTree);
			}
			else if((LLCall == paramList1 || LLCall == paramList2) && t->name == VAR)
			{
				BSTV_Insert(&(actualFunction[0]->variables), t->content);
				BSTV_Print(actualFunction[0]);
			}
			else if(LLCall == function && t->name == OPENBRACE)
			{
				innerBraces = 0;
			}
			else if(t->name == OPENBRACE)
			{
				DEBUG("přidávám {");
				++innerBraces;
			}
			else if(t->name == CLOSEBRACE)
			{
				--innerBraces;
				if(innerBraces == 0)
				{
					printf("vylézám z funkce %s", actualFunction[0]->key);
					actualFunction[0] = actualFunction[1];
				}
			}

			getToken(f, t);
		}

		if(breakParent) break;

		LLCall = LLRule[LLTable[stackTop(&stack)-NONTERMINALBORDER][t->name]];

		if(LLCall == NULL)
		{
			DEBUG("není pravidlo ");
			break;
		}

		LLCall(&stack, t);
	}

	if(stackEmpty(stack) || t->name != END || stackTop(&stack) != END || stack->top != 0)
	{
		DEBUG("špatné ukončení programu");
		printError(SYNTAXERR, SYNTAXERROR);
	}

	gfreeAll();
	fclose(f);

	return 0;
}
