#include "TADarquivos.h"
#include "Utils.h"
#include "stack.h"
#include "queue.h"
#include <conio.h>
#include "binaryTree.c"

//  Maximo de palavras diferentes que o sistema pode ler
//  Max diferrent words than the system suports.
#define MAX_WORDS 5000

//  Maximo de caracteres que uma palavra pode ter
//  Max chars than a word can has
#define MAX_CHAR 30



/*********************************************************/
/**      Insere uma palavra (e suas informacoes)
        no dicionario global.                           **/
/*********************************************************/
/*********************************************************/
/**      Insert into the global dictionary a word
        and your informations.                          **/
/*********************************************************/
void insertWordDictionary(hashNode dictionary[], int id, hashNode to_Insert){
    dictionary[id] = to_Insert;
}


/*********************************************************/
/**      Retorna uma palavra do dicionario global
        pelo ID.                                        **/
/*********************************************************/
/*********************************************************/
/**      Return a word from global dictionary based
        at ID sent.                                     **/
/*********************************************************/
char* getWordFromDictionary(hashNode dictionary[], int id){
    return dictionary[id].palavra;
}


/*********************************************************/
/**      Retorna o ID do dicionario global da palavra.  **/
/*********************************************************/
/*********************************************************/
/**      Return an ID from global dictionary based
        at the word sent.                               **/
/*********************************************************/
int getIdFromDictionary(hashNode dictionary[], char* palavra){
    for(int i = 0; i < MAX_WORDS; i++){
        if((dictionary[i].palavra != NULL && palavra != NULL) && (!strcmp(dictionary[i].palavra, palavra))){
            return dictionary[i].idGlobal;
        }
    }
    return -1;
}



void getAllDocumentsAndMakeTree(archiveWords archives[], BinaryTree** tree, lS_descritor* toCompare){
    hashNode* auxHashNode;
    node_string_List* auxStringList;
    float multiplier = 1;
    float score;
    if(*tree == NULL)
        *tree = createTree();
    for(int i = 0; archives[i].name != NULL; i++){
        score = 0;
        if(toCompare != NULL){
            auxStringList = toCompare->head;
            for(int j = 1; j < (toCompare->Size)+1; j++){
                auxHashNode = archives[i].first;
                multiplier = 1;
                while(auxHashNode != NULL){
                    if(!strcmp(auxStringList->word, auxHashNode->palavra)){
                        score += (j/multiplier)*100;
                    }
                    auxHashNode = auxHashNode->next;
                    multiplier++;
                }
                auxStringList = auxStringList->next;
            }
        }
        insertInTree(*tree, archives[i].name, score);
    }
}


/*********************************************************/
/*********************************************************/
/**                  MAIN FUNCTION                      **/
/*********************************************************/
/*********************************************************/
int main(){

    //  Estrutura de dados utilizados durante o programa para execucao das diversas funcoes
    //  Data Structs used while the program is running to do all functions correctly
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

    BinaryTree* binaryTree;

    //  Inicializacao de "processedArchives"
    //  "processedArchives" inicialization
    for(int i = 0; i < MAX_TO_PROCESS; i++){
        processedArchives[i].first= NULL;
        processedArchives[i].name= NULL;
    }

    //  Inicializacao de "globalDictionary"
    //  "globalDictionary" inicialization
    for(int i = 0; i < MAX_WORDS; i++){
        globalDictionary[i].palavra = NULL;
        globalDictionary[i].next = NULL;
        globalDictionary[i].frequencia = 0;
        globalDictionary[i].idGlobal = -1;
    }

    //  While para repeticao do codigo
    //  While to choose different functions
    while(1){
        op = MainMenu();
        switch(op){
            case 1:     // Enfileirar documento
                printf("Digite o nome do arquivo a ser enfileirado\n"
                       "(Nao deve haver espacos ou caracteres especiais):\n");
                if(fgets(file, MAX_FILE, stdin) != NULL){
                    file[strlen(file)-1] = '\0';
                    fileEnqueue(documentsQueue, file);
                    printf("Arquivo enfileirado!\n");
                } else
                    printf("Erro na leitura do nome do arquivo!\n");
                break;
            case 2:     // Remover documento
                fileDequeue(documentsQueue);
                printf("Arquivo desenfileirado!\n");
                break;
            case 3:     // Visualizar proximo documento
                printf("Proximo documento na fila: %s\n", fileQueuePeek(*documentsQueue));
                break;
            case 4:     // Processar proximo documento
                nextDocument = fileDequeue(documentsQueue);
                stackPush(processStack, "Arquivo desenfileirado!\n");

                bufferStringList = readArchive(nextDocument);
                if(bufferStringList != NULL){
                    stackPush(processStack, "Arquivo lido!\n");

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
                    stackPush(processStack,"Palavras inseridas na tabela Hash\n\0");
                    stackPush(processStack,"Palavras inseridas na lista do arquivo\n\0");
                    stackPush(processStack,"Documento finalizado!\n\0");
                    printf("Documento \"%s\" processado!\n", processedArchives[numberOfArchive].name);
                    numberOfArchive++;
                } else{
                    stackPush(processStack, "Erro com o documento");
                    printf("Erro com o documento!\n");
                }
                break;
            case 5:             //  Exibir a pilha de processos
                printStack(*processStack);
                break;
            case 6:             //  Visualizar o ultimo processo
                if(stackPeek(*processStack) != NULL)
                    printf("Ultimo processo: %s\n", stackPeek(*processStack));
                else
                    printf("Pilha de processos vazia!\n");
                break;
            case 7:             //  Buscar palavra pelo ID (Apenas no ultimo documento)
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
            case 8:             //  Visualizar todas as palavras do ultimo arquivo
                if(findLastArchive(processedArchives) != NULL)
                    printArchiveWords(*findLastArchive(processedArchives));
                else
                    printf("Nenhum documento processado!\n");
                break;
            case 9:             //  Buscar ID de uma palavra (Contexto global)
                printf("Digite a palavra:\n");
                scanf("%s", palavra);
                if(getIdFromDictionary(globalDictionary, palavra) != -1)
                    printf("ID referente a palavra %s: %d\n", palavra, getIdFromDictionary(globalDictionary, palavra));
                else
                    printf("Nenhum ID associado a esta palavra!\n");
                break;
            case 10:            //  Buscar palavra pelo seu ID  (Contexto global)
                printf("Digite o ID da palavra a ser buscada:\n");
                scanf("%d", &id);
                getchar();
                if(getWordFromDictionary(globalDictionary, id) != NULL)
                    printf("Palavra referente ao id %d: %s\n", id, getWordFromDictionary(globalDictionary, id));
                else
                    printf("Nenhuma palavra associada a este ID!\n");
                break;
            case 11:            //  Buscar documentos relevantes pelo score
                bufferStringList->head = NULL;
                bufferStringList->Size = 0;

                printf("Digite a sequencia de palavras para buscar nos documentos separadas por um espaco:\n");

                do{
                    scanf("%s", palavra);
                    tokenization(palavra);
                    auxNodeStrList = malloc(sizeof(node_string_List));
                    auxNodeStrList->word = malloc((strlen(palavra)+1)*sizeof(char));
                    strcpy(auxNodeStrList->word, palavra);
                    auxNodeStrList->next = bufferStringList->head;
                    bufferStringList->head = auxNodeStrList;
                    bufferStringList->Size += 1;
                }while(!StdinIsEmpty());
                getAllDocumentsAndMakeTree(processedArchives, &binaryTree, bufferStringList);
                printf("Arvore em ordem:\n");
                readTreeInOrder(binaryTree);
                freeTree(&binaryTree);
                break;
        }
    }
    return 0;
}
