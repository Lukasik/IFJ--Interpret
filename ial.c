#include "ial.h"


void BSTF_Init(tFunction ** node) {
    *node = NULL;
}


tFunction * BSTF_Search(tFunction * node, char * key) {
    if(node != NULL) {
        int compare = strcmp(key, node->key);

        if(compare == 0) {
            return node;
        }
        else if(compare > 0) {
            return BSTF_Search(node->rptr, key);
        }
        else {
            return BSTF_Search(node->lptr, key);
        }
    }
    return NULL;
}

tFunction* BSTF_Insert(tFunction ** node, char * key) {
    if(*node == NULL) {

        tFunction * tmp;
        if((tmp = malloc(sizeof(tFunction))) != NULL) {
            *node = tmp;
            (*node)->key = malloc(strlen(key)+1);
            if((*node)->key == NULL) printError(ALLOCERROR, INTERPRETERROR);
            memcpy((*node)->key, key, strlen(key)+1);
            (*node)->lptr = (*node)->rptr = NULL;
            (*node)->paramNames = gmalloc(sizeof(sString), free);
            stackStringInit((*node)->paramNames, 5);
            (*node)->codePosition = 0;
            BSTV_Init(&(*node)->variables);
            (*node)->code = gmalloc(sizeof(sInstruction), free);
            stackInstructionInit((*node)->code, 50);
            return *node;
        }
        else {
            printError(ALLOCERROR, INTERPRETERROR);
            return NULL;
        }
    }
    else {

        int compare = strcmp(key, (*node)->key);

        if(compare > 0) {
            return BSTF_Insert(&(*node)->rptr, key);
        }
        else if (compare < 0) {
            return BSTF_Insert(&(*node)->lptr, key);
        }
        else
        {
            printError(FUNCTIONEXISTS, FUNCTIONDEFINITIONERROR);
            return NULL;
        }
    }
}

void BSTF_Dispose(void * node) {
    tFunction * treePointer = (tFunction *) node;

    if(treePointer != NULL) {
        if(treePointer->lptr != NULL) {
            BSTF_Dispose((void *) treePointer->lptr);
        }
        if(treePointer->rptr != NULL) {
            BSTF_Dispose((void *) treePointer->rptr);
        }
        BSTV_Dispose(treePointer->variables);
        free(treePointer->key);
        free(treePointer);
        treePointer = NULL;
    }
}

//##############################################################################################

void BSTV_Init(tVariable ** node) {
    *node = NULL;
}


tVariable * BSTV_Search(tVariable * node, char * key) {
    if(node != NULL) {
        int compare = strcmp(key, node->key);

        while(compare != 0)
        {
            if(compare > 0)
            {
                node = node->rptr;
            }
            else
            {
                node = node->lptr;
            }

            if(node == NULL) return NULL;

            compare = strcmp(key, node->key);
        }

        return node;

    }
    return NULL;
}

tVariable* BSTV_Insert(tVariable ** node, char * key) {
    if (*node==NULL) // vklada se prvni prvek
    {
        tVariable* newElement= gmalloc (sizeof (tVariable), free);
        newElement->lptr=newElement->rptr=NULL;
        newElement->key = gmalloc(strlen(key)+1, free);
        memcpy(newElement->key, key, strlen(key)+1);
        newElement->defined = false;
        newElement->value = (tVariableValue*) gmalloc(sizeof(tVariableValue), free);
        newElement->value->stringv = NULL;
        newElement->usable = false;

        *node=newElement;
        return newElement;
    }


    tVariable* tmp=*node;

    // neprazdny strom, hledame jestli prvek jiz neexistuje
    while (strcmp(tmp->key, key) != 0)
    {
        if (strcmp(tmp->key, key) > 0 && tmp->lptr!=NULL) tmp=tmp->lptr;
        else if (strcmp(tmp->key, key) < 0 && tmp->rptr!=NULL) tmp=tmp->rptr;
        else break;
    }

    // pokud neexistuje, pridame jej
    if (strcmp(tmp->key, key) != 0)
    {
        tVariable* newElement= gmalloc (sizeof (tVariable), free);
        newElement->lptr = newElement->rptr = NULL;
        newElement->key = gmalloc(strlen(key)+1, free);
        memcpy(newElement->key, key, strlen(key)+1);
        newElement->defined = false;
        newElement->value = (tVariableValue*) gmalloc(sizeof(tVariableValue), free);
        newElement->value->stringv = NULL;
        newElement->usable = false;

        if (strcmp(tmp->key, key) > 0) tmp->lptr=newElement;
        else tmp->rptr=newElement;

        return newElement;
    }

    return tmp;
    

    // if(*node == NULL) {
    //     tVariable * tmp;
    //     if((tmp = gmalloc(sizeof(tVariable),free)) != NULL) {
    //         *node = tmp;
    //         (*node)->key = gmalloc(strlen(key)+1, free);
    //         if((*node)->key == NULL) printError(ALLOCERROR, INTERPRETERROR);
    //         memcpy((*node)->key, key, strlen(key)+1);
    //         (*node)->lptr = (*node)->rptr = NULL;
    //         (*node)->defined = false;
    //         (*node)->value = (tVariableValue*) gmalloc(sizeof(tVariableValue), free);
    //         if((*node)->value == NULL) printError(ALLOCERROR, INTERPRETERROR);
    //         (*node)->value->stringv = NULL;
    //         // (*node)->type = NULLV;
    //     }
    //     else {
    //         printError(ALLOCERROR, INTERPRETERROR);
    //     }
    // }
    // else {

    //     int compare = strcmp(key, (*node)->key);

    //     if(compare > 0) {
    //         return BSTV_Insert(&(*node)->rptr, key);
    //     }
    //     else if (compare < 0) {
    //         return BSTV_Insert(&(*node)->lptr, key);
    //     }
    // }

    // return *node;
}

void BSTV_Dispose(void * node) {
    tVariable * treePointer = (tVariable *) node;
    if(treePointer != NULL) {
        if(treePointer->lptr != NULL) {
            BSTV_Dispose(treePointer->lptr);
        }
        if(treePointer->rptr != NULL) {
            BSTV_Dispose(treePointer->rptr);
        }
        // DEBUG("dispose");SAS
        //TODO zjistit proč nefunguje bez garbage až bude čas
        // if(treePointer->value != NULL && treePointer->type == STRING) free(treePointer->value->stringv);
        // if(treePointer->value != NULL) free(treePointer->value);
        // free(treePointer->key);
        // free(treePointer);
        treePointer = NULL;
    }
}

char * IAL_sort_string (char * str) {
    int left = 0;
    int right = strlen(str) - 1;
    int stack[strlen(str)];
    int topStack = -1;
    int i, j, pivot;
    char tmp;

    stack[++topStack] = left;
    stack[++topStack] = right;

    while(topStack >= 0) {
        right = stack[topStack--];
        left = stack[topStack--];

        while(left<right) {
            /* PARTITION */
            i = left;
            j = right;
            pivot = str[(i+j) / 2];

            while(i < j) {
                while(str[i] < pivot) { i++; }
                while(str[j] > pivot) { j--; }

                if(i<=j) {
                    tmp = str[i];
                    str[i++] = str[j];
                    str[j--] = tmp;
                }
            }
            /* END OF PARTITION */

           stack[++topStack] = i;
           stack[++topStack] = right;
           right = j;
        }
    }
    return str;
}

int IAL_find_string(char * str, char * substr) {
    int sub_lenght = strlen(substr);        // délka hledaného podřetězce
    int str_lenght = strlen(str);           // délka řetězce v němž se hledá
    int position = sub_lenght - 1;          // pozice vyhledávání
    int equal = 1;                          // indikátor nalezení
    int res_pos = -1;                       // výsledná pozice, na které se hledaný řetězec nachází
    int tmp_pos;                            // pomocná pozice pro vyhledávání
    char * pch;                             // pomocná proměnná pro nalezení pozice znaku v hledaném řetězci
    int chr_pos;                            // pozice znaku v hledaném řetezci
    int i;                                  // pomocná proměnná pro cyklus

    if(sub_lenght == 0) return 0;

    while(position < str_lenght) {
        equal = 1;
        if(substr[sub_lenght-1] == str[position]) {
            tmp_pos = position-1;
            for(i = sub_lenght - 2; i >= 0; i--, tmp_pos--) {
                if(substr[i] != str[tmp_pos]) {
                    equal = 0;
                    break;
                }
            }
            if(equal == 1) {
                res_pos = tmp_pos + 1;
                break;
            }
        }
        else if((pch = strchr(substr, str[position])) != NULL) {
            tmp_pos = position+1;
            chr_pos = pch - substr;
            for(i = chr_pos + 1; i <= sub_lenght - 1; i++, tmp_pos++) {
                //
                if(substr[i] != str[tmp_pos]) {
                    equal = 0;
                    break;
                }
            }
            if(equal == 1) {
                tmp_pos = position-1;
                for(i = chr_pos - 1; i >= 0; i--, tmp_pos--) {
                    //
                    if(substr[i] != str[tmp_pos]) {
                        equal = 0;
                        break;
                    }
                }
            }
            if(equal == 1) {
                res_pos = tmp_pos + 1;
                break;
            }
        }
        ++position;
    }
    return res_pos;
}
