#include "inbuilt_functions.h"

void boolval(void) {
    tVariable * retVal = gmalloc(sizeof(tVariable),free);
    retVal->value = gmalloc(sizeof(tVariableValue),free);

    tVariable * term = stackVarPop(&stackVariables);

    retVal->type = BOOLEAN;

    switch(term->type) {
        case NULLV:
            retVal->value->boolv = false;
            break;

        case BOOLEAN:
            retVal->value->boolv = term->value->boolv;
            break;

        case INTEGER:
            if(term->value->intv == 0)
                retVal->value->boolv = false;
            else
                retVal->value->boolv = true;
            break;

        case DOUBLE:
            if(term->value->doublev == 0.0)
                retVal->value->boolv = false;
            else
                retVal->value->boolv = true;
            break;

        case STRING:
            if(!strcmp(term->value->stringv, ""))
                retVal->value->boolv = false;
            else
                retVal->value->boolv = true;
            break;
    }

    stackVarPush(&stackVariables, retVal);
}

void doubleval(void) {
    tVariable * retVal = gmalloc(sizeof(tVariable),free);
    retVal->value = gmalloc(sizeof(tVariableValue),free);
    int index = 0;
    char* str;

    tVariable * term = stackVarPop(&stackVariables);

    retVal->type = DOUBLE;

    switch(term->type) {
        case NULLV:
            retVal->value->doublev = 0.0;
            break;

        case BOOLEAN:
            if(term->value->boolv)
                retVal->value->doublev = 1.0;
            else
                retVal->value->doublev = 0.0;
            break;

        case INTEGER:
            retVal->value->doublev = (double)term->value->intv;
            break;

        case DOUBLE:
            retVal->value->doublev = term->value->doublev;
            break;

        case STRING:
            str = term->value->stringv;

            while(isspace(*str)) ++str;

            if(!isdigit(*str))
            {
                retVal->value->doublev = 0.0;
                break;
            }

            while(isdigit(str[index])) index++;

            if(str[index] == '.')
            {
                if(!isdigit(str[++index]))
                    printError(RETYPEERR, RETYPE);
                while(isdigit(str[index])) ++index;
            }

            if(tolower(str[index]) == 'e')
            {
                ++index;
                if(!isdigit(str[index]))
                {
                    if(str[index] != '+' && str[index] != '-')
                    {
                        printError(RETYPEERR, RETYPE);
                    }
                    else
                    {
                        ++index;
                        if(!isdigit(str[index])) printError(RETYPEERR, RETYPE);
                    }
                }
            }

            sscanf(term->value->stringv, "%lf", &(retVal->value->doublev));
            break;
    }

    stackVarPush(&stackVariables, retVal);
}

void intval(void) {
    tVariable * retVal = gmalloc(sizeof(tVariable),free);
    retVal->value = gmalloc (sizeof(tVariableValue),free);
    char*str;
    tVariable * term = stackVarPop(&stackVariables);

    retVal->type = INTEGER;

    switch(term->type) {
        case NULLV:
            retVal->value->intv = 0;
            break;

        case BOOLEAN:
            if(term->value->boolv)
                retVal->value->intv = 1;
            else
                retVal->value->intv = 0;
            break;

        case INTEGER:
            retVal->value->intv = term->value->intv;
            break;

        case DOUBLE:
            retVal->value->intv = (int)term->value->doublev;
            break;

        case STRING:
            str = term->value->stringv;

            while(isspace(*str)) ++str;
            
            if(str[0] == '-') retVal->value->intv = 0;
            else retVal->value->intv = (int) strtol(str, (char **)NULL, 10);
            break;
    }

    stackVarPush(&stackVariables, retVal);
}

void strval(void) {
    tVariable * retVal = gmalloc(sizeof(tVariable),free);
    retVal->value = gmalloc (sizeof(union tVariableValue),free);

    tVariable * term = stackVarPop(&stackVariables);

    retVal->type = STRING;

    switch(term->type) {
        case NULLV:
            retVal->value->stringv = gmalloc(1*sizeof(char), free);
            strcpy(retVal->value->stringv, "");
            break;

        case BOOLEAN:
            if(term->value->boolv) {
                retVal->value->stringv = gmalloc(2*sizeof(char), free);
                strcpy(retVal->value->stringv, "1");
            }
            else {
                retVal->value->stringv = gmalloc(1*sizeof(char), free);
                strcpy(retVal->value->stringv, "");
            }
            break;

        case INTEGER:
            retVal->value->stringv = gmalloc(maxChars(term->value->intv), free); //maxChars je v generator.c
            sprintf(retVal->value->stringv,"%d",term->value->intv);
            break;

        case DOUBLE:
            retVal->value->stringv = gmalloc(sizeof(char)*36, free); //max delka double
            // printf("double: %g\n", term->value->doublev);
            sprintf(retVal->value->stringv,"%g",term->value->doublev);
            break;

        case STRING:
            retVal->value->stringv = gmalloc((1+strlen(term->value->stringv))*sizeof(char), free);
            strcpy(retVal->value->stringv, term->value->stringv);
            break;
    }

    stackVarPush(&stackVariables, retVal);
}

void get_string(void) {
    tVariable * retVal = gmalloc(sizeof(tVariable),free);
    retVal->value = gmalloc(sizeof(tVariableValue),free);

    int c, i = 0, size = 100;
	retVal->type = STRING;
    retVal->value->stringv = gmalloc(sizeof(char)*size,free);

    while((c = getchar()) != '\n') {
        if(c == EOF)
            break;
        if(i+1>=size)
            grealloc((void **) &(retVal->value->stringv), &size, sizeof(char));

        (retVal->value->stringv)[i++] = (char)c;
    }

    (retVal->value->stringv)[i] = '\0';

    stackVarPush(&stackVariables, retVal);
}

void put_string(void) {
	tVariable * retVal = gmalloc(sizeof(tVariable),free);
    retVal->value = gmalloc (sizeof(tVariableValue),free);
	retVal->type = INTEGER;
    int i = 0;
    tVariable *term;

    if(!stackVarEmpty(stackVariables))
	{
		for (i = 0; i < stackVariables->top+1 ; i++)
		{
            term = stackVariables->data[i];

            switch(term->type)
            {
                case BOOLEAN: if(term->value->boolv) printf("1");break;
                case INTEGER:printf("%d",term->value->intv);break;
                case DOUBLE:printf("%g",term->value->doublev);break;
                case STRING:printf("%s", term->value->stringv);break;
            }
		}
	}

    retVal->value->intv = i;
    stackVariables->top = -1;
    stackVarPush(&stackVariables, retVal);
}

void strlength(void) {
    tVariable * retVal = gmalloc(sizeof(tVariable),free);
    retVal->value = gmalloc (sizeof(tVariableValue),free);

    retVal->type = INTEGER;

    if(stackVariables->data[stackVariables->top]->type != STRING) strval();

    tVariable * str = stackVarPop(&stackVariables);
    retVal->value->intv = strlen(str->value->stringv);

    stackVarPush(&stackVariables, retVal);
}

void get_substring(void) {
	if(stackVariables->data[stackVariables->top]->type != INTEGER) intval();
    tVariable * last = stackVarPop(&stackVariables);
	if(stackVariables->data[stackVariables->top]->type != INTEGER) intval();
    tVariable * first = stackVarPop(&stackVariables);
	if(stackVariables->data[stackVariables->top]->type != STRING) strval();
    tVariable * str = stackVarPop(&stackVariables);

    if((first->value->intv < 0) || (last->value->intv < 0) || (first->value->intv > last->value->intv)
       || (first->value->intv >= (int) strlen(str->value->stringv)) || (last->value->intv > (int) strlen(str->value->stringv)))
        printError(OTHERSERRS, OTHERS);

    tVariable * retVal = gmalloc(sizeof(tVariable),free);
    retVal->value = gmalloc(sizeof(union tVariableValue),free);
    retVal->type = STRING;
    retVal->value->stringv = gmalloc(sizeof(char)*(last->value->intv - first->value->intv + 2),free);

    strncpy(retVal->value->stringv, ((str->value->stringv)+first->value->intv), last->value->intv - first->value->intv);
    retVal->value->stringv[last->value->intv - first->value->intv+1] = '\0';

    stackVarPush(&stackVariables, retVal);
}

void find_string(void){
    tVariable * retVal = gmalloc(sizeof(tVariable),free);
    retVal->value = gmalloc(sizeof(tVariableValue),free);

    retVal->type = INTEGER;

	if(stackVariables->data[stackVariables->top]->type != STRING) strval();
    tVariable * substr = stackVarPop(&stackVariables);
	if(stackVariables->data[stackVariables->top]->type != STRING) strval();
    tVariable * str = stackVarPop(&stackVariables);

    retVal->value->intv = IAL_find_string(str->value->stringv, substr->value->stringv);

    stackVarPush(&stackVariables, retVal);
}

void sort_string(void){
    tVariable * retVal = gmalloc(sizeof(tVariable),free);
    retVal->value = gmalloc (sizeof(tVariableValue),free);

    retVal->type = STRING;

	if(stackVariables->data[stackVariables->top]->type != STRING) strval();

    tVariable * str = stackVarPop(&stackVariables);

    retVal->value->stringv = gmalloc(sizeof(char)*(strlen(str->value->stringv)+1), free);
    strcpy(retVal->value->stringv, str->value->stringv);
    retVal->value->stringv = IAL_sort_string(retVal->value->stringv);

    stackVarPush(&stackVariables, retVal);
}
