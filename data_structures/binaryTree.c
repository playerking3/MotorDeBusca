#include <stdlib.h>
#include <stdio.h>

typedef struct ArvoreNode{
    int idDocumento;
    float score;
    struct ArvoreNode *esquerda;
    struct ArvoreNode *direita;
} ArvoreNode;

typedef struct{
    ArvoreNode *raiz;
}BinaryTree;

BinaryTree *createTree(){
    BinaryTree *arvore = malloc(sizeof(BinaryTree));
    arvore->raiz = NULL;
    return arvore;
}

ArvoreNode *createNode(int idDocumento, float score){
    ArvoreNode *novo = malloc(sizeof(ArvoreNode));
    novo->idDocumento = idDocumento;
    novo->score = score;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

ArvoreNode *insertNode(ArvoreNode *atual, int idDocumento, float score){
    if (atual == NULL){
        return createNode(idDocumento,score);
    }

    if(score < atual->score){
        atual->esquerda = insertNode(atual->esquerda, idDocumento,score);
    }else if(score > atual->score){
        atual->direita = insertNode(atual->direita, idDocumento, score);
    }

    return atual;
}

void insertInTree(BinaryTree *arvore, int idDocumento, float score){
    arvore->raiz = insertNode(arvore,idDocumento, score);
}


void readNodeInOrder(ArvoreNode *atual){
    if(atual != NULL){
        readNodeInOrder(atual->esquerda);
        printf("ID do documento: %d\n Score do documento: %f\n", atual->idDocumento, atual->score);
        readNodeInOrder(atual->direita);
    }
}

void readTreeInOrder(BinaryTree *arvore){
    readNodeInOrder(arvore->raiz);
}

void readNodeReverse(ArvoreNode *atual){
    if(atual != NULL){
        readNodeReverse(atual->direita);
        printf("ID do documento: %d\n Score do documento: %f\n", atual->idDocumento, atual->score);
        readNodeReverse(atual->esquerda);
    }
}

void readTreeReverse(BinaryTree *arvore){
    readNodeReverse(arvore->raiz);
}

void freeTree(BinaryTree *arvore) {
    if (arvore != NULL) {
        freeNode(arvore->raiz);
        free(arvore);
    }
}