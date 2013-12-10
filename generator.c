#include "generator.h"


tVariable * duplicateTree(tVariable * root)
{
	if(root == NULL)
	{
		return NULL;
	}

	tVariable *new, *newItem, *prev;
	BSTV_Init(&new);

	sVariable *stack = gmalloc(sizeof(sVariable), free);
	stackVarInit(stack, 5);

	while(root != NULL)
	{
		stackVarPush(&stack, root);

		newItem = BSTV_Insert(&new, root->key);
		memcpy(newItem->key, root->key, strlen(root->key)*sizeof(char)+1);
		memcpy(newItem->value, root->value, sizeof(tVariableValue));
		newItem->defined = root->defined;
		newItem->type = root->type;
		newItem->lptr = NULL;
		newItem->rptr = NULL;
		root = root->lptr;
	}

	while(!stackVarEmpty(stack) || root->rptr != NULL)
	{
		root = stackVarPop(&stack);

		if(root->rptr != NULL)
		{
			prev = root;
			root = root->rptr;

			while(root != NULL)
			{
				newItem = BSTV_Insert(&new, root->key);
				memcpy(newItem->key, root->key, strlen(root->key)*sizeof(char)+1);
				memcpy(newItem->value, root->value, sizeof(tVariableValue));
				newItem->defined = root->defined;
				newItem->type = root->type;
				newItem->lptr = NULL;
				newItem->rptr = NULL;
				stackVarPush(&stack, root);
				root = root->lptr;
			}

			root = prev;
		}
	}

	return new;
}

// funkce pro duplikaci funkce
void duplicateFunction (tFunction *f)
{
	tFunction *tmpFunc = gmalloc (sizeof(tFunction), free);
	memcpy(tmpFunc,f,sizeof(tFunction));
	tmpFunc->codePosition=0;
	tmpFunc->variables=duplicateTree(f->variables);
	stackFuncPush(&stackFunctions,tmpFunc);
}





// aritmeticke instrukce

// pomocna funkce pro zjisteni, jestli je promenna typu int
bool isInt (tVariable *var)
{
	return var->type == INTEGER;
}

// pomocna funkce pro zjisteni jestli je promenna typu double
bool isDouble (tVariable *var)
{
	return var->type == DOUBLE;
}

// pomocne funkce, rozpoznavajici typy promennych aritmetickych operaci
bool twoInts (tVariable *par1,tVariable *par2)
{
	return isInt(par1) && isInt(par2);
}

bool twoDoubles (tVariable *par1,tVariable *par2)
{
	return isDouble(par1) && isDouble(par2);
}

bool intDouble (tVariable *par1,tVariable *par2)
{
	return isInt(par1) && isDouble(par2);
}

bool doubleInt (tVariable *par1,tVariable *par2)
{
	return isDouble(par1) && isInt(par2);
}

// -------------------------------------------------------------

// instrukce souctu +
void add (char * param, char * function)
{
	tVariable *par1, *par2, * source = stackVarTopUsable(&stackTmpVariables);
	// source->value = gmalloc (sizeof(tVariableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);

	// oba parametry int . vraci int
	if (twoInts(par1,par2))
	{
		source->type=INTEGER;
		source->value->intv=par1->value->intv + par2->value->intv;
		stackVarPush(&stackVariables, source);
	}
	// oba double
	else if (twoDoubles(par1,par2))
	{
		source->type=DOUBLE;
		source->value->doublev=par1->value->doublev + par2->value->doublev;
		stackVarPush(&stackVariables, source);
	}
	// double a int
	else if (doubleInt(par1,par2))
	{
		source->type=DOUBLE;
		source->value->doublev=par1->value->doublev + (double)par2->value->intv;
		stackVarPush(&stackVariables, source);
	}
	// int a double
	else if (intDouble(par1,par2))
	{
		source->type=DOUBLE;
		source->value->doublev=(double)par1->value->intv + par2->value->doublev;
		stackVarPush(&stackVariables, source);
	}
	else printError(INCOMPATIBLETYPE,INCOMPATIBLE);

}


// operace rozdilu -
void sub (char * param, char * function)
{
	tVariable *par1, *par2, * source = stackVarTopUsable(&stackTmpVariables);
	// source->value = gmalloc (sizeof(tVariableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);

	// oba parametry int . vraci int
	if (twoInts(par1,par2))
	{
		source->type=INTEGER;
		source->value->intv=par1->value->intv - par2->value->intv;
		stackVarPush(&stackVariables, source);
	}
	// oba double
	else if (twoDoubles(par1,par2))
	{
		source->type=DOUBLE;
		source->value->doublev=par1->value->doublev - par2->value->doublev;
		stackVarPush(&stackVariables, source);
	}
	// double a int
	else if (doubleInt(par1,par2))
	{
		source->type=DOUBLE;
		source->value->doublev=par1->value->doublev - (double)par2->value->intv;
		stackVarPush(&stackVariables, source);
	}
	// int a double
	else if (intDouble(par1,par2))
	{
		source->type=DOUBLE;
		source->value->doublev=(double)par1->value->intv - par2->value->doublev;
		stackVarPush(&stackVariables, source);
	}
	else printError(INCOMPATIBLETYPE,INCOMPATIBLE);

}


// instrukce nasobeni
void mul (char * param, char * function)
{
	tVariable *par1, *par2, * source = stackVarTopUsable(&stackTmpVariables);
	// source->value = gmalloc (sizeof(tVariableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);

	// oba parametry int . vraci int
	if (twoInts(par1,par2))
	{
		source->type=INTEGER;
		source->value->intv=par1->value->intv * par2->value->intv;
		stackVarPush(&stackVariables, source);
	}
	// oba double
	else if (twoDoubles(par1,par2))
	{
		source->type=DOUBLE;
		source->value->doublev=par1->value->doublev * par2->value->doublev;
		stackVarPush(&stackVariables, source);
	}
	// double a int
	else if (doubleInt(par1,par2))
	{
		source->type=DOUBLE;
		source->value->doublev=par1->value->doublev * (double)par2->value->intv;
		stackVarPush(&stackVariables, source);
	}
	// int a double
	else if (intDouble(par1,par2))
	{
		source->type=DOUBLE;
		source->value->doublev=(double)par1->value->intv * par2->value->doublev;
		stackVarPush(&stackVariables, source);
	}
	else printError(INCOMPATIBLETYPE,INCOMPATIBLE);

}

// instrukce deleni, osetruje deleni nulou
void division(char * param, char * function)
{
	tVariable *par1, *par2, * source = stackVarTopUsable(&stackTmpVariables);
	// source->value = gmalloc (sizeof(tVariableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);

	source->type=DOUBLE;
	// oba parametry int . vraci int
	if (twoInts(par1,par2))
	{
		if (par2->value->intv==0) printError(ZERODIVISION,ZERODIV);
		source->value->doublev=par1->value->intv / (double)par2->value->intv;
		stackVarPush(&stackVariables, source);
	}
	// oba double
	else if (twoDoubles(par1,par2))
	{
		if (par2->value->doublev==0.0) printError(ZERODIVISION,ZERODIV);
		source->value->doublev=par1->value->doublev / par2->value->doublev;
		stackVarPush(&stackVariables, source);
	}
	// double a int
	else if (doubleInt(par1,par2))
	{
		if (par2->value->intv==0) printError(ZERODIVISION,ZERODIV);
		source->value->doublev=par1->value->doublev / (double)par2->value->intv;
		stackVarPush(&stackVariables, source);
	}
	// int a double
	else if (intDouble(par1,par2))
	{
		if (par2->value->doublev==0.0) printError(ZERODIVISION,ZERODIV);
		source->value->doublev=(double)par1->value->intv / par2->value->doublev;
		stackVarPush(&stackVariables, source);
	}
	else printError(INCOMPATIBLETYPE,INCOMPATIBLE);

}

// pomocna pro velikost charu

int maxChars(int num)
{
	int counter = 0;
	while (num != 0)
	{
		counter++;
		num/=10;
	}
	// vraci o jedno vic pro minus a o jedno pro koncovou nulu
	return counter+2;

}

// konkatenace retezcu
void concatenate (char * param, char * function)
{
	tVariable *par1, *par2, * source = stackVarTopUsable(&stackTmpVariables);
	// source->value = gmalloc (sizeof(tVariableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);


	// prvni parametr musi byt string
	if (par1->type!=STRING) printError(INCOMPATIBLETYPE,INCOMPATIBLE);

	// vysledny bude take string
	source->type=STRING;

	int par2Length, par1Length=strlen(par1->value->stringv);

	switch (par2->type)
	{
		case INTEGER:
			source->value->stringv = gmalloc (sizeof(char)*(par1Length+maxChars(par2->value->intv)), free);
			sprintf(source->value->stringv,"%s%d",par1->value->stringv, par2->value->intv);
			break;

		case DOUBLE: // max delka double cca 35
			source->value->stringv = gmalloc (sizeof(char)*(par1Length+36),free);
			sprintf(source->value->stringv,"%s%g",par1->value->stringv,par2->value->doublev);
			break;

		case BOOLEAN:
			if (par2->value->boolv == true)
			{
				source->value->stringv = gmalloc (sizeof(char)*par1Length+2,free);
				strcpy (source->value->stringv , par1->value->stringv);
				source->value->stringv[par1Length]='1';
				source->value->stringv[par1Length+1]='\0';
			}
			else
			{
				source->value->stringv = gmalloc (sizeof(char)*par1Length+1,free);
				strcpy (source->value->stringv , par1->value->stringv);
				source->value->stringv[par1Length]='\0';
			}
			break;

		case NULLV:
			source->value->stringv = gmalloc (sizeof(char)*par1Length+1, free);
			strcpy(source->value->stringv , par1->value->stringv);
			break;

		case STRING:
			par2Length=strlen(par2->value->stringv);
			source->value->stringv = gmalloc (sizeof(char)*(par1Length + par2Length) +1, free);
			strcpy(source->value->stringv , par1->value->stringv);
			strcat(source->value->stringv , par2->value->stringv);
			source->value->stringv[par1Length+par2Length]='\0';
			// source->value->stringv[0]='\0';
			break;
	}
	stackVarPush(&stackVariables, source);

}


// operator ===
void equal (char * param, char * function)
{
	tVariable *par1, *par2, * source = stackVarTopUsable(&stackTmpVariables);
	// source->value = gmalloc (sizeof(tVariableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);


	//vysledek bool
	source->type=BOOLEAN;

	if (par1->type!=par2->type) source->value->boolv=false;
	else
	{
		switch (par1->type)
		{
			case STRING:
				source->value->boolv = !strcmp(par1->value->stringv,par2->value->stringv);
				break;

			case BOOLEAN:
				source->value->boolv=par1->value->boolv == par2->value->boolv;
				break;

			case INTEGER:
				source->value->boolv=par1->value->intv == par2->value->intv;
				break;

			case DOUBLE:
				source->value->boolv=par1->value->doublev == par2->value->doublev;
				break;

			case NULLV:
				source->value->boolv=true;
				break;
		}

	}
	stackVarPush(&stackVariables, source);

}

// operator !==
void notEqual (char * param, char * function)
{
	equal(param, function);
	tVariable * var = stackVariables->data[stackVariables->top];
	var->value->boolv = !var->value->boolv;
	// stackVariables->data[stackVariables->top]->value->boolv = !stackVariables->data[stackVariables->top]->value->boolv;
}

//operator >
void bigger (char * param, char * function)
{
	tVariable *par1, *par2, * source = stackVarTopUsable(&stackTmpVariables);
	// source->value = gmalloc (sizeof(tVariableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);


	source->type=BOOLEAN;

	if (par1->type!=par2->type) printError(INCOMPATIBLETYPE,INCOMPATIBLE);
	else
	{
		switch (par1->type)
		{
			case STRING:
				source->value->boolv = strcmp(par1->value->stringv,par2->value->stringv)>0;
				break;

			case BOOLEAN:
				source->value->boolv=par1->value->boolv > par2->value->boolv;
				break;

			case INTEGER:
				source->value->boolv=par1->value->intv > par2->value->intv;
				break;

			case DOUBLE:
				source->value->boolv=par1->value->doublev > par2->value->doublev;
				break;

			case NULLV:
				source->value->boolv = false;
				break;
		}

	}
	stackVarPush(&stackVariables, source);

}

//operator <
void lesser (char * param, char * function)
{
	tVariable *par1, *par2, * source = stackVarTopUsable(&stackTmpVariables);
	// source->value = gmalloc (sizeof(tVariableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);


	source->type=BOOLEAN;

	if (par1->type!=par2->type) printError(INCOMPATIBLETYPE,INCOMPATIBLE);
	else
	{
		switch (par1->type)
		{
			case STRING:
				source->value->boolv = strcmp(par1->value->stringv,par2->value->stringv)<0;
				break;

			case BOOLEAN:
				source->value->boolv=par1->value->boolv < par2->value->boolv;
				break;

			case INTEGER:
				source->value->boolv=par1->value->intv < par2->value->intv;
				break;

			case DOUBLE:
				source->value->boolv=par1->value->doublev < par2->value->doublev;
				break;

			case NULLV:
				source->value->boolv = false;
				break;
		}

	}
	stackVarPush(&stackVariables, source);

}

//operator <=
void lesserEqual (char * param, char * function)
{
	tVariable *par1, *par2, * source = stackVarTopUsable(&stackTmpVariables);
	// source->value = gmalloc (sizeof(tVariableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);

	source->type=BOOLEAN;

	if (par1->type!=par2->type) printError(INCOMPATIBLETYPE,INCOMPATIBLE);
	else
	{
		switch (par1->type)
		{
			case STRING:
				source->value->boolv = strcmp(par1->value->stringv,par2->value->stringv)<=0;
				break;

			case BOOLEAN:
				source->value->boolv=par1->value->boolv <= par2->value->boolv;
				break;

			case INTEGER:
				source->value->boolv=par1->value->intv <= par2->value->intv;
				break;

			case DOUBLE:
				source->value->boolv=par1->value->doublev <= par2->value->doublev;
				break;

			case NULLV:
				 source->value->boolv = true;
				break;
		}

	}
	stackVarPush(&stackVariables, source);

}

// operator >=
void biggerEqual (char * param, char * function)
{
	tVariable *par1, *par2, * source = stackVarTopUsable(&stackTmpVariables);
	// source->value = gmalloc (sizeof(tVariableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);
	source->type=BOOLEAN;

	if (par1->type!=par2->type) printError(INCOMPATIBLETYPE,INCOMPATIBLE);
	else
	{
		switch (par1->type)
		{
			case STRING:
			source->value->boolv = strcmp(par1->value->stringv,par2->value->stringv)>=0;
				break;

			case BOOLEAN:
				source->value->boolv=par1->value->boolv >= par2->value->boolv;
				break;

			case INTEGER:
				source->value->boolv=par1->value->intv >= par2->value->intv;
				break;

			case DOUBLE:
				source->value->boolv=par1->value->doublev >= par2->value->doublev;
				break;

			case NULLV:
				source->value->boolv = true;
				break;
		}

	}
	stackVarPush(&stackVariables, source);

}


// funkce pro zavolani funkce
// pokusi se najit ve stromu funkci danou funkci
// pokud ji nenajde, hlasi semantickou chybu
// pokud ano, naduplikuje ji, pushne na zasobnik funkci, pozici v kodu nastavi na 0

void iFunctionCall (char * param, char * function)
{
	tFunction *topFunction, * func = BSTF_Search(functionTree, function);
	if (func == NULL) printError(UNDECLAREDFUNCTION,FUNCTIONDEFINITIONERROR);

	if(func->function != NULL)
	{
		func->function();
	}

	// if (strcmp(func->key,"boolval") == 0)
	// {
	// 	if (stackVarEmpty(stackVariables)) printError(FEWPARAMETERS,PARAMMISSING);
	// 	stackVariables->top=0;
	// 	boolval();
	// }
	// else if (strcmp(func->key,"doubleval") == 0)
	// {
	// 	if (stackVarEmpty(stackVariables)) printError(FEWPARAMETERS,PARAMMISSING);
	// 	stackVariables->top=0;
	// 	doubleval();
	// }
	// else if (strcmp(func->key,"intval") == 0)
	// {
	// 	if (stackVarEmpty(stackVariables)) printError(FEWPARAMETERS,PARAMMISSING);
	// 	stackVariables->top=0;
	// 	intval();
	// }
	// else if (strcmp(func->key,"strval") == 0)
	// {
	// 	if (stackVarEmpty(stackVariables)) printError(FEWPARAMETERS,PARAMMISSING);
	// 	stackVariables->top=0;
	// 	strval();
	// }
	// else if (strcmp(func->key,"strlen") == 0)
	// {
	// 	if (stackVarEmpty(stackVariables)) printError(FEWPARAMETERS,PARAMMISSING);
	// 	stackVariables->top=0;
	// 	strlength();
	// }
	// else if (strcmp(func->key,"get_string") == 0)
	// {
	// 	stackVariables->top= -1;
	// 	get_string();
	// }
	// else if (strcmp(func->key,"put_string") == 0)
	// {
	// 	put_string();
	// }
	// else if (strcmp(func->key,"sort_string") == 0)
	// {
	// 	if (stackVarEmpty(stackVariables)) printError(FEWPARAMETERS,PARAMMISSING);
	// 	stackVariables->top = 0;
	// 	sort_string();
	// }
	// else if (strcmp(func->key,"find_string") == 0)
	// {
	// 	if (stackVariables->top < 1) printError(FEWPARAMETERS,PARAMMISSING);
	// 	stackVariables->top = 1;
	// 	find_string();
	// }
	// else if (strcmp(func->key,"get_substring") == 0)
	// {
	// 	if (stackVariables->top < 2) printError(FEWPARAMETERS,PARAMMISSING);
	// 	stackVariables->top = 2;
	// 	get_substring();
	// }
	else
	{
		duplicateFunction(func);
		topFunction = stackFuncTop(&stackFunctions);

		// DEBUG(topFunction->key);

		// BSTV_Print(topFunction->variables);
		int count=0;
		tVariable *var;
		tVariable * argument;

		while(count <= func->paramNames->top && count <= stackVariables->top)
		{
			var = BSTV_Search(topFunction->variables, func->paramNames->data[count]);

			argument = stackVariables->data[count++];
			var->type = argument->type;
			var->defined = true;

			switch(var->type)
			{
				case DOUBLE:
					var->value->doublev = argument->value->doublev;
				break;

				case INTEGER:
					var->value->intv = argument->value->intv;
					break;

				case STRING:
					var->value->stringv = gmalloc(sizeof(char)*strlen(argument->value->stringv)+1, free);
					strcpy(var->value->stringv , argument->value->stringv);
					break;

				case BOOLEAN:
					var->value->boolv = argument->value->boolv;
					break;
			}
		}

		if(count < func->paramNames->top+1 ) printError(FEWPARAMETERS,PARAMMISSING);
		stackVariables->top = -1;
	}
}


// v parseru pri redukci <i -> E se naalokuje novy prvek, tato funkce na nej dostane ukazatel
// a ten ve spravnou chvili strci na zasobnik
void pushSVar(char * param, char * function)
{
	tFunction *topFunction = stackFuncTop(&stackFunctions);
	tVariable *var = BSTV_Search(topFunction->variables, param);
	if(var == NULL || var->defined == false) printError(VARIABLENOTEXISTS, UNDECLAREDVARIABLE);
	stackVarPush(&stackVariables, var);
}


// popne ze zasobniku funkci, pokracuje se na zasobniku funkci na pozici, codePosition
// musi byt az za vyrazem
void iReturn (char * param, char * function)
{
	stackFuncPop(&stackFunctions);
}


// musi byt az za vyrazem / volanim fce
// nahraje hodnotu z vrcholu zasobniku hodnot hodnotu pro assign do par1
void assign (char * param, char * function)
{
	// tVariable * source = gmalloc(sizeof(tVariable),free);
	// source->value = gmalloc (sizeof(tVariableValue),free);
	tVariable * top = NULL;
	tFunction *topFunction = stackFuncTop(&stackFunctions);
	tVariable *var = BSTV_Search(topFunction->variables, param);
	var->defined = true;

	if(stackVarEmpty(stackVariables))
	{
		var->type = NULLV;
		return;
	}

	top = stackVarPop(&stackVariables);

	var->type = top->type; //TADY SE D8V8 NULLV

	switch (top->type)
	{
		case DOUBLE:
			var->value->doublev = top->value->doublev;
			break;

		case INTEGER:
			var->value->intv = top->value->intv;
			break;

		case STRING:
			// if (var->value->stringv != NULL) gfree(var->value->stringv);

			var->value->stringv = gmalloc(sizeof(char)*(strlen(top->value->stringv)+1), free);
			strcpy(var->value->stringv , top->value->stringv);
			break;

		case BOOLEAN:
			var->value->boolv = top->value->boolv;
			break;
	}
}


// skoc, pokud vyraz podminky if je false
// dava se az za vyraz podminky
void jmpFalse (char * param, char * function)
{
	tFunction *f = stackFuncTop(&stackFunctions);

	boolval();

	tVariable * top = stackVarPop(&stackVariables);

	if (top->value->boolv==false)
	{
		f->codePosition = f->code->data[f->codePosition-1]->destination;
	}
}

void jmp(char * param, char * function)
{
	tFunction *f = stackFuncTop(&stackFunctions);
	f->codePosition = f->code->data[f->codePosition-1]->destination;
}

void generateInstruction(instructionFunction *f, char *var, char * name)
{
	tInstruction *instruction;

	instruction = gmalloc(sizeof(tInstruction), free);
	instruction->f = f;
	instruction->variable = var;
	instruction->functionName = name;
	instruction->destination = 0;
	stackInstructionPush(&(actualFunction[0]->code), instruction);
}

void interpret(void)
{
	tFunction * topFunction;
	tInstruction * instruction;
	stackTmpVariables = gmalloc(sizeof(sVariable), free);
	stackVarInit(stackTmpVariables, 4);

	while(stackFunctions->top != -1)
	{
		topFunction = stackFunctions->data[stackFunctions->top];
		instruction = topFunction->code->data[topFunction->codePosition++];
		instruction->f(instruction->variable, instruction->functionName);
	}

}
