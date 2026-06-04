#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 139

struct hashNode{
    char *palavra;
    int idGlobal;
    int frequencia;
    struct hashNode *next;
};

typedef struct{
    struct hashNode* first[TABLE_SIZE];
}HashTable;

HashTable init(HashTable _hash){
    for(int i = 0; i < TABLE_SIZE; i++){
        _hash.first[i] = NULL;
    }
    return _hash;
}

int hashFunc(char *palavra){
    int counter = 0;
    for(int i = 0; palavra[i] != '\0'; i++){
        counter += palavra[i]*(i+1);
    }
    return counter%TABLE_SIZE;
}

struct hashNode* findInHash(struct hashNode *first, char *palavra){
    while(first != NULL){
        if(strcmp(first->palavra, palavra) == 0){
            return first;
        }
        first = first->next;
    }
    return NULL;
}

void insertHashTable(char *palavra, HashTable _hash){
    static int globalId = 0;
    int tableIndex = hashFunc(palavra);
    struct hashNode *newNode = findInHash(_hash.first[tableIndex], palavra);
    if(newNode != NULL){ // Se a palavra ja existir aumenta a frequência
        newNode->frequencia++;
    }else{
        newNode = malloc(sizeof(struct hashNode));
        strcpy(newNode->palavra, palavra);
        newNode->frequencia = 1;
        newNode->idGlobal = globalId;
        globalId++;
        if(_hash.first[tableIndex] == NULL){
            _hash.first[tableIndex] = newNode;
            newNode->next = NULL;
        }else{
            newNode->next = _hash.first[tableIndex];
            _hash.first[tableIndex] = newNode;
        }
    }
}

int findID(char *palavra, HashTable _hash){
    int tableIndex = hashFunc(palavra);
    struct hashNode *result = findInHash(_hash.first[tableIndex], palavra);
    if(result != NULL){
        return result->idGlobal;
    }
    return -1;
}

