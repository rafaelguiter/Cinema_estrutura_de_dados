#include <stdio.h>
#include <stdlib.h>
#include "cinema.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
	
    Cliente cliente;
    int escolha;

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Comprar Ingresso\n");
        printf("2 - Imprimir Ingresso\n");
        printf("3 - Relatorio\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        
        if (scanf("%d", &escolha) != 1) {
            limparBuffer();
            printf("Opção inválida! Digite um número.\n");
            continue;
        }
        limparBuffer();

        switch (escolha) {
            case 1:
                system("cls");
                printf("\n**** COMPRAR INGRESSO ****\n");
                comprar_assentos(&cliente, filmes);
                break;
            case 2:
                system("cls");
                printf("\n**** IMPRIMIR INGRESSO ****\n");
                if (pessoa == NULL) {
                    printf("Nenhum ingresso vendido ainda!\n");
                    break;
                }
                int idBusca;
                printf("Digite o ID do ingresso: ");
                scanf("%d", &idBusca);
                // Removida a chamada para ordenarPagamentos pois não é mais necessária
                pagamento *ingresso = buscarIngressoBinario(pessoa, idBusca);
                if (ingresso) {
                    imprimirIngresso(ingresso);
                } else {
                    printf("Ingresso não encontrado!\n");
                }
                break;
            case 3:
                system("cls");
                printf("\n**** RELATORIO ****\n");
                imprimirRelatorio(pessoa);
                break;
        }
    } while (escolha != 0);

    return 0;
}
