#include "ial.h"


void BSTF_Init(sFunction ** node) {
    *node = NULL;
}


sFunction * BSTF_Search(sFunction * node, char * key) {
    if(node != NULL) {
        int compare = strcmp(node->key, key);

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

sFunction* BSTF_Insert(sFunction ** node, char * key) {
    if(*node == NULL) {

        sFunction * tmp;
        if((tmp = malloc(sizeof(sFunction))) != NULL) {
            *node = tmp;
            (*node)->key = key;
            (*node)->lptr = (*node)->rptr = NULL;
            (*node)->elseBranches = NULL;
            (*node)->endIfBranches = NULL;
            (*node)->whileBranches = NULL;
            (*node)->paramNames = NULL;
            (*node)->paramCount = 0;
            BSTV_Init(&(*node)->variables);
            (*node)->code = NULL;

            gadd(*node, BSTF_Dispose);
        }
        else {
            //chyba mallocu
        }
    }
    else {

        int compare = strcmp((*node)->key, key);

        if(compare > 0) {
            BSTF_Insert(&(*node)->rptr, key);
        }
        else if (compare < 0) {
            BSTF_Insert(&(*node)->lptr, key);
        }
    }

    return *node;
}

void BSTF_Dispose(void * node) {
    sFunction * treePointer = (sFunction *) node;

    if(treePointer != NULL) {
        if(treePointer->lptr != NULL) {
            BSTF_Dispose((void *) treePointer->lptr);
        }
        if(treePointer->rptr != NULL) {
            BSTF_Dispose((void *) treePointer->rptr);
        }
        free(treePointer);
        treePointer = NULL;
    }
}

//##############################################################################################

void BSTV_Init(sVariable ** node) {
    *node = NULL;
}


sVariable * BSTV_Search(sVariable * node, char * key) {
    if(node != NULL) {
        int compare = strcmp(node->key, key);

        if(compare == 0) {
            return node;
        }
        else if(compare > 0) {
            return BSTV_Search(node->rptr, key);
        }
        else {
            return BSTV_Search(node->lptr, key);
        }
    }
    return NULL;
}

sVariable* BSTV_Insert(sVariable ** node, char * key) {
    if(*node == NULL) {
        sVariable * tmp;
        if((tmp = malloc(sizeof(sVariable))) != NULL) {
            *node = tmp;
            (*node)->key = key;
            (*node)->lptr = (*node)->rptr = NULL;
            (*node)->defined = false;

            gadd((*node), BSTV_Dispose);
        }
        else {
            //chyba mallocu
        }
    }
    else {

        int compare = strcmp((*node)->key, key);

        if(compare > 0) {
            BSTV_Insert(&(*node)->rptr, key);
        }
        else if (compare < 0) {
            BSTV_Insert(&(*node)->lptr, key);
        }
    }

    return *node;
}

void BSTV_Dispose(void * node) {
    sVariable * treePointer = (sVariable *) node;
    if(treePointer != NULL) {

        if(treePointer->lptr != NULL) {
            BSTV_Dispose(treePointer->lptr);
        }
        if(treePointer->rptr != NULL) {
            BSTV_Dispose(treePointer->rptr);
        }
        free(treePointer);
        treePointer = NULL;
    }
}

char * sort_string (char * str) {
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

int find_string(char * str, char * substr) {
    int sub_lenght = strlen(substr);        // délka hledaného podřetězce
    int str_lenght = strlen(str);           // délka řetězce v němž se hledá
    int position = sub_lenght - 1;          // pozice vyhledávání
    int equal = 1;                          // indikátor nalezení
    int res_pos = -1;                       // výsledná pozice, na které se hledaný řetězec nachází
    int tmp_pos;                            // pomocná pozice pro vyhledávání
    char * pch;                             // pomocná proměnná pro nalezení pozice znaku v hledaném řetězci
    int chr_pos;                            // pozice znaku v hledaném řetezci
    int i;                                  // pomocná proměnná pro cyklus

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
        position += sub_lenght;
    }
    return res_pos;
}
/*
int main( void ) {
    char veta[] = "if you wish to understand others you must";
    char slovo[] = "musten";
    char slovo2[] = "fa";
    char slovo3[] = "alenka";
    char slovo4[] = "mazličekmiláček";
    char slovo5[] = "vašek";
    char slovo6[] = "david";
    char slovo7[] = "huavagahavap";
    char slovo8[] = "hugp";
    char slovo9[] = "huaahrhrřp";
    //
    //

    tBSTNodePtr root;
    tBSTNodePtr node;
    BST_Init(&root);

    BST_Insert(&root, slovo, veta);
    BST_Insert(&root, slovo2, veta);
    BST_Insert(&root, slovo3, veta);
    BST_Insert(&root, slovo4, veta);
    BST_Insert(&root, slovo5, veta);

    node = BST_Search(root, slovo3);
    if(node != NULL)


    BST_Insert(&root, slovo6, veta);

    node = BST_Search(root, slovo);
    if(node != NULL)


    BST_Insert(&root, slovo7, veta);
    BST_Insert(&root, slovo8, veta);

    node = BST_Search(root, "hup");
    if(node != NULL)


    BST_Insert(&root, slovo9, veta);

    node = BST_Search(root, slovo9);
    if(node != NULL)


    BST_Dispose(&root);
    return 0;
}*/
