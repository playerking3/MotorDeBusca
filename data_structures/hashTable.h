#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 139



/*********************************************************/
/**          Struct basica que contera as informacoes
            de uma palavra e sera usado em diferentes
            estruturas para administracao dos recursos. **/
/*********************************************************/
/*********************************************************/
/**          Basic Struct of system, this struct model
            most of list and logic of system, storage
            informations about a word.                  **/
/*********************************************************/
typedef struct hashNode{
    char *palavra;
    int idGlobal;
    int frequencia;
    struct hashNode *next;
} hashNode;



/*********************************************************/
/**     Struct responsável por modelar a tabela hash.   **/
/*********************************************************/
/*********************************************************/
/**     This struct model the system's tabel hash.      **/
/*********************************************************/
typedef struct{
    struct hashNode* first[TABLE_SIZE];
}HashTable;


/*********************************************************/
/**     Funcao que inicializa a tabela hash com NULO.   **/
/*********************************************************/
/*********************************************************/
/**     Function than inicializate the table hash with
        NULL.                                           **/
/*********************************************************/
HashTable init(HashTable* _hash){
    for(int i = 0; i < TABLE_SIZE; i++){
        _hash->first[i] = NULL;
    }
    return *_hash;
}


/*********************************************************/
/**                 Funcao hash.                        **/
/*********************************************************/
/*********************************************************/
/**                 Hash Function.                      **/
/*********************************************************/
int hashFunc(char *palavra){
    int counter = 0;
    for(int i = 0; palavra[i] != '\0'; i++){
        counter += palavra[i]*(i+1);
    }
    return counter%TABLE_SIZE;
}




/*********************************************************/
/**          Funcao que retorna o no com a mesma
            palavra que a enviada para comparacao.      **/
/*********************************************************/
/*********************************************************/
/**          Function than return the node in table hash
            if it's word is the same than the sent.     **/
/*********************************************************/
hashNode* findInHash(hashNode *first, char *palavra){
    hashNode* aux = first;
    int c = 0;
    while(aux != NULL && c++ < 50){
        if(!strcmp(aux->palavra, palavra)){
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}


/*********************************************************/
/**          Funcao que insere uma palavra na
            tabela hash.                                **/
/*********************************************************/
/*********************************************************/
/**          Function than insert a word in the
            table hash.                                 **/
/*********************************************************/
hashNode* insertHashTable(char *palavra, HashTable* _hash){
    static int globalId = 0;

    //  Aplica a funcao hash para obter o indice
    //  Apply the hash function to get the index
    int tableIndex = hashFunc(palavra);

    //  Verifica se a palavra ja existe na tabela hash
    //  Verify if the word is already exist in the table hash
    hashNode *newNode = findInHash(_hash->first[tableIndex], palavra);

    //  Se a palavra ja existir aumenta a frequência
    //  If the word is already exist, increases frequency
    if(newNode != NULL){
        newNode->frequencia++;
    }else{
        //  Caso contrario, cria o no e inicializa as informacoes dele
        //  Else, creates a node and inicilizes the informations
        newNode = malloc(sizeof(hashNode));
        newNode->palavra = malloc(sizeof(char)*(strlen(palavra)+1)); // +1 para o '\0'
        strcpy(newNode->palavra, palavra);
        newNode->frequencia = 1;
        newNode->idGlobal = globalId++;
        newNode->next = NULL;

        //  Se nao houver nada naquele indice ainda o armazena como primeiro  no do indice
        //  If this index of table hash is NULL, place it in the first node of it
        if(_hash->first[tableIndex] == NULL){
            _hash->first[tableIndex] = newNode;
        }
        //  Caso contrario, "empurra" todos os nos para frente e o coloca como primeiro
        //  Else, place it in the first position and move the others to the next position
        else{
            newNode->next = _hash->first[tableIndex];
            _hash->first[tableIndex] = newNode;
        }
    }

    //  Retorna o no criado ou encontrado
    //  Return the changed node
    return newNode;
}



/*********************************************************/
/**          Encontra o ID de uma palavra em
            pela tabela hash montada.                   **/
/*********************************************************/
/*********************************************************/
/**      Find the ID of a word based on table hash.     **/
/*********************************************************/
int findID(char *palavra, HashTable _hash){
    int tableIndex = hashFunc(palavra);
    struct hashNode *result = findInHash(_hash.first[tableIndex], palavra);
    if(result != NULL){
        return result->idGlobal;
    }
    return -1;
}


/*********************************************************/
/**          Funcao para exibir um no.                  **/
/*********************************************************/
/*********************************************************/
/**          Function to print a hash node.             **/
/*********************************************************/
void printHashNode(hashNode node){
    printf( "===================\nPalavra: %s\nID Global: %d\nFrequencia: %d\n", node.palavra, node.idGlobal, node.frequencia);
}


