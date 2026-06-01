#include <stdio.h>



/*********************************************************/
/**      Função para exibir um menu com as
        funcionalidades do programa e retorna
        a opção selecionada.                            **/
/*********************************************************/
/*********************************************************/
/**      Function than show the features of program
 *      and returns the option selected.                **/
/*********************************************************/
int MainMenu(){
    int ret;
    printf("01 - Adicionar documento na fila;");
    printf("02 - Remover documento da fila;");
    printf("03 - Vizualizar proximo documento;");
    printf("04 - Processar proximo documento;");
    printf("05 - Visualizar pilha de processos;");
    printf("06 - Visualizar o ultimo processo;");
    printf("07 - Buscar palavra do ultimo documento pelo ID;");
    printf("08 - Percorrer todas as palavras do ultimo documento;");
    printf("09 - Buscar ID de uma palavra;");
    printf("10 - Visualizar palavas pelo ID global;");
    printf("11 - Buscar documentos relevantes pelo Score;");

    scanf("%d", &ret);
    return ret;
}

