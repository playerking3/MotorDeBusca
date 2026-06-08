#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 139

typedef struct hashNode{
    char *palavra;
    int idGlobal;
    int frequencia;
    struct hashNode *next;
} hashNode;

typedef struct{
    struct hashNode* first[TABLE_SIZE];
}HashTable;

HashTable init(HashTable* _hash){
    for(int i = 0; i < TABLE_SIZE; i++){
        _hash->first[i] = NULL;
    }
    return *_hash;
}

int hashFunc(char *palavra){
    int counter = 0;
    for(int i = 0; palavra[i] != '\0'; i++){
        counter += palavra[i]*(i+1);
    }
    return counter%TABLE_SIZE;
}

hashNode* findInHash(hashNode *first, char *palavra){
    hashNode* aux = first;
    int i = 0;
    while(aux != NULL){
        printf("\n%s\n", aux->palavra);
        if(!strcmp(aux->palavra, palavra)){
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

hashNode* insertHashTable(char *palavra, HashTable* _hash){
    static int globalId = 0;
    int tableIndex = hashFunc(palavra);
    hashNode *newNode = findInHash(_hash->first[tableIndex], palavra);
    if(newNode != NULL){ // Se a palavra ja existir aumenta a frequência
        newNode->frequencia++;
    }else{
        newNode = malloc(sizeof(hashNode));
        newNode->palavra = malloc(sizeof(char)*strlen(palavra));
        strcpy(newNode->palavra, palavra);
        newNode->frequencia = 1;
        newNode->idGlobal = globalId++;
        newNode->next = NULL;
        if(_hash->first[tableIndex] == NULL){
            _hash->first[tableIndex] = newNode;
        }else{
            newNode->next = _hash->first[tableIndex];
            _hash->first[tableIndex] = newNode;
        }
    }
    return newNode;
}

int findID(char *palavra, HashTable _hash){
    int tableIndex = hashFunc(palavra);
    struct hashNode *result = findInHash(_hash.first[tableIndex], palavra);
    if(result != NULL){
        return result->idGlobal;
    }
    return -1;
}


void printHashNode(hashNode node){
    printf( "Palavra: %s\n", node.palavra,
            "ID Global: %d\n", node.idGlobal,
            "Frequencia: %d\n", node.frequencia);
}


