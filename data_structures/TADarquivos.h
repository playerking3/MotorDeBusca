#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "hashTable.h"


// TO COMMENT
#define MAX_TO_PROCESS 20

/*********************************************************/
/**     No de para armazenar as palavras lidas no
                    Arquivo                             **/
/*********************************************************/
/*********************************************************/
/**      Struct of a linked list node to store a word
        and the locale of the next node.                **/
/*********************************************************/
struct node_string_List{
    char* word;
    struct node_string_List* next;
}typedef node_string_List;


/*********************************************************/
/**          Lista que contem todas as palavras
            e a quantidade delas.                       **/
/*********************************************************/
/*********************************************************/
/**          Struct of a list to store all words
            read and the quantity of words.             **/
/*********************************************************/
struct lS_descritor{
    node_string_List* head;
    int Size;
} typedef lS_descritor;


// TO COMMENT
typedef struct archiveWords{
    char* name;
    hashNode* first;
}archiveWords;



/*********************************************************/
/**      Funcao que captura apenas as letras
        do alfabeto americano, descartando pontuacao
                e acentuacao.                           **/
/*********************************************************/
/*********************************************************/
/**      Function than catch only letters and
        discards punctuation to token words.            **/
/*********************************************************/
void tokenization(char* word){
    for(int i = 0; i < strlen(word); i++){
        if((word[i] >= 'A' && word[i] <= 'Z'))
            word[i] += 32;
        if(!(word[i] >= 'a' && word[i] <= 'z')){
            for(int j = i; j < strlen(word); j++){
                word[j] = word[j+1];
            }
            i--;
        }
    }
}



/*********************************************************/
/**      Funcao que recebe o nome de um arquivo
        e armazena todas as palavras em uma
        lista ligada. Caso encontre palavras repetidas,
        as descarta imediatamente.                      **/
/**     RETORNO: um ponteiro para a lista construida    **/
/*********************************************************/
/*********************************************************/
/**      A function that receives the name of a file
        and stores all the words in a linked list.
         If it finds repeated words, it immediately
        discards them.                                  **/
/**     RETURN: A pointer to the made list.             **/
/*********************************************************/
lS_descritor* readArchive(char* file_name){
    // Abertura do arquivo
    // Open archive
    FILE* file = fopen("teste.txt", "r");

    // Variaveis auxiliares
    // Auxiliar variables
    lS_descritor* ret = malloc(sizeof(lS_descritor));
    ret->head = NULL;
    ret->Size = 0;
    node_string_List* actual = NULL;
    node_string_List* before = NULL;
    char* next_word;

    // Verificando caso o arquivo nao foi encontrado
    // Checking if the archive don't exist
    if(!file){
        perror(file_name);
        return ret;
    }

    // Buffer de 50 letras para armazenamento das palavras
    // A buffer with 50 letters to store word to word of archive
    next_word = malloc(sizeof(int)*50);

    // Executa para a primeira palavra, caso exista
    // Do to the first word, if it exist
    if(fscanf(file, "%s", next_word) != EOF){
        tokenization(next_word);
        actual = malloc(sizeof(node_string_List));
        actual->word = malloc(sizeof(char)*(strlen(next_word)+1));
        strcpy(actual->word, next_word);
        actual->next = before;
        before = actual;
        ret->Size++;
    }

    // Executa para as demais palavras do arquivo
    // Do to another words
    while(fscanf(file, "%s", next_word) != EOF){
        tokenization(next_word);
        if(strcmp(before->word, next_word)){
            actual = malloc(sizeof(node_string_List));
            actual->word = malloc(sizeof(char)*(strlen(next_word)+1));
            strcpy(actual->word, next_word);
            actual->next = before;
            before = actual;
            ret->Size++;
        }
    }

    // Faz o retorno apontar para o primeiro elemento da lista
    // Assignent of the linked list for return pointer
    ret->head = actual;

    return ret;
}


// TO COMMENT
archiveWords findLastArchive(archiveWords words[]){
    archiveWords ret;
    ret.first = NULL;
    ret.name = NULL;
    for(int i = MAX_TO_PROCESS; i >= 0; i--){
        if(words[i].name != NULL)
            return words[i];
    }
    return ret;
}


void insertArchiveList(archiveWords archives[], archiveWords* words){
    static int index = 0;
    if(index < MAX_TO_PROCESS)
        archives[index] = *words;
}

void printArchiveWords(archiveWords words){
    struct hashNode* aux = words.first;
    while(aux != NULL){
        printHashNode(*aux);
        aux = aux->next;
    }
}

hashNode* findWordByID(archiveWords words, int ID){
    hashNode* aux = words.first;
    while(aux != NULL){
        if(aux->idGlobal == ID)
            return aux;
    }
    return NULL;
}
