#include <string.h>
#include <stdlib.h>

#define SIZE 70

/*
A pilha indica qual foi o procedimento feito no documento
*/

/*********************************************************/
/**          Estrutura de nos da pilha.                 **/
/*********************************************************/
/*********************************************************/
/**          Struct to model the stack.                 **/
/*********************************************************/
struct StackNode{
    char content[SIZE];
    struct StackNode *next;
};
/*********************************************************/
/**          Descritor da pilha.                        **/
/*********************************************************/
/*********************************************************/
/**          Stack Descriptor.                         **/
/*********************************************************/
typedef struct{
    struct StackNode *head;
    int _size;
} Stack;

/*********************************************************/
/**     Funcao que verifica se a pilha esta vazia.      **/
/*********************************************************/
/*********************************************************/
/**     Function than verify if the stack is empty.     **/
/*********************************************************/
int stackIsEmpty(Stack _stack){
    if(_stack.head == NULL){
        return 1;
    }
    return 0;
}

/*********************************************************/
/**          Funcao que empilha os dados baseado no
            arquivo que esta executando a funcao.       **/
/*********************************************************/
/*********************************************************/
/**          Function than push a log based on the
            actual archive and the operation.           **/
/*********************************************************/
void stackPush(Stack *_stack, char *requisitor, char *content){

    //  Cria novo no
    //  Create a new node
    struct StackNode *newNode = malloc(sizeof(struct StackNode));
    char* aux = malloc(sizeof(char)* (strlen(requisitor) + strlen(content) + 1));
    strcpy(newNode->content, aux);

    //  Se a pilha estiver vazia, coloca como primeiro
    //  If Stack is empty, then put it in first.
    if(stackIsEmpty(*_stack) == 1){
        newNode->next = NULL;
        _stack->head = newNode;
    }else{
        newNode->next = _stack->head;
        _stack->head = newNode;
    }
    _stack->_size++;
}
/*********************************************************/
/**      Funcao que desempilha o dado e o retorna.      **/
/*********************************************************/
/*********************************************************/
/**      Function than pop the data and return it.      **/
/*********************************************************/
char *stackPop(Stack *_stack){
    char* content = malloc(sizeof(char)*SIZE);
    struct StackNode *aux = _stack->head;
    _stack->head = aux->next;
    strcpy(content, aux->content);
    free(aux);
    return content;
}



/*********************************************************/
/**          Funcao que retorna o topo da pilha
            sem demsempilhar.                           **/
/*********************************************************/
/*********************************************************/
/**          Function than return the stack top but
            don't pop it.                               **/
/*********************************************************/
char *stackPeek(Stack _stack){
    if(!stackIsEmpty(_stack)){
        return _stack.head->content;
    }
    return NULL;
}


/*********************************************************/
/**          Funcao que exibe todos os processos
            empilhados ate o atual momento.             **/
/*********************************************************/
/*********************************************************/
/**          Function to print all process already
            pushed to stack.                            **/
/*********************************************************/
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
