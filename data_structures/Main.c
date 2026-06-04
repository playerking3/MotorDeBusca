#include "TADarquivos.h"
#include "Utils.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"


int main(){
    Queue* documentsQueue;
    Stack* processStack;
    archiveWords processedArchives[MAX_TO_PROCESS];
    int op;
    char file[MAX_FILE];

    documentsQueue = malloc(sizeof(Queue));
    documentsQueue->head = NULL;
    documentsQueue->tail = NULL;

    processStack = malloc(sizeof(Stack));
    processStack->head = NULL;
    processStack->_size = 0;

    for(int i = 0; i < MAX_TO_PROCESS; i++){
        processedArchives[i].first= NULL;
        processedArchives[i].name= NULL;
    }

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
                printf("Proximo documento na fila: %s\n", fileQueuePeek(*documentsQueue));
                break;
            case 4:
                break;
            case 5:
                printStack(*processStack);
                break;
            case 6:
                if(stackPeek(*processStack) != NULL)
                    printf("Ultimo processo: %s\n", stackPeek(*processStack));
                else
                    printf("Pilha de processos vazia!\n");
                break;
            case 7:
                int id;
                hashNode aux;

                printf("Digite o ID da palavra a ser buscada:\n");
                scanf("%d", &id);
                getchar();

                aux = findWordByID(findLastArchive(processedArchives), id);
                printHashNode(aux);
                break;
            case 8:
                printArchiveWords(findLastArchive(processedArchives));
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
        }
    }
    return 0;
}
