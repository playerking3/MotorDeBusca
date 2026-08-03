#include <stdlib.h>
#include <stdio.h>

typedef struct ArvoreNode{
    char* nameDocumento;
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

ArvoreNode *createNode(char* nameDocumento, float score){
    ArvoreNode *novo = malloc(sizeof(ArvoreNode));
    novo->nameDocumento = nameDocumento;
    novo->score = score;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

ArvoreNode *insertNode(ArvoreNode *atual, char* nameDocumento, float score){
    if (atual == NULL){
        return createNode(nameDocumento,score);
    }

    if(score < atual->score){
        atual->esquerda = insertNode(atual->esquerda, nameDocumento,score);
    }else if(score > atual->score){
        atual->direita = insertNode(atual->direita, nameDocumento, score);
    }

    return atual;
}

void insertInTree(BinaryTree *arvore, char* nameDocumento, float score){
    arvore->raiz = insertNode(arvore->raiz, nameDocumento, score);
}


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


void freeNode(ArvoreNode *atual){
    if(atual != NULL){
        freeNode(atual->esquerda);
        freeNode(atual->direita);
        free(atual);
    }
}

void freeTree(BinaryTree *arvore) {
    if (arvore != NULL) {
        freeNode(arvore->raiz);
        free(arvore);
    }
}

