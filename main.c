#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "cinema.h"
#include <locale.h>

int main() {

    Cliente cliente;
    int escolha, id, escolher, idBusca, m_i, imprime_ultimo;

do{
    
    printf("\n  ========== MENU INICIAL ===========  \n");
    printf("\nSelecione a opcao desejada\n");
    printf("1 - Comprar Ingresso\n");
    printf("2 - Imprimir Ingresso\n");
    printf("3 - Impressao de Relatorio\n");
    printf("0 - Fechar programa\n");
    scanf("%d", &escolha);


    switch (escolha) {
        case 1:
            limpartela();
            printf("\n**** COMPRAR INGRESSO ****\n");
            comprar_assentos(&cliente, filmes);
            printf("\n\n\n\n\npressione qualquer tecla para voltar ao menu principal ...");
            _getch();

            break;
        case 2:

            limpartela();
            printf("\n**** BUSCAR INGRESSO POR ID ****\n\n");
            if (pessoa == NULL) {
                printf("Nenhum ingresso vendido ainda!\n");
                printf("\n\n\n\n\npressione qualquer tecla para voltar ao menu principal ...");
                _getch();
                break;
            }


            do
            {
                printf("\nSelecione uma das duas opcoes\n\n");
                printf("1- Ultimo ingresso comprado     2- pesquisar por ID \n\n");
                printf("Digite: ");
                scanf("%d", &imprime_ultimo);
            } while (imprime_ultimo != 1 && imprime_ultimo !=2);

            if (imprime_ultimo == 1){
                imprimirIngresso(pessoa);

            }else{
                limpartela();
                printf("\n**** BUSCAR INGRESSO POR ID ****\n\n");

                printf("Deseja pesquisar algum ingresso especifico? \n\n");
                printf("Digite o ID do ingresso: ");
                scanf("%d", &idBusca);
    
                pagamento *ingresso = buscarIngressoBinario(pessoa, idBusca);
                
                if (ingresso) {
                    imprimirIngresso(ingresso);
                } else {
                    printf("\n\nIngresso nao encontrado!\n\n");
                    printf("----------------------------------\n");
                }
                
            }
            printf("\n\n\n\n\npressione qualquer tecla para voltar ao menu principal ...");
            _getch();
            break;

        case 3:

            limpartela();
            
            if (pessoa == NULL) {
                printf("\n**** IMPRIMIR RELATORIO ****\n\n");
                printf("Nenhum ingresso vendido ainda!\n");
                printf("\n\n\n\n\npressione qualquer tecla para voltar ao menu principal ...");
                _getch();
                break;

            }else{
                printf("\n**** IMPRIMIR RELATORIO ****\n\n");
                printf("Deseja imprimir o relatorio de que forma ?\n\n");
                printf("1- ID    2- TIPO DE INGRESSO\n\n");

                do
                {   
                    printf("Digite:  ");
                    scanf("%d", &escolher);
                } while (escolher != 1 && escolher != 2);
                
                

                if (escolher == 1){
                    
                    do
                    {
                        limpartela();
                        printf("\n**** IMPRIMIR RELATORIO ****\n\n");
                        printf("De que forma deseja ordenar o ID ?\n\n");
                        printf("1- Crescente     2- Decrescente\n\n");
                        printf("Digite:  ");
                        scanf("%d", &id);
                    } while (id != 1 && id !=2);

                    if (id == 1){
                        imprimirRelatorioOrdenado(pessoa);
                    }else{
                        imprimir_Relatorio_Id_Decrescente(pessoa);
                    }

                }else{

                    limpartela();
                    printf("**** IMPRIMIR RELATORIO ****\n\n");
                    printf("Deseja ordenar por Meia ou Inteira ?\n");

                    do
                    {
                        printf("\n1- Meia  2- Inteira\n\n");
                        printf("Digite: ");

                        scanf("%d",&m_i);
                    } while (m_i != 1 && m_i != 2);

                    if (m_i == 1){
                        imprimir_Relatorio_meia_primeiro(pessoa);
                    }else{
                        imprimir_Relatorio_inteira_primeiro(pessoa);
                    }

                }
            }


            printf("\n\n\n\n\npressione qualquer tecla para voltar ao menu principal ...");
            _getch();
            break;
            

            
        default:
        printf("\nDigito invalido\n");
        break;
        }


        limpartela();
    

} while (escolha != 0);

    return 0;
}