#include <stdlib.h>
#include <stdio.h>

/*********************************************************/
/**          Estrutura que contém o nó da arvore        **/
/*********************************************************/
/*********************************************************/
/**          Struct that contains the tree node       **/
/*********************************************************/
typedef struct ArvoreNode{
    char* nameDocumento;
    float score;
    struct ArvoreNode *esquerda;
    struct ArvoreNode *direita;
} ArvoreNode;

/*********************************************************/
/**          Estrutura que contém o a arvore em sí      **/
/*********************************************************/
/*********************************************************/
/**          Struct that contains the tree itself       **/
/*********************************************************/
typedef struct{
    ArvoreNode *raiz;
}BinaryTree;


/*********************************************************/
/**          Criação da arvore vazia                    **/
/*********************************************************/
/*********************************************************/
/**          Creation of a empty tree                   **/
/*********************************************************/
BinaryTree *createTree(){
    BinaryTree *arvore = malloc(sizeof(BinaryTree));
    arvore->raiz = NULL;
    return arvore;
}

/*********************************************************/
/**          Criação do nó vazio                        **/
/*********************************************************/
/*********************************************************/
/**          Creation of a empty node                   **/
/*********************************************************/
ArvoreNode *createNode(char* nameDocumento, float score){
    ArvoreNode *novo = malloc(sizeof(ArvoreNode));
    novo->nameDocumento = nameDocumento;
    novo->score = score;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

/*********************************************************/
/**   insere os dados em um nó e os organiza na arvore  **/
/*********************************************************/
/*********************************************************/
/**          Insertion of the data in a node 
             and insertion inside the tree              **/
/*********************************************************/
ArvoreNode *insertNode(ArvoreNode *atual, char* nameDocumento, float score){
    if (atual == NULL){
        return createNode(nameDocumento,score);
    }

    if(score < atual->score){
        atual->esquerda = insertNode(atual->esquerda, nameDocumento,score);
    }else{ // Caso empate o score, também irá para a direita
        atual->direita = insertNode(atual->direita, nameDocumento, score);
    }

    return atual;
}

/*********************************************************/
/**          Faz a atualização da arvore                **/
/*********************************************************/
/*********************************************************/
/**          Updating the tree                          **/
/*********************************************************/
void insertInTree(BinaryTree *arvore, char* nameDocumento, float score){
    arvore->raiz = insertNode(arvore->raiz, nameDocumento, score);
}

/*********************************************************/
/**         Leitura recursiva da arvore em ordem        **/
/*********************************************************/
/*********************************************************/
/**    Recursive tree reading, order left to right      **/
/*********************************************************/
void readNodeInOrder(ArvoreNode *atual){
    if(atual != NULL){
        readNodeInOrder(atual->esquerda);
        printf("Nome do documento: %s\n Score do documento: %f\n", atual->nameDocumento, atual->score);
        readNodeInOrder(atual->direita);
    }
}

void readTreeInOrder(BinaryTree *arvore){
    readNodeInOrder(arvore->raiz);
}

/*********************************************************/
/**     Leitura recursiva da arvore em ordem reversa    **/
/*********************************************************/
/*********************************************************/
/**        recursive tree reading in reverse order      **/
/*********************************************************/
void readNodeReverse(ArvoreNode *atual){
    if(atual != NULL){
        readNodeReverse(atual->direita);
        printf("Nome do documento: %s\n Score do documento: %f\n", atual->nameDocumento, atual->score);
        readNodeReverse(atual->esquerda);
    }
}

void readTreeReverse(BinaryTree *arvore){
    readNodeReverse(arvore->raiz);
}

/*********************************************************/
/**        Liberação do espaço de memória da arvore     **/
/*********************************************************/
/*********************************************************/
/**          Free tree from memory                      **/
/*********************************************************/
void freeNode(ArvoreNode *atual){
    if(atual != NULL){
        freeNode(atual->esquerda);
        freeNode(atual->direita);
        free(atual);
        atual = NULL;
    }
}

void freeTree(BinaryTree **arvore) {
    if (arvore != NULL) {
        freeNode((*arvore)->raiz);
        free(*arvore);
        *arvore = NULL;
    }
}

