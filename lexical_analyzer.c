#include "lexical_analyzer.h"
#include "error.h"

// primarni nastaveni velikosti alokovane pameti pro predavani syntaktickemu
// analyzatoru
int allocateSize=40;

// pomocne priznaky
enum tSymbols
{
	NUMBER,
	CHAR,
};

// vraci TOKEN pokud je klicove slovo, -1 pokud ne
int isKeyWord(char *str)
{
	if (strcmp("while",str)==0) return WHILE;
    if (strcmp("function",str)==0) return FUNCTION;
	if (strcmp("true",str)==0) return BOOL;
	if (strcmp("false",str)==0) return BOOL;
	if (strcmp("if",str)==0) return IF;
	if (strcmp("null",str)==0) return NULLV;
	if (strcmp("return",str)==0) return RETURN;
	if (strcmp("else",str)==0) return ELSE;
    return -1;
}
 
// funkce co prealokuje ukazatel str na dvojnasobnou velikost
// volano v pripade, ze je malo pameti pro predani hodnoty syntax. analyzatoru
// vraci nulu pri uspesne realokaci a 99 v pripade chyby nove alokace
int reallocation (char **str)
{
	allocateSize*=2;
	char *newStr=malloc(allocateSize*sizeof(char));
	if (newStr==NULL) 
	{
		free(*str);
		printError(ALLOCERROR,INTERPRETERROR);
	}
	memcpy(newStr,*str,allocateSize*sizeof(char)/2);
	free(*str);
	*str=newStr;
	return 0;
}

// vlozi znak
void insertChar(int *index, char **content, int c)
{
	if ((*index)==allocateSize-1) reallocation(content); 
			(*content)[(*index)++]=c;
}

// odstrani bile znaky, potom zkousi zda zde nelezi komentar a v kladnem pripade
// odstrani komentar a opet odstrani zbytecne bile znaky
// vraci 0 - odstraneno v poradku
// vraci INVALIDCHAR pokud viceradkovy komentar nema konec 
int comments_and_whtspc(FILE *f)
{
	// odstrani bile znaky
	int c=fgetc(f);
	while (isspace(c)) c=fgetc(f); 
	
	
	int hlpc=fgetc(f);
	
	// jestli je komentar jednoradkovy
	if (c=='/' && hlpc=='/')
	{
		while (c!='\n' && c!=EOF) c=fgetc(f);
		
		if (c==EOF) ungetc(c,f);
		
		while (isspace(c)) c=fgetc(f);
		ungetc(c,f);
		
	}
	else
	// jestli je komentar viceradkovy
	if (c=='/' && hlpc=='*')
	{
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
	return 0;
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
int is_paren_brace(int c)
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
	if (c == '=')  
	{
		c=fgetc(f);
		if (c == '=')
		{
			c=fgetc(f);
			if (c== '=') return TYPEEQUAL;
			else 
			{
				ungetc(c,f);
				return EQUAL;
			}
				
		}
		else 
		{
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
			if (c == '=') return TYPENOTEQUAL;
			else
			{
				ungetc(c,f);
				return NOTEQUAL;
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
int is_begin_or_lesser(FILE *f, int c)
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
	int ec;
	
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
		
		// pokud je nazev promenne klicove slovo, vrat chybovy token
		if ((ec=isKeyWord(*content))==-1) return INVALIDCHAR;
		
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
	
	if (c == '"') // zacatek retezce
	{
		// dokud neni druha " nebo EOF, dava pozor aby tam nebylo \"
		while (((c=fgetc(f))!='"' || hlpc=='\\') && c!=EOF)
		{
			// realokace kvuli nedostatku mista
			insertChar(&index,content,c);
			hlpc=c;
		}
	
		if (c==EOF) return INVALIDCHAR;
	
		insertChar(&index,content,'\0');
		return STRING;
	}
	else return -1;
}


// vraci token najiteho lexemu pripadne chybovy token INVALIDCHAR
int getToken(FILE *f, char **content )
{	
	(*content)[0]='\0';
	int index=0;
	
	int flag,d,ec,c;
	
	// enumator pro specialni skupiny symbolu

	
	// nacte prvni znak v poradi po bilych znacich a mezerach
	if((ec=comments_and_whtspc(f))==INVALIDCHAR) return INVALIDCHAR;
	c=fgetc(f);
	
	// pro EOF
	if (c==EOF) return END;
	
	// aritmeticke operace
	if ((ec=isArithmetic(c))!=-1) return ec;
	
	// strednik, tecka, carka
	if ((ec=isDotSmcComma(c))!=-1) return ec;
	
	// zavorky
	if ((ec=is_paren_brace(c))!=-1) return ec;
	
	// bud jedno, dve, nebo tri rovna se
	if ((ec=isEquating(f,c))!=-1) return ec;
	
	// !== != nebo ! tj chyba
	if ((ec=isNotEqual(f,c))!=-1) return ec;
	
	// >= a >
	if ((ec=isBigger(f,c))!=-1) return ec;
	
	// < , <= , <?php
	if ((ec=is_begin_or_lesser(f,c))!=-1) return ec;
	
	// STRING
	if ((ec=isString(f,c,content))!=-1) return ec;
	
	if ((ec=isVariable(f,c,content))==INVALIDCHAR) return INVALIDCHAR;
	else if ((ec=isVariable(f,c,content))!=-1) return ec;
	
	// pro ostatni, zjisti jestli se jedna o znak nebo o symbol vhodny pro ID
	if (isdigit(c)) flag=NUMBER;
	if (isalpha(c) || c=='_') flag=CHAR;
	(*content)[index++]=c;
	
	// automat pro id, double, int, bool keyword
	switch (flag)
	{
		// bud ID, nebo klicove slovo, nebo bool nebo null
		case CHAR :
			while (isalnum(c=fgetc(f)) || c=='_')
			{
				insertChar(&index,content,c);
			}
			ungetc(c,f);
					
			insertChar(&index,content,'\0');
			
			// pokud je to klicove slovo, vrat spravny token
			if ((ec=isKeyWord(*content))!=-1) return ec;
			
			return ID;
		
		// int nebo double nebo invalidchar
		case NUMBER :
			while (isdigit((c=fgetc(f))))
			{
				insertChar(&index,content,c);
			}
			// pokud narazi na tecku, uz to nemuze byt integer
			if (c=='.')
			{
				insertChar(&index,content,c);
						
				if (!isdigit(c=fgetc(f))) return INVALIDCHAR;
						
				insertChar(&index,content,c);
						
				while (isdigit((c=fgetc(f))))
				{
					insertChar(&index,content,c);
				}
				
				// moznost exponentu
				if (c=='e' || c=='E')
				{
					insertChar(&index,content,c);
							
					c=fgetc(f);
							
					insertChar(&index,content,c);
							
					if (c!='+' && c!='-' && !isdigit(c)) return INVALIDCHAR;
					else 
					{
						// nepovinne -,+
						if (c=='+' || c=='-')
						{
							c=fgetc(f);
							insertChar(&index,content,c);
						}
								
						if (!isdigit(c)) return INVALIDCHAR;	
						while (isdigit((c=fgetc(f))))
						{
							insertChar(&index,content,c);
						}
								
						ungetc(c,f);
								
						insertChar(&index,content,'\0');
								
						return DOUBLE;
					}
				}
				else
				{
					ungetc(c,f);
							
					insertChar(&index,content,'\0');
							
					return DOUBLE;
				}
			}
			else 
			{
				ungetc(c,f);
						
				insertChar(&index,content,'\0');
						
				return INT;
			}
					
		default : return INVALIDCHAR;
	}	
}