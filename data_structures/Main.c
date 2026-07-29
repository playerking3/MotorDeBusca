#include "TADarquivos.h"
#include "Utils.h"
#include "stack.h"
#include "queue.h"
#include <conio.h>

#define MAX_WORDS 5000
#define MAX_CHAR 30

void insertWordDictionary(hashNode dictionary[], int id, hashNode to_Insert){
//    printHashNode(to_Insert);
    dictionary[id] = to_Insert;
}

char* getWordFromDictionary(hashNode dictionary[], int id){
    return dictionary[id].palavra;
}

int getIdFromDictionary(hashNode dictionary[], char* palavra){
    for(int i = 0; i < MAX_WORDS; i++){
        if((dictionary[i].palavra != NULL && palavra != NULL) && (!strcmp(dictionary[i].palavra, palavra))){
            return dictionary[i].idGlobal;
        }
    }
    return -1;
}

int main(){
    Queue* documentsQueue;

    Stack* processStack;

    archiveWords processedArchives[MAX_TO_PROCESS];
    archiveWords* auxLastArchive;
    node_string_List* auxNodeStrList;
    lS_descritor* bufferStringList;

    hashNode* auxHashNode;
    HashTable hashTable;
    init(&hashTable);

    hashNode globalDictionary[MAX_WORDS];

    int op;
    int id;
    int numberOfArchive = 0;

    char palavra[MAX_CHAR];
    char* nextDocument;
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

    for(int i = 0; i < MAX_WORDS; i++){
        globalDictionary[i].palavra = NULL;
        globalDictionary[i].next = NULL;
        globalDictionary[i].frequencia = 0;
        globalDictionary[i].idGlobal = -1;
    }
    while(1){
        op = MainMenu();
        switch(op){
            case 1:
                printf("Digite o nome do arquivo a ser enfileirado\n"
                       "(Nao deve haver espacos ou caracteres especiais):\n");
                if(fgets(file, MAX_FILE, stdin) != NULL){
                    file[strlen(file)-1] = '\0';
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
                nextDocument = fileDequeue(documentsQueue);
                stackPush(processStack, nextDocument, " - Arquivo desenfileirado!\n");

                bufferStringList = readArchive(nextDocument);
                if(bufferStringList != NULL){
                    stackPush(processStack, nextDocument, " - Arquivo lido!\n");

                    processedArchives[numberOfArchive].name = nextDocument;
                    processedArchives[numberOfArchive].first = NULL;

                    auxNodeStrList = bufferStringList->head;
                    for(int i = 0; i < bufferStringList->Size; i++){
                        auxHashNode = malloc(sizeof(hashNode));
                        *auxHashNode = *insertHashTable(auxNodeStrList->word, &hashTable);
                        auxHashNode->next = processedArchives[numberOfArchive].first;
                        processedArchives[numberOfArchive].first = auxHashNode;
                        auxNodeStrList = auxNodeStrList->next;
                        insertWordDictionary(globalDictionary, auxHashNode->idGlobal, *auxHashNode);
                    }

                    stackPush(processStack, nextDocument, " - Palavras inseridas na tabela Hash\n\0");
                    stackPush(processStack, nextDocument, " - Palavras inseridas na lista do arquivo\n\0");
                    stackPush(processStack, nextDocument, " - Documento finalizado!\n\0");
                    printf("Documento \"%s\" processado!\n", processedArchives[numberOfArchive].name);
                } else{
                    stackPush(processStack, nextDocument, " - Erro com o documento");
                    printf("Erro com o documento!\n");
                }
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
                printf("Digite o ID da palavra a ser buscada:\n");
                scanf("%d", &id);
                getchar();
                auxLastArchive = findLastArchive(processedArchives);
                if(auxLastArchive != NULL){
                    auxHashNode = findWordByID(*auxLastArchive, id);
                    if(auxHashNode != NULL)
                        printHashNode(*auxHashNode);
                    else
                        printf("Palavra nao encontrada no ultimo documento!\n");
                }else
                    printf("Nenhum arquivo processado!\n");
                break;
            case 8:
                if(findLastArchive(processedArchives) != NULL)
                    printArchiveWords(*findLastArchive(processedArchives));
                else
                    printf("Nenhum documento processado!\n");
                break;
            case 9:
                printf("Digite a palavra:\n");
                scanf("%s", palavra);
                if(getIdFromDictionary(globalDictionary, palavra) != -1)
                    printf("ID referente a palavra %s: %d\n", palavra, getIdFromDictionary(globalDictionary, palavra));
                else
                    printf("Nenhum ID associado a esta palavra!\n");
                break;
            case 10:
                printf("Digite o ID da palavra a ser buscada:\n");
                scanf("%d", &id);
                getchar();
                if(getWordFromDictionary(globalDictionary, id) != NULL)
                    printf("Palavra referente ao id %d: %s\n", id, getWordFromDictionary(globalDictionary, id));
                else
                    printf("Nenhuma palavra associada a este ID!\n");
                break;
            case 11:
                break;
        }
    }
    return 0;
}
