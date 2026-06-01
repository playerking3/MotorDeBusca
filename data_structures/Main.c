#include "TADarquivos.h"
#include "Utils.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"


int main(){
    Queue* documentsQueue;
    int op;
    char file[MAX_FILE];
    documentsQueue = malloc(sizeof(Queue));
    documentsQueue->head = NULL;
    documentsQueue->tail = NULL;

    while(1){
        op = MainMenu();
        switch(op){
            case 1:
                printf("Digite o nome do arquivo a ser enfileirado\n"
                       "(Nao deve haver espacos ou caracteres especiais):\n");
                if(fgets(file, MAX_FILE, stdin) != NULL){
                    fileEnqueue(documentsQueue, file);
                    printf("Arquivo enfileirado!\n");
                } else
                    printf("Erro na leitura do nome do arquivo!\n");
                break;
            case 2:
                fileDequeue(documentsQueue);
                printf("Arquivo desenfileirado!\n");
                break;
            case 3:
                printf("Proximo documento na fila: %s\n", fileQueuePeek(documentsQueue[0]));
                break;
        }
    }
    return 0;
}
