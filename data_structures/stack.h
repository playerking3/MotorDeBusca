#include <string.h>
#include <stdlib.h>

#define SIZE 70

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
void stackPush(Stack *_stack, char *requisitor, char *content){
    // Cria novo nó
    struct StackNode *newNode = malloc(sizeof(struct StackNode));
    char* aux = malloc(sizeof(char)* (strlen(requisitor) + strlen(content) + 1));
    strcpy(newNode->content, aux);

    // Se a pilha estiver vazia, coloca como primeiro
    if(stackIsEmpty(*_stack) == 1){
        newNode->next = NULL;
        _stack->head = newNode;
    }else{
        newNode->next = _stack->head;
        _stack->head = newNode;
    }
    _stack->_size++;
}

//Desempilha dados
char *stackPop(Stack *_stack){
    char* content = malloc(sizeof(char)*SIZE);
    struct StackNode *aux = _stack->head;
    _stack->head = aux->next;
    strcpy(content, aux->content);
    free(aux);
    return content;
}

char *stackPeek(Stack _stack){
    if(!stackIsEmpty(_stack)){
        return _stack.head->content;
    }
    return NULL;
}

void printStack(Stack _stack){
    struct StackNode* aux;
    if(!stackIsEmpty(_stack)){
        printf("%d\n", _stack._size);
        aux = _stack.head;
        for(int i = _stack._size; i > 0; i--){
            printf("Processo %d: %s\n", i, aux->content);
            aux = aux->next;
        }
    }else
        printf("Nenhum processo realizado!\n");
}
