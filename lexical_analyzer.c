#include "lexical_analyzer.h"

// CHYBI VYRESIT PROBLEM STRINGU
// BOOL
// PREDAVANI NAZVU ID A HODNOT

int allocateSize=40;

void reallocation (char **str)
{
	allocateSize*=2;
	char *newStr=malloc(allocateSize*sizeof(char));
	memcpy(newStr,*str,allocateSize*sizeof(char)/2);
	free(*str);
	*str=newStr;
}

// vraci token najiteho lexemu pripadne chybovy token
int getToken(FILE *f, char **content )
{

	(*content)[0]='\0';
	int index=0;

	// enumator pro specialni skaly symbolu
	enum tSymbols
	{
		NUMBER,
		CHAR,
	};
	int flag,d;

	// nacte prvni znak v poradi
	int c=fgetc(f);

	// vynecha vsechny bile znaky
	while (isspace(c)) c=fgetc(f);

	// konecny automat
	switch(c)
	{
		// budto se jedna o nejaky typ komentare, nebo deleni
		case '/' :
			c=fgetc(f);
			switch (c)
			{
				//jednoradkovy komentar .. vynecha vse do konce radku
				case '/' :
					while ((c=fgetc(f))!='\n');
					break;

				// viceradkovy komentar, vynecha vse do pristiho */
				case '*' :
					d=fgetc(f);
					c=fgetc(f);
					while (d!='*' || c!='/' )
					{
						d=c;
						c=fgetc(f);
					}
					break;

				// jinak se jednalo o deleni, vrati se o znak zpatky a da token
				default :
					ungetc(c,f);
					return DIVISION;

			}
			break;

		// znaky strednik tecka carka
		case ';' : return SEMICOLON;
		case '.' : return DOT;
		case ',' : return COMMA;

		// aritmeticke operace krome deleni, to je reseno s komentari
		case '-' : return MINUS;
		case '+' : return PLUS;
		case '*' : return TIMES;

		// zavorky
		case '(' : return OPENPAREN;
		case ')' : return CLOSEPAREN;
		case '{' : return OPENBRACE;
		case '}' : return CLOSEBRACE;

		// bud jedno, dve, nebo tri rovna se
		case '=' :
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

		// samotna negace ! neni definovana, cili se jedna o chybu, pokud
		// neni za vykricnikem jedno nebo dve =
		case '!' :
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

		// > nebo >=
		case '>' :
			c=fgetc(f);
			if (c == '=') return BIGGEREQUAL;
			else
			{
				ungetc(c,f);
				return BIGGER;
			}

		// budto se jedna o zacatek <?php
		// nebo o znaminko < ci <=
		case '<' :
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

		// EOF
		case EOF : return END;

		case '"' :
			d='a';
			while (((c=fgetc(f))!='"' || d=='\\') && c!=EOF)
			{
				if (index==allocateSize-1) reallocation(content);
				(*content)[index++]=c;
				d=c;
			}

			if (c==EOF) return END;

			if (index==allocateSize-1) reallocation(content);
			(*content)[index]='\0';
			return STRING;

		case '$' :
			c=fgetc(f);

			if (isalpha(c) || c=='_')
			{
				flag=CHAR;
				(*content)[index++]=c;
			}
			else return INVALIDCHAR;
			while (isalnum(c=fgetc(f)) || c=='_')
			{
				if (index==allocateSize-1) reallocation(content);
				(*content)[index++]=c;
			}
			ungetc(c,f);

			if (index==allocateSize-1) reallocation(content);
			(*content)[index]='\0';

			return VAR;


		//identifikator, bool, double nebo int
		default :
		{
			if (isdigit(c)) flag=NUMBER;
			if (isalpha(c) || c=='_') flag=CHAR;

			(*content)[index++]=c;
			switch (flag)
			{
				// ID nebo bool hodnota nebo nazev fcee
				//VRACET HODNOTU
				case CHAR :
					while (isalnum(c=fgetc(f)) || c=='_')
					{
						if (index==allocateSize-1) reallocation(content); ;
						(*content)[index++]=c;
					}
					ungetc(c,f);

					if (index==allocateSize-1) reallocation(content);
					(*content)[index]='\0';

					return ID;

				// number type
				//VRACET HODNOTU
				case NUMBER :
					while (isdigit((c=fgetc(f))))
					{
						if (index==allocateSize-1) reallocation(content);
						(*content)[index++]=c;
					}
					if (c=='.')
					{
						if (index==allocateSize-1) reallocation(content);
							(*content)[index++]=c;

						if (!isdigit(c=fgetc(f))) return INVALIDCHAR;

						if (index==allocateSize-1) reallocation(content);
						(*content)[index++]=c;

						while (isdigit((c=fgetc(f))))
						{
							if (index==allocateSize-1) reallocation(content);
							(*content)[index++]=c;
						}

						if (c=='e' || c=='E')
						{
							if (index==allocateSize-1) reallocation(content);
							(*content)[index++]=c;

							c=fgetc(f);

							if (index==allocateSize-1) reallocation(content);
							(*content)[index++]=c;

							if (c!='+' && c!='-' && !isdigit(c)) return INVALIDCHAR;
							else
							{
								if (c=='+' || c=='-')
								{
									c=fgetc(f);
									if (index==allocateSize-1) reallocation(content);
									(*content)[index++]=c;
								}

								if (!isdigit(c)) return INVALIDCHAR;
								while (isdigit((c=fgetc(f))))
								{
									if (index==allocateSize-1) reallocation(content);
									(*content)[index++]=c;
								}

								ungetc(c,f);

								if (index==allocateSize-1) reallocation(content); ;
								(*content)[index]='\0';

								return DOUBLE;
							}
						}
						else
						{
							ungetc(c,f);

							if (index==allocateSize-1) reallocation(content); ;
							(*content)[index]='\0';

							return DOUBLE;
						}
					}
					else
					{
						ungetc(c,f);

						if (index==allocateSize-1) reallocation(content); ;
						(*content)[index]='\0';

						return INT;
					}

				default : return INVALIDCHAR;
			}

		}
	}

	return INVALIDCHAR;
}
