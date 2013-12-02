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
	NULL,
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
	{0,0,0,0,0,0,0,0,0,0,0,28,0,0,0,0,28,28,28,28,28,28,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,29,0,29,0,0,0,0,0,29,29,29,0,30,0,0,0,0,0,0,0,31},
	{0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,0,32,32,32,32,32,32,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,33,0,0,0,0,33,33,33,33,33,33,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int intMaxChars()
{
	unsigned num = ~0;
	int counter = 0;

	while(num > 0)
	{
		num /=10;
		counter++;
	}

	return counter+1;
}

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
	sVariable *variable;
	tStack *tmpStack = gmalloc(sizeof(tStack), free);
	stackInit(tmpStack, 2);
	tStackVar *stackVar = gmalloc(sizeof(tStackVar), free);
	stackVarInit(stackVar, 2);

	do
	{
		top = stackTopTerminal(s, &tmpStack, true);
		operation = precedenceTable[top][isOperand(t->name) ? VALUE : t->name];

		switch(operation)
		{
			case REDUCE: reduce(s, &tmpStack, &stackVar);break;
			case SHIFT:
				if(isOperand(t->name) && t->name != VAR)
				{
					variable = generateLiteral(t);
					stackVarPush(&stackVar, variable);
				}
				else if(t->name == VAR)
				{
					variable = BSTV_Search(actualFunction[0]->variables, t->content);

					if(variable == NULL)
					{
						printError(VARIABLENOTEXISTS, UNDECLAREDVARIABLE);
					}
					stackVarPush(&stackVar, variable);
				}


				shift(s, &tmpStack, t);
				break;

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

//TODO volat při výpisu
char * escapeSequences(char * str)
{
	int index = -1;
	char substr[5];
	// char *replacements[][2] =
	// {
	// 	{"\\t", "\t"},
	// 	{"\\n", "\n"},
	// 	{"\\\\", "\\"},
	// 	{"\\\"", "\""},
	// 	{"\\$", "$"},
	// };

	// for(int i = 0; i < 5; ++i)
	// {
	// 	sprintf(substr, "%s", replacements[i][0]);
	// 	while((index = IAL_find_string(str, substr)) > -1)
	// 	{
	// 		str[index] = replacements[i][1][0];
	// 		shiftString(str, index+1, 1);
	// 	}
	// }

	for(int i = 0; i <= 255; ++i)
	{
		sprintf(substr, "\\x%.2X", i);
		// DEBUG(substr);
		while((index = IAL_find_string(str, substr)) > -1)
		{
			str[index] = i;
			shiftString(str, index+1, 3);
		}

		sprintf(substr, "\\x%.2x", i);
		while((index = IAL_find_string(str, substr)) > -1)
		{
			str[index] = i;
			shiftString(str, index+1, 3);
		}
	}

	char * new = gmalloc(strlen(str)+1, free);
	strcpy(new, str);

	return new;
}

void shiftString(char * str, unsigned index, unsigned n)
{
	unsigned i;
	for(i = index; i+n < strlen(str); ++i)
	{
		str[i] = str[i+n];
	}

	str[i] = '\0';
}

void reduce(tStack **s,tStack **tmpStack, tStackVar **stackVar)
{
	stackPush(s, REDUCE);
	stackPop(s);

	tInstruction *instruction;
	sVariable *var;
	char* pushVarName;

	while(!stackEmpty(*tmpStack)) stackPush(s, stackPop(tmpStack));

	int top = stackPop(s);
	int operator = -1;

	// i -> E
	if(top == VALUE)
	{
		top = stackPop(s);

		if(top == SHIFT)
		{
			var = stackVarPop(stackVar);
			pushVarName = gmalloc(strlen(var->key)+1, free);
			strcpy(pushVarName, var->key);

			instruction = gmalloc(sizeof(tInstruction), free);
			instruction->f=pushSVar;
			instruction->variable = pushVarName;
			instruction->functionName = NULL;

			stackInstructionPush(&(actualFunction[0]->code), instruction);

			stackPush(s, E);
			return;
		}
	}
	// (E) -> E
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
	//E op E -> E
	else if(top == E)
	{
		top = stackPop(s);

		if(isOperator(top))
		{
			operator = top;
			top = stackPop(s);

			if(top == E)
			{
				top = stackPop(s);

				if(top == SHIFT)
				{
					stackPush(s, E);

					instruction = gmalloc(sizeof(tInstruction), free);
					instruction->variable = NULL;
					instruction->functionName = NULL;

					switch(operator)
					{
						case EQUAL:instruction->f = equal;break;
						case NOTEQUAL:instruction->f = notEqual;break;
						case BIGGER:instruction->f = bigger;break;
						case LESSER:instruction->f = lesser;break;
						case BIGGEREQUAL:instruction->f = biggerEqual;break;
						case LESSEREQUAL:instruction->f = lesserEqual;break;
						case PLUS:instruction->f = add;break;
						case MINUS:instruction->f = sub;break;
						case TIMES:instruction->f = mul;break;
						case DIVISION:instruction->f = division;break;
						case DOT:instruction->f = concatenate;break;
					}

					stackInstructionPush(&(actualFunction[0]->code), instruction);
					return;
				}
			}
		}
	}

	// DEBUG("Neexistuje pravidlo pro reduce");
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

sVariable * generateLiteral(tToken *t)
{
	static int literalCounter = 0;
	char literal[intMaxChars()];

	sprintf(literal, "%d", literalCounter++);
	sVariable *argvar = BSTV_Insert(&(actualFunction[0]->variables), literal);
	argvar->type = t->name;
	argvar->defined = true;
	// BSTV_Print(actualFunction[0]);
	char *endptr;

	switch(argvar->type)
	{
		case INTEGER:
			argvar->value->intv = (int) strtol(t->content, &endptr, 10);
			break;
		case DOUBLE:
			argvar->value->doublev = strtod(t->content, &endptr);
			break;
		case NULLV: break;
		case BOOLEAN: argvar->value->boolv = strcmp(t->content, "true") == 0;break;
		case STRING: argvar->value->stringv = escapeSequences(t->content);break;
	}

	return argvar;
}

void generateParams(tToken *t)
{
	if(BSTV_Search(actualFunction[0]->variables, t->content) != NULL) printError(SAMEPARAM, OTHERS);
	BSTV_Insert(&(actualFunction[0]->variables), t->content);
	stackStringPush(&(actualFunction[0]->paramNames), t->content);
}

void generateArguments(tToken *t, LLFunction *LLCall)
{
	sFunction *topFunction = actualFunction[0];
	sVariable *argvar;
	char *pushVarName;

	if(LLCall == argumentVar)
	{
		argvar = BSTV_Search(topFunction->variables , t->content);
		if(argvar == NULL) argvar = BSTV_Insert(&(topFunction->variables), t->content);
	}
	else
	{
		argvar = generateLiteral(t);
	}

	pushVarName = gmalloc(strlen(argvar->key)+1, free);
	strcpy(pushVarName, argvar->key);
	generateInstruction(pushSVar, pushVarName, NULL);
}

void parse(tStack *stack, tToken *t)
{
	bool breakParent = false;
	bool inFunction = false;
	instructionFunction *generatedFunction = NULL;
	bool waitingSemicolon = false;
	sVariable *destination = NULL;
	char * calledFunctionName = NULL;
	int innerBraces = 0;
	int *dstJump;
	char* variableName;
	LLFunction *LLCall = NULL;
	tInstruction *instruction;
	sFunction *topFunction;

	tStack *conditionStack = gmalloc(sizeof(tStack), free);
	stackInit(conditionStack, 2);
	tStackIf *ifStack = gmalloc(sizeof(tStackIf), free);
	stackIfInit(ifStack, 2);
	tStack *whileStack = gmalloc(sizeof(tStack), free);
	stackInit(whileStack, 2);

	getToken(f, t);
	stackPush(&stack, NPROGRAM);

	while(t->name != END && !stackEmpty(stack))
	{
		while(stackTop(&stack) < NONTERMINALBORDER)
		{

			if(t->name == SEMICOLON && waitingSemicolon)
			{
				generateInstruction(generatedFunction, variableName, calledFunctionName);

				waitingSemicolon = false;
				generatedFunction = NULL;
				variableName = NULL;
				calledFunctionName = NULL;
			}

			if(stackPop(&stack) != t->name)
			{
				breakParent = true;
				break;
			}

			if(LLCall == commandVar && t->name == VAR)
			{
				destination = BSTV_Insert(&(actualFunction[0]->variables), t->content);
				waitingSemicolon = true;
				generatedFunction = assign;
				variableName = gmalloc(strlen(destination->key)+1,free);
				strcpy(variableName, destination->key);
				// destination = NULL;
			}
			else if(LLCall == commandIf && t->name == IF)
			{
				stackPush(&conditionStack, IF);
			}
			else if(LLCall == commandWhile && t->name == WHILE)
			{
				stackPush(&conditionStack, WHILE);
				stackPush(&whileStack, actualFunction[0]->code->top+1);
			}
			else if(LLCall == block && t->name == OPENBRACE)
			{
				++innerBraces;
				if(!stackEmpty(conditionStack) && stackTop(&conditionStack) == IF)
				{
					generateInstruction(jmpFalse, NULL, NULL);
					instruction = stackInstructionTop(&(actualFunction[0]->code));
					stackIfPush(&ifStack, 1, &(instruction->destination));
				}
				else if(!stackEmpty(conditionStack) && stackTop(&conditionStack) == WHILE)
				{
					generateInstruction(jmpFalse, NULL, NULL);
					stackPush(&whileStack, actualFunction[0]->code->top);
				}
			}
			else if(t->name == CLOSEBRACE)
			{
				--innerBraces;

				if(innerBraces == 0 && inFunction)
				{
					generateInstruction(iReturn, NULL, NULL);
					actualFunction[0] = actualFunction[1];
					inFunction = false;
				}
				else if(!stackEmpty(conditionStack))
				{
					if(stackTop(&conditionStack) == IF)
					{
						stackPop(&conditionStack);
						stackPush(&conditionStack, ELSE);

						generateInstruction(jmp, NULL, NULL);
						dstJump = stackIfTop(&ifStack);
						*dstJump = actualFunction[0]->code->top+1;

						instruction = stackInstructionTop(&(actualFunction[0]->code));
						stackIfPush(&ifStack, -1, &(instruction->destination));
					}
					else if(stackTop(&conditionStack) == ELSE)
					{
						stackPop(&conditionStack);

						dstJump = stackIfTop(&ifStack);
						*dstJump = actualFunction[0]->code->top+1;
						stackIfPop(&ifStack);
					}
					else if(stackTop(&conditionStack) == WHILE)
					{
						stackPop(&conditionStack);
						generateInstruction(jmp, NULL, NULL);
						instruction = stackInstructionTop(&(actualFunction[0]->code));
						actualFunction[0]->code->data[stackPop(&whileStack)]->destination = actualFunction[0]->code->top+1;
						instruction->destination = stackPop(&whileStack);
					}
				}

			}
			else if(LLCall == commandReturn)
			{
				waitingSemicolon = true;
				generatedFunction = iReturn;
			}
			else if(LLCall == function && t->name == ID)
			{
				actualFunction[1] = actualFunction[0];
				actualFunction[0] = BSTF_Insert(&functionTree, t->content);
				innerBraces = 0;
				inFunction = true;
			}
			else if((LLCall == paramList1 || LLCall == paramList2) && t->name == VAR)
			{
				generateParams(t);
			}
			else if(LLCall == functionCall && t->name == VAR)
			{
				topFunction = stackFuncTop(&stackFunctions);
				destination = BSTV_Search(topFunction->variables, t->content);
				waitingSemicolon = true;
				generatedFunction = assign;
				variableName = NULL;
				// variableName = gmalloc(strlen(destination->key)+1,free);
				// strcpy(variableName, destination->key);
				calledFunctionName = destination->key;
				destination = NULL;
			}
			else if(LLCall == functionCall && t->name == ID)
			{
				calledFunctionName = gmalloc(strlen(t->content)+1, free);
				strcpy(calledFunctionName, t->content);
			}
			else if(isOperand(t->name) && (LLCall == argumentDouble || LLCall == argumentNull || LLCall == argumentBoolean || LLCall ==  argumentVar || LLCall == argumentInteger || LLCall == argumentString))
			{
				generateArguments(t, LLCall);
			}
			else if(LLCall == argumentList && t->name == CLOSEPAREN)
			{
				generateInstruction(iFunctionCall, NULL, calledFunctionName);
			}

			getToken(f, t);
		}

		if(breakParent) break;

		LLCall = LLRule[LLTable[stackTop(&stack)-NONTERMINALBORDER][t->name]];

		if(LLCall == NULL)
		{
			break;
		}

		LLCall(&stack, t);
	}
}

int main (int argc, char *argv[])
{
	ginit();

	stackVariables = gmalloc(sizeof(tStackVar), free);
	stackVarInit(stackVariables, 8);

	stackFunctions = gmalloc (sizeof(tStackFunc),free);
	stackFuncInit (stackFunctions, 2);

	if (argc!=2) printError(PARAMSERROR,INTERPRETERROR);
	f=fopen(argv[1],"r");
	if (f==NULL) printError(SOURCECODEERR,INTERPRETERROR);

	// pokud nezacina < je to chyba
	int c=fgetc(f);
	if (c!='<') printError(SYNTAXERR,SYNTAXERROR);
	else ungetc (c,f);


	tToken *t = (tToken *) gmalloc(sizeof(tToken), free);
	t->content = (char *) gmalloc(40, free);
	tStack *stack = gmalloc(sizeof(tStack), free);

	stackInit(stack, 2);

	BSTF_Init(&functionTree);
	actualFunction[0] = BSTF_Insert(&functionTree, "1");
	// BSTF_Print(functionTree);
	gadd(functionTree, BSTF_Dispose);
	BSTF_Insert(&functionTree, "boolval");
	BSTF_Insert(&functionTree, "intval");
	BSTF_Insert(&functionTree, "strval");
	BSTF_Insert(&functionTree, "doubleval");
	BSTF_Insert(&functionTree, "put_string");
	BSTF_Insert(&functionTree, "find_string");
	BSTF_Insert(&functionTree, "sort_string");
	BSTF_Insert(&functionTree, "get_substring");
	BSTF_Insert(&functionTree, "get_string");
	BSTF_Insert(&functionTree, "strlen");

	stackFuncPush(&stackFunctions, actualFunction[0]);

	parse(stack, t);

	if(stackEmpty(stack) || t->name != END || stackTop(&stack) != END || stack->top != 0)
	{
		// DEBUG("špatné ukončení programu");
		printError(SYNTAXERR, SYNTAXERROR);
	}

	generateInstruction(iReturn, NULL, NULL);
	// printInstructionStack(stackFunctions->data[0]->code);

	interpret();

	gfreeAll();
	fclose(f);

	return 0;
}
