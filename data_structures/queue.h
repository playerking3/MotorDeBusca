#include<stdlib.h>
#include<string.h>

// Tamanho maximo dos nomes dos arquivos
#define MAX_FILE 20

// Estrutura dos nós da fila
struct FileNode{
    char content[MAX_FILE];
    struct FileNode *next;
};

// Descritor da fila
typedef struct{
    struct FileNode *head;
    struct FileNode *tail;
} Queue;

// Verifica se a fila está vazia
int fileQueueIsEmpty(Queue _queue){
    if(_queue.head == NULL && _queue.tail == NULL){
        return 1;
    }
    return 0;
}

// Adiciona nós ao descritor da fila
void fileEnqueue(Queue *_queue, char *docFile){

    // cria um novo nó
    struct FileNode *newFileNode = malloc(sizeof(struct FileNode));
    strcpy(newFileNode->content, docFile);
    newFileNode->next = NULL;

    // Verifica se a fila é vazia, caso for adiciona como primeiro elemento;
    if(fileQueueIsEmpty(*_queue)){
        _queue->head = newFileNode;
        _queue->tail = newFileNode;
    }else{
        _queue->head->next = newFileNode;
        _queue->head = newFileNode;
    }

}

// Tira o primeiro elemento da fila e retorna seu conteúdo
char* fileDequeue(Queue *_queue){
    char* fileName = malloc(sizeof(char)*MAX_FILE);
    struct FileNode *aux;
    if(!fileQueueIsEmpty(*_queue)){
        strcpy(fileName, _queue->tail->content);
        aux = _queue->tail;
        if(_queue->tail->next == NULL){
            free(aux);
            _queue->head = NULL;
            _queue->tail = NULL;
        }else{
            _queue->tail = aux->next;
            free(aux);
        }
        return fileName;
    }
    return NULL;
}

// Apenas apresenta o conteúdo do primeiro elemento da fila
char *fileQueuePeek(Queue _queue){
    if(fileQueueIsEmpty(_queue) == 0){
        return _queue.tail->content;
    }
    return NULL;
}
