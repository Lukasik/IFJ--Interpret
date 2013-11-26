#include "generator.h"
#include "scanner.h"
#include "stack.h"
#include "structs.h"
#include <stdbool.h>


// TODO: iRETURN CELE

sVariable * duplicateTree(sVariable * root)
{
	if(root == NULL)
	{
		return NULL;
	}

	sVariable *new, *newItem, *prev;
	BSTV_Init(&new);
	gadd(new, BSTV_Dispose);
	tStackVar *stack = gmalloc(sizeof(tStackVar), free);
	stackVarInit(stack, 20);

	while(root != NULL)
	{
		stackVarPush(&stack, root);
		root = root->lptr;
	}

	while(!stackVarEmpty(stack) || root->rptr != NULL)
	{
		root = stackVarPop(&stack);

		newItem = BSTV_Insert(&new, root->key);
		memcpy(newItem->key, root->key, strlen(root->key)*sizeof(char)+1);
		memcpy(newItem->value, root->value, sizeof(variableValue));
		newItem->defined = root->defined;
		newItem->type = root->type;
		newItem->lptr = NULL;
		newItem->rptr = NULL;

		if(root->rptr != NULL)
		{
			prev = root;
			root = root->rptr;

			while(root != NULL)
			{
				stackVarPush(&stack, root);
				root = root->lptr;
			}

			root = prev;
		}
	}

	gfree(stack->data);
	gfree(stack);

	return new;
}

// funkce pro duplikaci funkce
void duplicateFunction (sFunction *f)
{
	sFunction *tmpFunc = gmalloc (sizeof(sFunction), free);
	memcpy(tmpFunc,f,sizeof(sFunction));
	tmpFunc->codePosition=tmpFunc->whileCounter=tmpFunc->ifCounter=0;
	tmpFunc->variables=duplicateTree(f->variables);
	stackFuncPush(&stackFunctions,tmpFunc);
}





// aritmeticke instrukce

// pomocna funkce pro zjisteni, jestli je promenna typu int
bool isInt (sVariable *var)
{
	return var->type == INTEGER;
}

// pomocna funkce pro zjisteni jestli je promenna typu double
bool isDouble (sVariable *var)
{
	return var->type == DOUBLE;
}

// pomocne funkce, rozpoznavajici typy promennych aritmetickych operaci
bool twoInts (sVariable *par1,sVariable *par2)
{
	return isInt(par1) && isInt(par2);
}

bool twoDoubles (sVariable *par1,sVariable *par2)
{
	return isDouble(par1) && isDouble(par2);
}

bool intDouble (sVariable *par1,sVariable *par2)
{
	return isInt(par1) && isDouble(par2);
}

bool doubleInt (sVariable *par1,sVariable *par2)
{
	return isDouble(par1) && isInt(par2);
}

// -------------------------------------------------------------

// instrukce souctu +
void add (sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

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
void sub (sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

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
void mul (sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

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
void division(sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);

	// oba parametry int . vraci int
	if (twoInts(par1,par2))
	{
		source->type=INTEGER;
		if (par2->value->intv==0) printError(ZERODIVISION,ZERODIV);
		source->value->intv=par1->value->intv / par2->value->intv;
		stackVarPush(&stackVariables, source);
	}
	// oba double
	else if (twoDoubles(par1,par2))
	{
		source->type=DOUBLE;
		if (par2->value->doublev==0.0) printError(ZERODIVISION,ZERODIV);
		source->value->doublev=par1->value->doublev / par2->value->doublev;
		stackVarPush(&stackVariables, source);
	}
	// double a int
	else if (doubleInt(par1,par2))
	{
		source->type=DOUBLE;
		if (par2->value->intv==0) printError(ZERODIVISION,ZERODIV);
		source->value->doublev=par1->value->doublev / (double)par2->value->intv;
		stackVarPush(&stackVariables, source);
	}
	// int a double
	else if (intDouble(par1,par2))
	{
		source->type=DOUBLE;
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
void concatenate (sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

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
			stackVarPush(&stackVariables, source);
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
void equal (sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

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
void notEqual (sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

	par2 = stackVarPop(&stackVariables);
	par1 = stackVarPop(&stackVariables);


	source->type=BOOLEAN;

	if (par1->type!=par2->type) source->value->boolv=true;
	else
	{
		switch (par1->type)
		{
			case STRING:
				source->value->boolv = strcmp(par1->value->stringv,par2->value->stringv);
				break;

			case BOOLEAN:
				source->value->boolv=par1->value->boolv != par2->value->boolv;
				break;

			case INTEGER:
				source->value->boolv=par1->value->intv != par2->value->intv;
				break;

			case DOUBLE:
				source->value->boolv=par1->value->doublev != par2->value->doublev;
				break;

			case NULLV:
				source->value->boolv=false;
				break;
		}

	}
	stackVarPush(&stackVariables, source);
}

//operator >
void bigger (sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

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
				 printError(INCOMPATIBLETYPE,INCOMPATIBLE);
				break;
		}

	}
	stackVarPush(&stackVariables, source);
}

//operator <
void lesser (sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

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
				 printError(INCOMPATIBLETYPE,INCOMPATIBLE);
				break;
		}

	}
	stackVarPush(&stackVariables, source);
}

//operator <=
void lesserEqual (sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

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
				 printError(INCOMPATIBLETYPE,INCOMPATIBLE);
				break;
		}

	}
	stackVarPush(&stackVariables, source);
}

// operator >=
void biggerEqual (sVariable * param, char * function)
{
	sVariable *par1, *par2, * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);

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
				 printError(INCOMPATIBLETYPE,INCOMPATIBLE);
				break;
		}

	}
	stackVarPush(&stackVariables, source);
}


// funkce pro zavolani funkce
// pokusi se najit ve stromu funkci danou funkci
// pokud ji nenajde, hlasi semantickou chybu
// pokud ano, naduplikuje ji, pushne na zasobnik funkci, pozici v kodu nastavi na 0

//TODO
void iFunctionCall (sVariable * param, char * function)
{
	sFunction *topFunction, * func = BSTF_Search(functionTree, function);
	if (func == NULL) printError(UNDECLAREDFUNCTION,FUNCTIONDEFINITIONERROR);

	duplicateFunction(func);

	topFunction = stackFuncTop(&stackFunctions);
	int count=0;
	sVariable *var;
	sVariable * argument;

	//TODO je vestavěná? -> může být putstring -> neomezené počet parametrů -> jiný přístup

	while(count < func->paramCount && count != stackVariables->top-1)
	{
		var = BSTV_Search(topFunction->variables, func->paramNames[count]);

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

	if(count < func->paramCount ) printError(FEWPARAMETERS,PARAMMISSING);
	stackVariables->top = -1;
}


// v parseru pri redukci <i -> E se naalokuje novy prvek, tato funkce na nej dostane ukazatel
// a ten ve spravnou chvili strci na zasobnik
void pushSVar(sVariable * param, char * function)
{
	stackVarPush(&stackVariables, param);
}


// popne ze zasobniku funkci, pokracuje se na zasobniku funkci na pozici, codePosition
// musi byt az za vyrazem
void iReturn (sVariable * param, char * function)
{
	stackFuncPop(&stackFunctions);
}


// musi byt az za vyrazem / volanim fce
// nahraje hodnotu z vrcholu zasobniku hodnot hodnotu pro assign do par1
void assign (sVariable * param, char * function)
{
	sVariable * source = gmalloc(sizeof(sVariable),free);
	source->value = gmalloc (sizeof(variableValue),free);
	sVariable * top;

	if(stackVarEmpty(stackVariables))
	{
		param->type = NULLV;
		return;
	}

	top = stackVarPop(&stackVariables);
	// top = 0x32123123;
	printf("param: %p\n", (void*)top);
	// param->type = top->type;
	// switch (top->type)
	// {
	// 	case DOUBLE:
	// 		param->value->doublev = top->value->doublev;
	// 		break;

	// 	case INTEGER:
	// 		param->value->intv = top->value->intv;
	// 		break;

	// 	case STRING:
	// 		if (param->value->stringv != NULL) free(param->value->stringv);

	// 		param->value->stringv = gmalloc(sizeof(char)*strlen(top->value->stringv)+1, free);
	// 		strcpy(param->value->stringv , top->value->stringv);
	// 		break;

	// 	case BOOLEAN:
	// 		param->value->boolv = top->value->boolv;
	// 		break;
	// }
}


// skoc, pokud vyraz podminky if je false
// dava se az za vyraz podminky
void jmpIfFalseIF (sVariable * param, char * function)
{
	sVariable * top = stackVarPop(&stackVariables);
	bool result;
	switch (top->type)
	{
		case DOUBLE:
			if (top->value->doublev==0.0) result=false;
			else result=true;
			break;

		case INTEGER:
			if (top->value->intv==0) result=false;
			else result=true;
			break;

		case STRING:
			if (strcmp("",top->value->stringv)==0) result=false;
			else result=true;
			break;

		case BOOLEAN:
			result=top->value->boolv;
			break;

		case NULLV:
			result=false;
		break;
	}

	if (result==false)
	{
		sFunction *f = stackFuncTop(&stackFunctions);
		f->codePosition = f->elseBranches[f->ifCounter++];
	}
}


// stejne jako jmpIFFalseIF, jen pro while
void jmpIfFalseWHILE (sVariable * param, char * function)
{
	sVariable * top = stackVarPop(&stackVariables);
	bool result;
	switch (top->type)
	{
		case DOUBLE:
			if (top->value->doublev==0.0) result=false;
			else result=true;
			break;

		case INTEGER:
			if (top->value->intv==0) result=false;
			else result=true;
			break;

		case STRING:
			if (strcmp("",top->value->stringv)==0) result=false;
			else result=true;
			break;

		case BOOLEAN:
			result=top->value->boolv;
			break;

		case NULLV:
			result=false;
		break;
	}

	if (result==false)
	{
		sFunction *f = stackFuncTop(&stackFunctions);
		f->codePosition = f->whileBranches[f->whileCounter++];
	}
}



// nepodminene skoky, provedou se vzdy
void jmpIF (sVariable * param, char * function)
{
	sFunction *f = stackFuncTop(&stackFunctions);
	f->codePosition = f->ifEnds[f->ifCounter++];
}

void jmpWHILE (sVariable * param, char * function)
{
	sFunction *f = stackFuncTop(&stackFunctions);
	f->codePosition = f->whileEnds[f->whileCounter++];
}

void generateInstruction(instructionFunction *f, sVariable *var, char * name)
{
	tInstruction *instruction;
	sFunction *topFunction = stackFuncTop(&stackFunctions);

	instruction = gmalloc(sizeof(tInstruction), free);
	instruction->f = f;
	instruction->variable = var;
	instruction->functionName = name;
	stackInstructionPush(&(topFunction->code), instruction);
}
