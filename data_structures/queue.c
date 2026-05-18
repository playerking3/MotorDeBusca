#include<stdlib.h>
#include<string.h>

// Tamanho maximo dos nomes dos arquivos
#define MAX_FILE 20

// Estrutura dos nós da fila
struct Node{
    char content[MAX_FILE];
    struct Node *next;
};

// Descritor da fila
typedef struct{
    struct Node *head;
    struct Node *tail;  
} Queue;

// Verifica se a fila está vazia
int isEmpty(Queue queue){
    if(queue.head == NULL && queue.tail == NULL){
        return 1;
    }
    return 0;
}

// Adiciona nós ao descritor da fila
void enqueue(Queue *queue, char *docFile){
    // cria um novo nó
    struct Node *newNode = malloc(sizeof(struct Node));
    strcpy(newNode->content, docFile);
    newNode->next = NULL;

    // Verifica se a fila é vazia, caso for adiciona como primeiro elemento;
    if(isEmpty(*queue) == 0){
        queue->head->next = newNode;
        queue->head = newNode;
    }else{
        queue->head = newNode;
        queue->tail = newNode;
    }
    
}

// Tira o primeiro elemento da fila e retorna seu conteúdo
char *dequeue(Queue *queue){
    char fileName[MAX_FILE];
    struct Node *aux;
    if(isEmpty(*queue) == 0){
        strcpy(fileName, queue->tail->content);
        aux = queue->tail;
        if(queue->tail->next == NULL){ 
            free(aux);
            queue->head = NULL;
            queue->tail = NULL;
        }else{
            queue->tail = aux->next;
            free(aux);
        }
        return fileName;
    }
    return NULL;
}

// Apenas apresenta o conteúdo do primeiro elemento da fila
char *peek(Queue queue){
    if(isEmpty(queue) == 0){
        return queue.tail->content;
    }
    return NULL;
}