#include <string.h>
#include <stdlib.h>

#define SIZE 12
/*
A pilha indica qual foi o procedimento feito no documento
*/

// Estrutura de nós da pilha
struct Node{
    char content[SIZE];
    struct node *next;
};

// Descritor da pilha
typedef struct{
    struct Node *head;
    int size;
} Stack;

//Verifica se a pilha está vazia
int isEmpty(Stack stack){
    if(stack.head == NULL){
        return 1;
    }
    return 0;
}

// Empilha dados
void push(Stack *stack, char *content){
    // Cria novo nó
    struct Node *newNode = malloc(sizeof(struct Node));
    strcpy(newNode->content, content);

    // Se a pilha estiver vazia, coloca como primeiro
    if(isEmpty(*stack) == 1){
        newNode->next = NULL;
        stack->head = newNode;
    }else{
        newNode->next = stack->head;
        stack->head = newNode;
    }
}

//Desempilha dados
char *pop(Stack *stack){
    char content[SIZE];
    struct Node *aux = stack->head;
    stack->head = aux->next;
    strcpy(content, aux->content);
    free(aux);
    return content;
}

char *peek(Stack stack){
    if(isEmpty(stack) == 0){
        return stack.head->content;
    }
    return NULL;
}