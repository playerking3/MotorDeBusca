
// Ponteiro opaco para a árvore (esconde os detalhes de implementação)
typedef struct BinaryTree BinaryTree;

// Aloca e inicializa uma nova árvore binária de busca
BinaryTree *createTree(void);

// Insere um novo documento na árvore respeitando a ordem do score
void insertInTree(BinaryTree *arvore, int idDocumento, float score);

// Imprime os documentos em ordem crescente de score
void readTreeInOrder(const BinaryTree *arvore);

// Imprime os documentos em ordem decrescente de score
void readTreeReverse(const BinaryTree *arvore);

// Libera toda a memória alocada pela árvore
void freeTree(BinaryTree *arvore);
