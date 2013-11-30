#include "inbuilt_functions.h"

void boolval(void) {
    sVariable * retVal = gmalloc(sizeof(sVariable),free);
    retVal->value = gmalloc(sizeof(variableValue),free);

    sVariable * term = stackVarPop(&stackVariables);

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
    sVariable * retVal = gmalloc(sizeof(sVariable),free);
    retVal->value = gmalloc(sizeof(variableValue),free);

    sVariable * term = stackVarPop(&stackVariables);

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
            if(term->value->stringv[0] == '-') retVal->value->doublev = 0;
            else sscanf(term->value->stringv, "%g", &(retVal->value->doublev));
            break;
    }

    stackVarPush(&stackVariables, retVal);
}

void intval(void) {
    sVariable * retVal = gmalloc(sizeof(sVariable),free);
    retVal->value = gmalloc (sizeof(variableValue),free);

    sVariable * term = stackVarPop(&stackVariables);

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
            if(term->value->stringv[0] == '-') retVal->value->intv = 0;
            else retVal->value->intv = (int) strtol(term->value->stringv, (char **)NULL, 10);
            break;
    }

    stackVarPush(&stackVariables, retVal);
}

void strval(void) {
    sVariable * retVal = gmalloc(sizeof(sVariable),free);
    retVal->value = gmalloc (sizeof(union variableValue),free);

    sVariable * term = stackVarPop(&stackVariables);

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
                strcpy(retVal->value->stringv, "0");
            }
            break;

        case INTEGER:
            retVal->value->stringv = gmalloc(maxChars(term->value->intv), free); //maxChars je v generator.c
            sprintf(retVal->value->stringv,"%d",term->value->intv);
            break;

        case DOUBLE:
            retVal->value->stringv = gmalloc(sizeof(char)*36, free); //max delka double
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
    sVariable * retVal = gmalloc(sizeof(sVariable),free);
    retVal->value = gmalloc(sizeof(variableValue),free);

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
	sVariable * retVal = gmalloc(sizeof(sVariable),free);
    retVal->value = gmalloc (sizeof(variableValue),free);
	retVal->type = INTEGER;
    int i = 0;
    sVariable *term;

    if(!stackVarEmpty(stackVariables))
	{
		for (i = 0; i < stackVariables->top+1 ; i++)
		{
            term = stackVariables->data[i];

            switch(term->type)
            {
                case NULLV: printf("");break;
                case BOOLEAN: term->value->boolv ? printf("1") : printf("");break;
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
    sVariable * retVal = gmalloc(sizeof(sVariable),free);
    retVal->value = gmalloc (sizeof(variableValue),free);

    retVal->type = INTEGER;

    if(stackVariables->data[stackVariables->top]->type != STRING) strval();

    sVariable * str = stackVarPop(&stackVariables);
    retVal->value->intv = strlen(str->value->stringv);

    stackVarPush(&stackVariables, retVal);
}

void get_substring(void) {
	if(stackVariables->data[stackVariables->top]->type != INTEGER) intval();
    sVariable * last = stackVarPop(&stackVariables);
	if(stackVariables->data[stackVariables->top]->type != INTEGER) intval();
    sVariable * first = stackVarPop(&stackVariables);
	if(stackVariables->data[stackVariables->top]->type != STRING) strval();
    sVariable * str = stackVarPop(&stackVariables);

    if((first->value->intv < 0) || (last->value->intv < 0) || (first->value->intv > last->value->intv)
       || (first->value->intv >= (int) strlen(str->value->stringv)) || (last->value->intv > (int) strlen(str->value->stringv)))
        printError(OTHERSERRS, OTHERS);

    sVariable * retVal = gmalloc(sizeof(sVariable),free);
    retVal->value = gmalloc(sizeof(union variableValue),free);
    retVal->type = STRING;
    retVal->value->stringv = gmalloc(sizeof(char)*(last->value->intv - first->value->intv + 2),free);

    strncpy(retVal->value->stringv, ((str->value->stringv)+first->value->intv), last->value->intv - first->value->intv);
    retVal->value->stringv[last->value->intv - first->value->intv+1] = '\0';

    stackVarPush(&stackVariables, retVal);
}

void find_string(void){
    sVariable * retVal = gmalloc(sizeof(sVariable),free);
    retVal->value = gmalloc(sizeof(variableValue),free);

    retVal->type = INTEGER;

	if(stackVariables->data[stackVariables->top]->type != STRING) strval();
    sVariable * substr = stackVarPop(&stackVariables);
	if(stackVariables->data[stackVariables->top]->type != STRING) strval();
    sVariable * str = stackVarPop(&stackVariables);

    retVal->value->intv = IAL_find_string(str->value->stringv, substr->value->stringv);

    stackVarPush(&stackVariables, retVal);
}

void sort_string(void){
    sVariable * retVal = gmalloc(sizeof(sVariable),free);
    retVal->value = gmalloc (sizeof(variableValue),free);

    retVal->type = STRING;

	if(stackVariables->data[stackVariables->top]->type != STRING) strval();

    sVariable * str = stackVarPop(&stackVariables);

    retVal->value->stringv = gmalloc(sizeof(char)*(strlen(str->value->stringv)+1), free);
    strcpy(retVal->value->stringv, str->value->stringv);
    retVal->value->stringv = IAL_sort_string(retVal->value->stringv);

    stackVarPush(&stackVariables, retVal);
}
