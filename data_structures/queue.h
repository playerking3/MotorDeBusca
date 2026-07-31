#include<stdlib.h>
#include<string.h>

/*********************************************************/
/**      Tamanho maximo dos nomes dos arquivos.         **/
/*********************************************************/
/*********************************************************/
/**      Max caracteres to file names.                  **/
/*********************************************************/
#define MAX_FILE 20

/*********************************************************/
/**      Estrutura dos nos da fila.                     **/
/*********************************************************/
/*********************************************************/
/**      Structs of queue nodes.                        **/
/*********************************************************/
struct FileNode{
    char content[MAX_FILE];
    struct FileNode *next;
};
/*********************************************************/
/**          Descritor da fila.                         **/
/*********************************************************/
/*********************************************************/
/**          Queue descriptor.                          **/
/*********************************************************/
typedef struct{
    struct FileNode *head;
    struct FileNode *tail;
} Queue;

/*********************************************************/
/**      Verifica se a fila esta vazia.                 **/
/*********************************************************/
/*********************************************************/
/**      Verify if the queue is empty.                  **/
/*********************************************************/
int fileQueueIsEmpty(Queue _queue){
    if(_queue.head == NULL && _queue.tail == NULL){
        return 1;
    }
    return 0;
}

/*********************************************************/
/**          Adiciona nos ao descritor da fila.         **/
/*********************************************************/
/*********************************************************/
/**          Add a new node to enqueue.                 **/
/*********************************************************/
void fileEnqueue(Queue *_queue, char *docFile){

    //  Cria um novo no
    //  Create a new node.
    struct FileNode *newFileNode = malloc(sizeof(struct FileNode));
    strcpy(newFileNode->content, docFile);
    newFileNode->next = NULL;

    //  Verifica se a fila é vazia, caso for adiciona como primeiro elemento
    //  Verify if the queue is empty, then if it is, add as the first node
    if(fileQueueIsEmpty(*_queue)){
        _queue->head = newFileNode;
        _queue->tail = newFileNode;
    }else{
        _queue->head->next = newFileNode;
        _queue->head = newFileNode;
    }

}

/*********************************************************/
/**      Tira o primeiro elemento da fila e
        retorna seu conteúdo.                           **/
/*********************************************************/
/*********************************************************/
/**      Dequeue the next element and return it.        **/
/*********************************************************/
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


/*********************************************************/
/**          Apenas apresenta o conteúdo do
            primeiro elemento da fila.                  **/
/*********************************************************/
/*********************************************************/
/**          Return the next element but don't
            dequeue it.                                 **/
/*********************************************************/
char *fileQueuePeek(Queue _queue){
    if(fileQueueIsEmpty(_queue) == 0){
        return _queue.tail->content;
    }
    return NULL;
}
