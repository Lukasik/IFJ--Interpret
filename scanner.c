#include "scanner.h"

// primarni nastaveni velikosti alokovane pameti pro predavani syntaktickemu
// analyzatoru
int allocateSize=40; //TODO přidat jako položku tokenu
FILE *f;
// pomocne priznaky
enum tSymbols
{
	NUMBER,
	CHAR,
};


bool exponent(int *index, char** content, int *c)
{
	insertChar(index, content, *c);

	*c = fgetc(f);

	if(*c == '+' || *c == '-')
	{
		insertChar(index, content, *c);
		*c = fgetc(f);
	}

	if(isdigit(*c))
	{
		*c = digits(index, content, *c);
		insertChar(index, content, '\0');
		return true;
	}

	// ungetc(c, f);
	return false;

}

int digits(int *index, char** content, int c)
{
	insertChar(index, content,c);

	while (isdigit((c=fgetc(f))))
	{
		insertChar(index, content,c);
	}

	return c;
}


// vraci TOKEN pokud je klicove slovo, -1 pokud ne
int isKeyWord(char *str)
{
	if (strcmp("while",str)==0) return WHILE;
    if (strcmp("function",str)==0) return FUNCTION;
	if (strcmp("true",str)==0) return BOOLEAN;
	if (strcmp("false",str)==0) return BOOLEAN;
	if (strcmp("if",str)==0) return IF;
	if (strcmp("null",str)==0) return NULLV;
	if (strcmp("return",str)==0) return RETURN;
	if (strcmp("else",str)==0) return ELSE;
    return -1;
}

// vlozi znak
void insertChar(int *index, char **content, int c)
{
	if ((*index)==allocateSize-1) grealloc((void**) content, &allocateSize, sizeof(char));

	(*content)[(*index)++]=c;
}

// odstrani bile znaky, potom zkousi zda zde nelezi komentar a v kladnem pripade
// odstrani komentar a opet odstrani zbytecne bile znaky
// vraci 0 - odstraneno v poradku
// vraci INVALIDCHAR pokud viceradkovy komentar nema konec
int CommentsAndWhitespaces(FILE *f)
{

	int isComment=0;

	// odstrani bile znaky
	int c=fgetc(f);
	while (isspace(c)) c=fgetc(f);


	int hlpc=fgetc(f);

	// jestli je komentar jednoradkovy
	if (c=='/' && hlpc=='/')
	{
		isComment=1;
		while (c!='\n' && c!=EOF) c=fgetc(f);

		if (c==EOF) ungetc(c,f);

		while (isspace(c)) c=fgetc(f);
		ungetc(c,f);

	}
	else
	// jestli je komentar viceradkovy
	if (c=='/' && hlpc=='*')
	{
		isComment=1;

		hlpc=fgetc(f);
	    c=fgetc(f);

		// hleda konec komentare
		while (hlpc!='*' || c!='/')
		{
			hlpc=c;
			c=fgetc(f);

			// pokud nenaslo konec komentare ale EOF, jedna se o chybu
			if (c==EOF) return INVALIDCHAR;
		}

		// odstraneni prebytecnych bilych znaku za komentarem
		c=fgetc(f);
		while (isspace(c)) c=fgetc(f);

		ungetc(c,f);
	}
	else
	{
		ungetc(hlpc,f);
		ungetc(c,f);
	}
	return isComment;
}

// vrati kod konkretni Aritmeticke operace nebo -1 pokud se o aritm. op. nejedna
int isArithmetic (int c)
{
	switch (c)
	{
		case '-' : return MINUS;
		case '+' : return PLUS;
		case '*' : return TIMES;
		case '/' : return DIVISION;

		default: return -1;
	}
}

// vrati kod stredniku, tecky, carky nebo -1 pokud se nejedna ani o jedno z nich
int isDotSmcComma(int c)
{
	switch (c)
	{
		case ';' : return SEMICOLON;
		case '.' : return DOT;
		case ',' : return COMMA;

		default : return -1;
	}
}

// vraci kod zavorek nebo -1
int isParenBrace(int c)
{
	switch (c)
	{
		case '(' : return OPENPAREN;
		case ')' : return CLOSEPAREN;
		case '{' : return OPENBRACE;
		case '}' : return CLOSEBRACE;

		default : return -1;
	}
}

// prirazeni, porovnani nebo typove porovnani nebo -1
// =			==				===
int isEquating (FILE *f, int c)
{
	int d; // pomocna promenna
	if (c == '=')
	{
		c=fgetc(f);
		d=fgetc(f);
		if (c == '=' && d == '=') return EQUAL;
		else
		{
			ungetc(d,f);
			ungetc(c,f);
			return ASSIGN;
		}
	}
	else return -1;
}

// vraci token pro typovou nerovnost, nerovnost, chybu - tj vykricnik, protoze
// IFJ13 nema operator negace (!) a nebo -1
int isNotEqual(FILE *f,int c)
{
	if ( c == '!')
	{
		c=fgetc(f);
		if (c == '=')
		{
			c=fgetc(f);
			if (c == '=') return NOTEQUAL;
			else
			{
				ungetc(c,f);
				return INVALIDCHAR;
			}
		}
		else
		{
			ungetc(c,f);
			return INVALIDCHAR;
		}
	}
	else return -1;
}

// vraci token znamenek > a >= nebo -1
int isBigger(FILE *f, int c)
{
	if (c == '>')
	{
		c=fgetc(f);
		if (c == '=') return BIGGEREQUAL;
		else
		{
			ungetc(c,f);
			return BIGGER;
		}
	}
	else return -1;
}

// vraci tokeny pro <, <= a <?php
int isBeginOrLesser(FILE *f, int c)
{
	if (c == '<')
	{
		c=fgetc(f);
		switch (c)
		{
			case '?' :
				if (
					(c=fgetc(f))=='p'
				     &&
				    (c=fgetc(f))=='h'
				     &&
				    (c=fgetc(f))=='p'
				     &&
				    (isspace((c=fgetc(f))))
				   ) return BEGIN;
				else return INVALIDCHAR;

			case '=': return LESSEREQUAL;

			default:
				ungetc(c,f);
				return LESSER;
		}
	}
	else return -1;
}

// Vraci token VAR pokud je vse vporadku, invalidchar char pokud se promenna
// jmenuje stejne jako klicove slovo jinak -1
int isVariable(FILE *f,int c, char **content)
{
	int index=0;

	if (c == '$')
	{
		c=fgetc(f);

		// nazev musi zacinat znakem nebo podtrzitkem
		if (isalpha(c) || c=='_')
		{
			(*content)[index++]=c;
		}
		else return INVALIDCHAR;
		while (isalnum(c=fgetc(f)) || c=='_')
		{
			insertChar(&index,content,c);
		}
		ungetc(c,f);
		insertChar(&index,content,'\0');

		return VAR;
	}
	else return -1;
}

// token pro STRING --- muze dojit k chybe, pokud neni osetreno
// ze string muze byt pozapomenut ukoncen, potom konci cteni znaku ve stringu
// EOFem a vraci se INVALIDCHAR, jinak STRING nebo -1
int isString (FILE *f, int c, char **content)
{
	int hlpc='a';
	int index=0;
	int discard=0;

	if (c == '"') // zacatek retezce
	{
		// dokud neni druha " nebo EOF, dava pozor aby tam nebylo \"
		while (((c=fgetc(f))!='"' || hlpc=='\\') && c!=EOF)
		{
			if (c<32 || (c=='$' && hlpc!='\\')) discard=1;

			insertChar(&index,content,c);
			hlpc=c;
		}

		if (c==EOF) return INVALIDCHAR;

		insertChar(&index,content,'\0');
		if (discard==0) return STRING;
		else return INVALIDCHAR;
	}
	else return -1;
}

void getToken(FILE *f, tToken *t)
{
	bool result = findToken(f, t);

	if(!result || t->name == INVALIDCHAR)
	{
		printError(LEXICALERR, LEXICALERROR);
	}

	//TODO: garbage collector
}

// vraci token najiteho lexemu pripadne chybovy token INVALIDCHAR
bool findToken(FILE *f, tToken *t)
{
	t->content[0] = '\0';
	int index=0;
	int flag = -1,ec,c;

	t->name = UNINITIALIZED;
	// enumator pro specialni skupiny symbolu


	// nacte prvni znak v poradi po bilych znacich a mezerach
	while((ec=CommentsAndWhitespaces(f))==1)
	{
		if (ec == INVALIDCHAR)
		{
			t->name = INVALIDCHAR;
		}
	}

	c = fgetc(f);

	if (c==EOF) t->name = END; // pro EOF
	else if ((ec=isArithmetic(c))!=-1) t->name = ec; // aritmeticke operace
	else if ((ec=isDotSmcComma(c))!=-1) t->name = ec; // strednik, tecka, carka
	else if ((ec=isParenBrace(c))!=-1) t->name = ec; // zavorky
	else if ((ec=isEquating(f,c))!=-1) t->name = ec; // bud jedno, dve, nebo tri rovna se
	else if ((ec=isNotEqual(f,c))!=-1) t->name = ec; // !== != nebo ! tj chyba
	else if ((ec=isBigger(f,c))!=-1) t->name = ec; // >= a >
	else if ((ec=isBeginOrLesser(f,c))!=-1) t->name = ec; // < , <= , <?php
	else if ((ec=isString(f,c,&(t->content)))!=-1) t->name = STRING; // STRING
	else if ((ec=isVariable(f,c,&(t->content)))==INVALIDCHAR) t->name = INVALIDCHAR;
	else if (ec!=-1) t->name = ec;
	else if (isdigit(c)) flag=NUMBER; // pro ostatni, zjisti jestli se jedna o znak nebo o symbol vhodny pro ID
	else if (isalpha(c) || c=='_') flag=CHAR;

	if(t->name != UNINITIALIZED && flag == -1)
	{
		return true;
	}

	// automat pro id, double, int, bool keyword
	switch (flag)
	{
		// bud ID, nebo klicove slovo, nebo bool nebo null
		case CHAR :
			insertChar(&index,&(t->content),c);
			while (isalnum(c=fgetc(f)) || c=='_')
			{
				insertChar(&index,&(t->content),c);
			}
			ungetc(c,f);

			insertChar(&index,&(t->content),'\0');

			// pokud je to klicove slovo, vrat spravny token
			if ((ec=isKeyWord(t->content))!=-1)
			{
				t->name = ec;
				return true;
			}
			else
			{
				t->name = ID;
				return true;
			}

		// int nebo double nebo invalidchar
		case NUMBER :
			c = digits(&index, &(t->content), c);

			if(c == '.')
			{
				c = digits(&index, &(t->content), c);

				if(tolower(c) == 'e')
				{
					if(exponent(&index, &(t->content), &c))
					{
						ungetc(c, f);
						t->name = DOUBLE;
						return true;
					}
					else
					{
						t->name = INVALIDCHAR;
						return false;
					}
				}
				else
				{
					ungetc(c, f);
					insertChar(&index, &(t->content), '\0');
					t->name = DOUBLE;
					return true;
				}
			}
			else if(tolower(c) == 'e')
			{
				if(exponent(&index, &(t->content), &c))
				{
					ungetc(c, f);
					t->name = DOUBLE;
					return true;
				}
				else
				{
					t->name = INVALIDCHAR;
					return false;
				}
			}

			ungetc(c, f);
			insertChar(&index, &(t->content), '\0');
			t->name = INTEGER;
			return true;


		default : return false;
	}
}

