#include <stdio.h>
#include <stdlib.h>
#include "cinema.h"


int main() {

    Cliente cliente;
    int escolha;

do{
    
    printf("Selecione a opcao desejada\n");
    printf("1 - Comprar Ingresso\n");
    printf("2 - Imprimir Ingresso\n");
    printf("3 - Impressao de Relatorio\n");
    printf("0 - Fechar programa\n");
    scanf("%d", &escolha);


    switch (escolha) {
        case 1:
            system("cls");
            printf("\n**** COMPRAR INGRESSO ****\n");
            comprar_assentos(&cliente, filmes);
            break;
        case 2:
            system("cls");
            printf("\n**** IMPRIMIR INGRESSO ****\n\n");
            imprimirIngresso(pessoa);
            break;
        case 3:
            system("cls");
            printf("\n**** IMPRIMIR RELATÓRIO ****\n");
            printf("\nPara imprimir um relatorio e necessario ser um usuario autorizado\n");
            // condição para verificar se e uma pessoa altorizada.
            imprimirRelatorio(pessoa);

            break;
        default:
            break;
    }


} while (escolha != 0);


    return 0;
}