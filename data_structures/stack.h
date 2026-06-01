#include <string.h>
#include <stdlib.h>

#define SIZE 12
/*
A pilha indica qual foi o procedimento feito no documento
*/

// Estrutura de nós da pilha
struct StackNode{
    char content[SIZE];
    struct StackNode *next;
};

// Descritor da pilha
typedef struct{
    struct StackNode *head;
    int _size;
} Stack;

//Verifica se a pilha está vazia
int stackIsEmpty(Stack _stack){
    if(_stack.head == NULL){
        return 1;
    }
    return 0;
}

// Empilha dados
void push(Stack *_stack, char *content){
    // Cria novo nó
    struct StackNode *newNode = malloc(sizeof(struct StackNode));
    strcpy(newNode->content, content);

    // Se a pilha estiver vazia, coloca como primeiro
    if(stackIsEmpty(*_stack) == 1){
        newNode->next = NULL;
        _stack->head = newNode;
    }else{
        newNode->next = _stack->head;
        _stack->head = newNode;
    }
}

//Desempilha dados
char *pop(Stack *_stack){
    char* content = malloc(sizeof(char)*SIZE);
    struct StackNode *aux = _stack->head;
    _stack->head = aux->next;
    strcpy(content, aux->content);
    free(aux);
    return content;
}

char *peek(Stack _stack){
    if(stackIsEmpty(_stack) == 0){
        return _stack.head->content;
    }
    return NULL;
}
