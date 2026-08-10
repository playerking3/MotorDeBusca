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
    printf("\n-==================================================-\n");
    printf("01 - Adicionar documento na fila;\n");
    printf("02 - Remover documento da fila;\n");
    printf("03 - Vizualizar proximo documento;\n");
    printf("04 - Processar proximo documento;\n");
    printf("05 - Visualizar pilha de processos;\n");
    printf("06 - Visualizar o ultimo processo;\n");
    printf("07 - Buscar palavra do ultimo documento pelo ID;\n");
    printf("08 - Percorrer todas as palavras do ultimo documento;\n");
    printf("09 - Buscar ID de uma palavra;\n");
    printf("10 - Visualizar palavra pelo ID global;\n");
    printf("11 - Buscar documentos relevantes pelo Score;\n");
    printf("12 - Sair;\n");
    printf("-==================================================-\n");

    scanf("%d", &ret);
    getchar();
    return ret;
}

int StdinIsEmpty(){
    int ch = getc(stdin);
    if (ch == '\n') {
        return 1; // Vazio ou fim de arquivo (EOF)
    }
    return 0; // Não está vazio
}
