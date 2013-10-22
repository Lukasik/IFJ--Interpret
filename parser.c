#include "parser.h"


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
	if (isComparsion(f,t)!=ISOK) return SYNERR;

	getToken(f, t);
	DEBUG(")");
	if (t->name!=CLOSEPAREN) return SYNERR;

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
	if ((isComparsion(f,t))!=ISOK) return SYNERR;

	getToken(f, t);
	DEBUG(")");
	if (t->name!=CLOSEPAREN) return SYNERR;

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
	else if ((isExpression(f,t))==ISOK) return ISOK;

	return SYNERR;
}


// je prirazeni / vraci ISOK nebo SYNERR
//TODO kontrolovat středník?
int isAssign (FILE *f, tToken *t)
{
	DEBUG("je proměnná?");
	if(t->name != VAR) return SYNERR;

	getToken(f, t);
	DEBUG("=?");
	if(t->name != ASSIGN) return SYNERR;

	getToken(f, t);
	DEBUG("volání fce nebo výraz?");
	if(isExpression(f, t) == ISOK) return ISOK;
	else if(isFunctionCall(f, t) == ISOK) return ISOK;

	return SYNERR;
}

// isExpression
// vraci ISOK, ISNT nebo SYNERR
int isExpression (FILE *f, tToken *t)
{
	int parens = 0;
	DEBUG("požírám (");
	while(t->name == OPENPAREN)
	{
		++parens;
		getToken(f, t);
	}

	DEBUG("je operand?");
	if(isOperand(t))
	{
		getToken(f, t);
		DEBUG("je ; a 0x ) nebo operátor?");
		if(t->name == SEMICOLON && parens == 0)
		{
			return ISOK;
		}
		else if(isOperator(t))
		{
			return doOperation(f, t, &parens);
		}

	}

	return SYNERR;
}

int doOperation(FILE *f, tToken *t, int *parens)
{

	getToken(f, t);
	DEBUG("je (");
	while(t->name == OPENPAREN)
	{
		DEBUG("žeru jednu (");
		++*parens;
		getToken(f, t);
	}

	DEBUG("je operand?");
	if(isOperand(t))
	{
		getToken(f, t);
		DEBUG("; a sedí závorky nebo je ) nebo operátor");
		if(t->name == SEMICOLON && *parens == 0)
		{
			return ISOK;
		}
		else if((t->name == CLOSEPAREN || isOperator(t)))
		{
			DEBUG("požířám )");
			while(t->name == CLOSEPAREN)
			{
				DEBUG("žeru jednu )");
				--(*parens);
				getToken(f, t);
			}

			DEBUG("je ; a sedí závorky nebo je operace?");
			if(t->name == SEMICOLON && *parens == 0)
			{
				return ISOK;
			}
			else if(isOperator(t))
			{
				DEBUG("je operátor, rekurze");
				return doOperation(f, t, parens);
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
	if(t->name == CLOSEPAREN) return ISOK;
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
		if(t->name == CLOSEPAREN) return ISOK;
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
		else return ISOK;
	}
	// pokud whatnow mod 2=0 a whatNow neni 0 function id (x,) nebo (x,x,) atd.
	return SYNERR;
}



int main (int argc, char *argv[])
{
	int exitCode = 0;
	tToken *t = malloc(sizeof(tToken));

	if(t == NULL) printError(ALLOCERROR, INTERPRETERROR);

	t->content = malloc(40);
	if(t->content == NULL) printError(ALLOCERROR, INTERPRETERROR);
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

	printf("ok\n");

	return 0;
}
