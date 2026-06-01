#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 139

struct Node{
    char *palavra;
    int idGlobal;
    int frequencia;
    struct Node *next;
};

typedef struct{
    struct Node* first[TABLE_SIZE];
}HashTable;

HashTable init(HashTable hash){
    for(int i = 0; i < TABLE_SIZE; i++){
        hash.first[i] = NULL;
    }
    return hash;
}

int hashFunc(char *palavra){
    int counter = 0;
    for(int i = 0; palavra[i] != '\0'; i++){
        counter += palavra[i]*(i+1);
    }
    return counter%TABLE_SIZE;
}

struct Node* findInHash(struct Node *first, char *palavra){
    while(first != NULL){
        if(strcmp(first->palavra, palavra) == 0){
            return first;
        }
        first = first->next;
    }
    return NULL;
}

void insert(char *palavra, HashTable hash){
    static int globalId = 0;
    int tableIndex = hashFunc(palavra);
    struct Node *newNode = findInHash(hash.first[tableIndex], palavra);
    if(newNode != NULL){ // Se a palavra ja existir aumenta a frequência
        newNode->frequencia++;
    }else{
        newNode = malloc(sizeof(struct Node));
        strcpy(newNode->palavra, palavra);
        newNode->frequencia = 1;
        newNode->idGlobal = globalId;
        globalId++;
        if(hash.first[tableIndex] == NULL){
            hash.first[tableIndex] = newNode;
            newNode->next = NULL;
        }else{
            newNode->next = hash.first[tableIndex];
            hash.first[tableIndex] = newNode;
        }
    }
}

int findID(char *palavra, HashTable hash){
    int tableIndex = hashFunc(palavra);
    struct Node *result = findInHash(hash.first[tableIndex], palavra);
    if(result != NULL){
        return result->idGlobal;
    }
    return -1;
}

