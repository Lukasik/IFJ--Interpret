/* Struktura uzlu binárního stromu */
typedef struct tBSTNode {
    char * key;
    char * data;
    struct tBSTNode * lptr;
    struct tBSTNode * rptr;
} *tBSTNodePtr;


/* Prototypy funkcí */
void BST_Init(tBSTNodePtr * node);
tBSTNodePtr BST_Search(tBSTNodePtr node, char * key);
void BST_Insert(tBSTNodePtr * node, char * key, char * data);
void BST_Dispose(tBSTNodePtr * node);
/*void BST_Delete(tBSTNode * node, char * key);
tBSTNode * BST_FindMin(tBSTNode * node);*/
char * sort_string(char * str);
int find_string(char * str, char * substr);
