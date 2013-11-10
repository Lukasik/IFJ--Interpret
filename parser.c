#include "parser.h"

int isOperator(tToken *token)
{
	return
		token->name == PLUS ||
		token->name == MINUS ||
		token->name == TIMES ||
		token->name == DOT ||
		token->name == DIVISION;
}

int isOperand(tToken *token)
{
	return isType(token) || token->name == VAR;
}

int isType(tToken *token)
{
	return
		token->name == INT ||
		token->name == DOUBLE ||
		token->name == STRING ||
		(token->name == KEYWORD && (strcmp(token->content, "true") == 0 || strcmp(token->content, "false") == 0 || strcmp(token->content, "null") == 0));
}

int isComparsionOperator(tToken *token)
{
	return
		token->name == BIGGER ||
		token->name == LESSER ||
		token->name == BIGGEREQUAL ||
		token->name == LESSEREQUAL ||
		token->name == EQUAL ||
		token->name == NOTEQUAL;
}

// v isCommand zjisti ze je keyword
// pokud keyword neni while returns ISNT
// pokud chyba returns SYNERR
// pokud ok, vraci ISOK
int isWhile(FILE *f, tToken *t)
{
	DEBUG("kontrola keywordu while");
	if (strcmp(t->content,"while")!=0) return ISNT;

	getToken(f, t);
	DEBUG("(");
	if (t->name!=OPENPAREN) return SYNERR;

	getToken(f, t);
	DEBUG("je porovnání?");
	if (isExpression(f,t, false)!=ISOK) return SYNERR;

	//DEBUG(")");
	//if (t->name!=CLOSEPAREN) return SYNERR;
//spatna vec
	getToken(f, t);
	DEBUG("je blok?");
	if (isBlock(f, t)==ISOK) return ISOK;

	return SYNERR;
}

// zjisti jestli je keyword if
// overi podminku a blok
// musi tu byt else!
int isIf(FILE *f,tToken *t)
{
	DEBUG("kontrola if keywordu");
	if (strcmp(t->content,"if")!=0) return ISNT;

	getToken(f, t);
	DEBUG("(");
	if (t->name!=OPENPAREN) return SYNERR;

	getToken(f, t);
	DEBUG("je porovnání?");
	if ((isExpression(f,t, false))!=ISOK) return SYNERR;

	// DEBUG(")");
	//if (t->name!=CLOSEPAREN) return SYNERR;
//spatna vec
	getToken(f, t);
	DEBUG("je blok?");
	if ((isBlock(f, t))!=ISOK) return SYNERR;

	getToken(f, t);
	DEBUG("je else?");
	if (t->name!=KEYWORD || strcmp("else",t->content)!=0) return SYNERR;

	getToken(f, t);
	DEBUG("je blok?");
	if (isBlock(f, t)!=ISOK) return SYNERR;

	return ISOK;
}

// vraci ISOK pokud je to return vyraz nebo return;
int isReturn (FILE *f, tToken *t)
{
	DEBUG("return");
	if (strcmp("return",t->content)!=0) return ISNT;

	getToken(f, t);
	DEBUG("; nebo výraz?");
	if (t->name==SEMICOLON) return ISOK;
	else if ((isExpression(f,t, true))==ISOK) return ISOK;

	return SYNERR;
}


// je prirazeni / vraci ISOK nebo SYNERR
int isAssign (FILE *f, tToken *t)
{
	DEBUG("je proměnná?");
	if(t->name != VAR) return SYNERR;

	BSTV_Insert(&(actualFunction[0]->variables), t->content);

	getToken(f, t);
	DEBUG("=?");
	if(t->name != ASSIGN) return SYNERR;

	getToken(f, t);
	DEBUG("volání fce nebo výraz?");
	if(isExpression(f, t, true) == ISOK) return ISOK;
	else if(isFunctionCall(f, t) == ISOK) return ISOK;

	return SYNERR;
}

// isExpression
// vraci ISOK, ISNT nebo SYNERR
int isExpression (FILE *f, tToken *t, bool semicolonEnd)
{
	int parens = 0;

	while(t->name == OPENPAREN)
	{
		DEBUG("požírám (");
		++parens;
		printf("parens: %d\n", parens);
		getToken(f, t);
	}

	DEBUG("je operand?");
	if(isOperand(t))
	{
		getToken(f, t);
		DEBUG("je ; a 0x ) nebo operátor?");
		if(((t->name == SEMICOLON && semicolonEnd) || (t->name == CLOSEPAREN && !semicolonEnd)) && parens == 0)
		{
			// getToken(f, t);
			return ISOK;
		}
		else if(isOperator(t) || isComparsionOperator(t))
		{
			DEBUG("první doOperation");
			return doOperation(f, t, &parens, semicolonEnd);
		}

	}

	return SYNERR;
}

int doOperation(FILE *f, tToken *t, int *parens, bool semicolonEnd)
{
	getToken(f, t);
	DEBUG("je (");
	while(t->name == OPENPAREN)
	{
		DEBUG("žeru jednu (");
		++*parens;
		printf("parens: %d\n", *parens);
		getToken(f, t);
	}

	DEBUG("je operand?");
	if(isOperand(t))
	{
		getToken(f, t);
		DEBUG("; a sedí závorky nebo je ) nebo operátor");
		if((
			t->name == SEMICOLON && semicolonEnd && *parens == 0) ||
			(t->name == CLOSEPAREN && !semicolonEnd && *parens == 0))
		{
			getToken(f, t);
			return ISOK;
		}
		else if((t->name == CLOSEPAREN || isOperator(t)) || isComparsionOperator(t))
		{
			DEBUG("je ), operator");
			while(t->name == CLOSEPAREN)
			{
				DEBUG("žeru jednu )");
				--(*parens);
				printf("parens: %d\n", *parens);
				getToken(f, t);
			}

			DEBUG("je ; a sedí závorky nebo je operace?");
			if((t->name == SEMICOLON && semicolonEnd && *parens == 0) || (!semicolonEnd && *parens == -1))
			{
				if(!semicolonEnd) getToken(f, t);
				return ISOK;
			}
			else if(isOperator(t) || isComparsionOperator(t))
			{
				DEBUG("je operátor, rekurze");
				return doOperation(f, t, parens, semicolonEnd);
			}
		}
	}

	return SYNERR;
}

int isComparsion(FILE *f, tToken *t)
{
	DEBUG("je porovnání?");
	if(isOperand(t))
	{
		getToken(f, t);
		DEBUG("je operátor porovnání?");
		if(isComparsionOperator(t))
		{
			getToken(f, t);
			DEBUG("je operand?");
			if(isOperand(t))
			{
				return ISOK;
			}
		}
	}

	return SYNERR;
}

int isFunctionCall(FILE *f, tToken *t)
{
	DEBUG("je identifikátor?");
	if(t->name != ID) return ISNT;

	getToken(f, t);
	DEBUG("je (?");
	if(t->name != OPENPAREN) return SYNERR;

	getToken(f, t);
	DEBUG("je )?");
	if(t->name == CLOSEPAREN)
	{
		getToken(f ,t);
		DEBUG("je ;?");
		if(t->name == SEMICOLON) return ISOK;
		return SYNERR;
	}

	DEBUG("je operand?");
	if(isOperand(t))
	{
		DEBUG("je operand nebo ,?");
		while(isOperand(t))
		{
			getToken(f, t);
			if(t->name == COMMA)
			{
				DEBUG("je čárka");
				getToken(f, t);
				if(t->name == CLOSEPAREN) return SYNERR;
			}
		}

		DEBUG("je )?");
		if(t->name == CLOSEPAREN)
		{
			getToken(f ,t);
			DEBUG("je ;?");
			if(t->name == SEMICOLON) return ISOK;
			return SYNERR;
		}
		DEBUG("není )");
	}

	return SYNERR;
}

// zjisti jestli je command, vraci ISOK a SYNERR
// pouziva iswhile isif isreturn
int isCommand(FILE *f, tToken *t)
{
	if (t->name==KEYWORD)
	{
		DEBUG("je keyword");
		if (isWhile(f,t)==ISOK) return ISOK;
		else if (isIf(f,t)==ISOK) return ISOK;
		else if (isReturn(f,t)==ISOK) return ISOK;
	}
	else if (t->name==SEMICOLON)
	{
		DEBUG("je ;");
		return ISOK;
	}
	else if (t->name==VAR && isAssign(f,t) == ISOK)
	{
		DEBUG("je přiřazení");
		return ISOK;
	}

	return SYNERR;
}


// zjisti jestli se jedna o blok, pokud ano, vyhodnoti a vraci 0
// jinak vraci ISNT pokud neni blok a SYNERR pokud je v nem chyba
int isBlock(FILE *f, tToken *t)
{
	// neni blok, vrat ISNT
	DEBUG("{");
	if (t->name!=OPENBRACE) return ISNT;

	// precti dalsi token
	getToken(f, t);

	// dokud je prikaz
	DEBUG("is command");
	while (isCommand(f,t)==ISOK) getToken(f, t);

	// pokud neni ukoncena slozena zavorka, vraci SYNERR
	DEBUG("}");
	if (t->name == CLOSEBRACE) return ISOK;

	return SYNERR;
}


// funkce zjisti, jestli se jedna o funci, pokud ne vraci ISNT, pokud ano,
// zkontroluje jeji spravne sepsani a vraci ISOK pokud ok a SYNERR pokud syntaxError
int isFunction (FILE *f, tToken *t)
{
	// nejedna se o klicove slovo function -> vrati ISNT
	DEBUG("keyword");
	if (t->name!=KEYWORD || strcmp(t->content,"function")!=0)
		return ISNT;

	// jednalo se o klicove slovo function
	getToken(f, t);

	// jedna se o ID?
	DEBUG("id");
	printf("%d\n", t->name);
	if (t->name!=ID) return SYNERR;

	//TODO: přidání funkce do stromu funkcí a nastavení fce jako aktuální
	//TODO: pokud je funkce uz definovana tak chyba 5
	actualFunction[1] = actualFunction[0];
	if(BSTF_Search(functionTree, t->content))
	{
		printError(FUNCTIONEXISTS, FUNCTIONDEFINITIONERROR);
	}

	actualFunction[0] = BSTF_Insert(&functionTree, t->content);

	// jedna se o ( ?
	getToken(f, t);
	DEBUG("(");
	if (t->name!=OPENPAREN) return SYNERR;

	getToken(f, t);
	int whatNow=0;
	// dokud neni )
	DEBUG("parametry");
	while (t->name!=CLOSEPAREN)
	{
		// ma prijit promenna
		if (whatNow % 2 == 0)
		{
			if (t->name==VAR)
			{
				//TODO přidání parametru do struktury funkce
				//TODO vytvoření prvku stromu s názvem proměné
				whatNow++;
			}
			else return SYNERR;
		}
		else // ma prijit carka
		{
			if (t->name == COMMA)
			{
				whatNow++;
			}
			else return SYNERR;
		}

		getToken(f, t);
	}

	// uz narazil na )
	// pokud whatNow==0 tak function id ()
	// pokud whatNow mod 2 =1 function id (x) nebo (x,x) atd ..
	DEBUG("správný počet parametrů a čárek");
	if (whatNow==0 || whatNow%2 ==1)
	{
		// nacte token a pokud je potom block, vse je OK - vraci 0
		// jinak vraci SYNERR do funkce main
		getToken(f, t);
		DEBUG("lezu do bloku");
		if (isBlock(f,t)!=ISOK) return SYNERR;
		//TODO: zrušení aktuálnosti fce (nastavit na main)
		else
		{
			actualFunction[0] = actualFunction[1];
			return ISOK;
		}
	}

	// pokud whatnow mod 2=0 a whatNow neni 0 function id (x,) nebo (x,x,) atd.
	return SYNERR;
}



int main (int argc, char *argv[])
{
	int exitCode = 0;
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

	BSTF_Init(&functionTree);
	actualFunction[0] = BSTF_Insert(&functionTree, "1");

	// typ struktury tokenu
	getToken(f, t);

	// pokud neni prvni token begin, je to chyba
	if (t->name != BEGIN) printError(SYNTAXERR,SYNTAXERROR);

	getToken(f, t);
	// dokud neni konec programu, zkousi jestli se jedna o povolene veci
	// tj bud funkce, nebo nejaky z prikazu
	while (t->name!=END)
	{
		exitCode = isFunction(f,t);
		printf("%d\n", t->name);
		printf("ec: %d\n", exitCode);
		// syntaxerrory mohou byt prejaty z ostatnich funkci
		if (exitCode==SYNERR) printError(SYNTAXERR,SYNTAXERROR);
		else if (exitCode==ISNT)
				if (isCommand(f,t)!=ISOK)
					// blbe pojmenovani, ale jak jinak :-(
					printError(SYNTAXERR,SYNTAXERROR);

		getToken(f, t);
	}


	gfree(t->content);
	gfree(functionTree);
	gfree(t);
	fclose(f);

	for (int i = 0; i < gArraySize; ++i)
	{
		if(gArray[i] == NULL) continue;
		printf("%p\n", (void*) gArray[i]->pointer);
	}
	gfreeAll();

	printf("ok\n");

	return 0;
}
