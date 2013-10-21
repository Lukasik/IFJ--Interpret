include "parser.h"

int isOperator(tToken *token)
{
	return
		token->name == PLUS ||
		token->name == MINUS ||
		token->name == TIMES ||
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
		token->name == BOOL ||
		token->name == NULLV;
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
	bool result = false;

	if (strcmp(t->content,"while")!=0) return ISNT;

	result = getToken(f, t);
	if (!result || t->name!=OPENPAREN) return SYNERR;

	result = getToken(f, t);
	if (!result || isCompare(f,t)!=ISOK) return SYNERR;

	result = getToken(f, t);
	if (!result || t->name!=CLOSEPAREN) return SYNERR;

	result = getToken(f, t);
	if (result && isBlock(f, t)==ISOK) return ISOK;

	return SYNERR;
}

// zjisti jestli je keyword if
// overi podminku a blok
// musi tu byt else!
int isIf(FILE *f,tToken *t)
{
	bool result = false;

	if (strcmp(t->content,"if")!=0) return ISNT;

	result = getToken(f, t);
	if (!result || t->name!=OPENPAREN) return SYNERR;

	result = getToken(f, t);
	if (!result || (ec=isCompare(f,t))!=ISOK) return SYNERR;

	result = getToken(f, t);
	if (!result || t->name!=CLOSEPAREN) return SYNERR;

	result = getToken(f, t);
	if (!result || (ec=isBlock)!=ISOK) return SYNERR;

	result = getToken(f, t);
	if (!result || t->name!=KEYWORD || strcmp("else",t->content)!=0) return SYNERR;

	result = getToken(f, t);
	if (!result || isBlock(f, t)!=ISOK) return SYNERR;

	return ISOK;
}

// vraci ISOK pokud je to return vyraz nebo return;
int isReturn (FILE *f, tToken *t)
{
	bool result = false;

	if (strcmp("return",t->content)!=0) return ISNT;

	result = getToken(f, t);
	if (result && t->name==SEMICOLON) return ISOK;
	else if (result && (ec=isExpression(f,t))==ISOK) return ISOK;

	return SYNERR;
}


// je prirazeni / vraci ISOK nebo SYNERR
//TODO kontrolovat středník?
int isAssign (FILE *f, tToken *t)
{
	bool result = false;

	if(t->name != VAR) return SYNERR;

	result = getToken(f, t);
	if(!result || t->name != ASSIGN) return SYNERR;

	result = getToken(f, t);
	if(result && isExpression(f, t) == ISOK) return ISOK;
	else if(result && isFunctionCall(f, t) == ISOK) return ISOK;

	return SYNERR;
}

// isExpression
// vraci ISOK, ISNT nebo SYNERR
int isExpression (FILE *f, tToken *t)
{
	bool result = false;
	int parens = 0;

	while(t->name == OPENPAREN)
	{
		++parens;
		result = getToken(f, t);
	}

	if(result && isOperand(t))
	{
		result = getToken(f, t);

		if(result && t->name == SEMICOLON && parens == 0)
		{
			return ISOK;
		}
		else if(result && isOperator(t))
		{
			return doOperation(f, t, &parens);
		}

	}

	return SYNERR;
}

int doOperation(FILE *f, tToken *t, int *parens)
{
	bool result = false;

	result = getToken(f, t);

	while(t->name == OPENPAREN)
	{
		++*parens;
		result = getToken(f, t);
	}

	if(result && isOperand(t))
	{
		result = getToken(f, t);

		if(result && t->name == SEMICOLON && *parens == 0)
		{
			return ISOK;
		}
		else if(result && t->name == CLOSEBRACE || isOperator(t))
		{
			while(t->name == CLOSEBRACE)
			{
				--*parens;
				result = getToken(f, t);
			}

			if(result && t->name == SEMICOLON && *parens == 0)
			{
				return ISOK;
			}
			else if(result && isOperator(t))
			{
				return doOperation(f, t, parens);
			}
		}
	}

	return SYNERR;
}

int isComparsion(FILE *f, tToken *t)
{
	bool result = false;

	if(isOperand(t))
	{
		result = getToken(f, t)

		if(result && isComparsionOperator(t))
		{
			result = getToken(f);

			if(result && isOperand(t))
			{
				return ISOK;
			}
		}
	}

	return SYNERR;
}

int isFunctionCall(FILE *f, tToken *t)
{
	bool result = false;

	if(t->name != ID) return ISNT;

	result = getToken(f, t);
	if(!result && t->name != OPENPAREN) return SYNERR;

	result = getToken(f, t);
	if(result && t->name == OPENPAREN) return ISOK;
	if(isOperand(t))
	{
		while(isOperand(t) || t->name == COMMA)
		{
			result = getToken(f, t);
		}

		if(t->name == CLOSEBRACE) return ISOK;
	}

	return SYNERR;
}

// zjisti jestli je command, vraci ISOK a SYNERR
// pouziva iswhile isif isreturn
int isCommand(FILE *f, tToken *t)
{
	int ec;
	if (t->name==KEYWORD)
	{
		if ((ec=isWhile(f,t))==ISOK)	return ISOK;
		else if (ec==SYNERR) return SYNERR;
		else if ((ec=isIf(f,t))==ISOK) return ISOK;
		else if (ec==SYNERR) return SYNERR;
		else if ((ec=isReturn(f,t))==ISOK) return ISOK;
		else if (ec==SYNERR) return SYNERR;
		else return SYNERR;
	}
	else if (t->name==SEMICOLON)
	{
		return ISOK;
	}
	else if (t->name==VAR)
	{
		ec=isAssign(f,t);
		if (ec!=ISOK) return SYNERR;
		else return ISOK;
	}

	return SYNERR;
}


// zjisti jestli se jedna o blok, pokud ano, vyhodnoti a vraci 0
// jinak vraci ISNT pokud neni blok a SYNERR pokud je v nem chyba
int isBlock(FILE *f, tToken *t)
{
	bool result = false;
	// neni blok, vrat ISNT
	if (t->name!=OPENBRACE) return ISNT;

	int ec;

	// precti dalsi token
	result = getToken(f, t);

	// dokud je prikaz
	while (result && (ec=isCommand(f,t))==ISOK);

	// pokud syntaxerror v commandu vrati SYNERR svemu volajicimu
	if (ec==SYNERR || !result) return SYNERR;

	// pokud neni ukoncena slozena zavorka, vraci SYNERR
	if (t->name != CLOSEBRACE) return SYNERR;
	else
	{
		return ISOK; // vse ok, vraci ISOK
	}

	return SYNERR;
}


// funkce zjisti, jestli se jedna o funci, pokud ne vraci ISNT, pokud ano,
// zkontroluje jeji spravne sepsani a vraci ISOK pokud ok a SYNERR pokud syntaxError
int isFunction (FILE *f, tToken *t)
{
	bool result = false;
	// nejedna se o klicove slovo function -> vrati ISNT
	if (t->name!=KEYWORD || strcmp(t->content,"function")!=0)
		return ISNT;

	// jednalo se o klicove slovo function
	result = getToken(f, t);

	// jedna se o ID?
	if (!result || t->name!=ID) return SYNERR;

	// jedna se o ( ?
	if (!result || t->name!=OPENPAREN) return SYNERR;

	int whatNow=0;
	// dokud neni )
	while (t->name!=CLOSEPAREN)
	{
		// ma prijit promenna
		if (whatNow % 2 == 0)
		{
			if (t->name==VAR)
			{
				whatNow++;
			}
			else return SYNERR;
		}
		else // ma prijit carka
		{
			if (t->name == COMMA)
			{
				whatnow++;
			}
			else return SYNERR;
		}
	}

	// navratovy kod
	int ec;

	// uz narazil na )
	// pokud whatNow==0 tak function id ()
	// pokud whatNow mod 2 =1 function id (x) nebo (x,x) atd ..

	if (whatNow==0 || whatNow%2 ==1)
	{
		// nacte token a pokud je potom block, vse je OK - vraci 0
		// jinak vraci SYNERR do funkce main
		result = getToken(f, t);
		if (!result || (ec=isBlock(f,t))!=ISOK) return SYNERR;
		else return ISOK;
	}
	// pokud whatnow mod 2=0 a whatNow neni 0 function id (x,) nebo (x,x,) atd.
	return SYNERR;
}



int main (int argc, char *argv[])
{
	tToken *t = malloc(sizeof(tToken));

	if(t == NULL) printError(ALLOCERROR, INTERPRETERROR);
	// pokud spatny pocet parametru
	if (argc!=2) printError(PARAMSERROR,INTERPRETERROR);

	// pokus o otevreni zdrojaku
	FILE *f=fopen(argv[1],"r");
	// pripad nepodareneho otevreni
	if (f==NULL) printError(SOURCECODEERR,INTERPRETERROR);

	// kod otevren

	// pokud nezacina < je to chyba
	int c=fgetc(f);
	if (c!='<') printError(SYNTAXERR,SYNTAXERROR);
	else ungetc (c,f);

	// typ struktury tokenu
	tToken *t=getToken(f);

	// pokud neni prvni token begin, je to chyba
	if (t->name != BEGIN) printError(SYNTAXERR,SYNTAXERROR);

	result = getToken(f, t);

	// navratovy kod
	int ec;

	// dokud neni konec programu, zkousi jestli se jedna o povolene veci
	// tj bud funkce, nebo nejaky z prikazu
	while (result && t->name!=END)
	{
		// syntaxerrory mohou byt prejaty z ostatnich funkci
		if ((ec=isFunction(f,t))==SYNERR) printError(SYNTAXERR,SYNTAXERROR);
		else if ((ec=isFunction(f,t))==ISNT)
				if ((ec=isCommand(f,t))!=ISOK)
					// blbe pojmenovani, ale jak jinak :-(
					printError(SYNTAXERR,SYNTAXERROR);

		result = getToken(f, t);
	}

	return 0;
}
