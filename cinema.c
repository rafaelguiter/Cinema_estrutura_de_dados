#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cinema.h"

pagamento *pessoa = NULL;

Filme filmes[CATALOGO] = {
    {"OS VINGADORES", "20:00", {0}, 35},
    {"VELOZES E FURIOSOS", "21:00", {0}, 25.0},
    {"VIVA LA VIDA UMA FESTA", "19:30", {0}, 25.0},
    {"ATE ONDE IREMOS ?", "20:00", {0}, 35.0},
    {"LARACROFT", "23:00", {0}, 40.0}
};

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpartela(){
    system("cls || clear");
}

void mostrarFilmes(){
    for(int i = 0; i < CATALOGO; i++){
        printf("\n%d - %s  as  %s\n", i + 1, filmes[i].nome, filmes[i].hora);
        printf("    valor do Ingresso R$ %0.2f\n",filmes[i].valor);
        printf("\n  --------------------------------\n");
    }
}

void escolherFilme(Filme filmes[], Filme **filme_escolhido){
    int escolha;

    mostrarFilmes();
    printf("\n\nQual filme deseja escolher - ");
    scanf("%d", &escolha);
    limparBuffer();

    *filme_escolhido = &filmes[escolha - 1];
}

float calcular_total(float inteira, float meia, Filme *film){
    float pagar = (inteira * film->valor) + (meia * (film->valor / 2.0));
    return pagar;
}

void Assentos(Filme *filme){

    int nColuna = 0;

    limpartela();

    printf("\nMapa dos assentos para o filme '%s' \n\n", filme->nome);

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {

            nColuna +=1;

            if (filme->sala[i][j] == 0) {
               printf("%02d[ ] ", nColuna); // Assentos livres
            } else {
                printf("%02d[X] ", nColuna); // Assentos ocupados
            }
        }
        printf("\n");
    }
}

void comprar_assentos(Cliente *cli, Filme filmes[]) {
    
    int lugar, cadeira;
    int capacidade = LINHAS * COLUNAS;
    int ass_ingresso[70] = {0};
    int comprar = 0;
    int lin = 0, col = 0;
    int i = 0;
    float meia = 0, inteira = 0, total = 0;
    Filme *filme_escolhido;
    
    
    pagamento *pag_novo = (pagamento *)malloc(sizeof(pagamento));
    if (pag_novo == NULL) {
        printf("Erro ao alocar memória para novo pagamento.\n");
        return;
    }


    escolherFilme(filmes, &filme_escolhido);

    Assentos(filme_escolhido);

    printf("\nQuantos ingressos deseja comprar? - ");
    scanf("%d", &comprar);
    limparBuffer();
    printf("\n");

    while(i < comprar) {
        printf("\nPor favor escolha o numero do seu assento: ");
        scanf("%d", &cadeira);
        limparBuffer();

        lugar = cadeira - 1;
        lin = lugar / 10;
        col = lugar % 10;

        if (filme_escolhido->sala[lin][col] == 0) {

            filme_escolhido->sala[lin][col] = 1;
            ass_ingresso[i] = cadeira;
            i++;

            limpartela();
            Assentos(filme_escolhido);
        } else {
            limpartela();
            Assentos(filme_escolhido);
            printf("\nO assento numero %d ja esta ocupado\n", cadeira);
        }
    }

    printf("\nPor favor digite os dados para pagamento\n");
    printf("\nNome: ");
    fgets(cli->nome, sizeof(cli->nome), stdin);
    cli->nome[strcspn(cli->nome, "\n")] = 0;
    //fgets(novo->nome, sizeof(novo->nome), stdin);
    

    printf("\nCPF: ");
    fgets(cli->cpf, sizeof(cli->cpf), stdin);
    cli->cpf[strcspn(cli->cpf, "\n")] = 0;
    //fgets(novo->cpf, sizeof(novo->cpf), stdin);
    

    printf("\nQuantos ingressos sao meia entrada? ");
    scanf("%f", &meia);
    limparBuffer();

    if (comprar == meia) {
        total = calcular_total(inteira, meia, filme_escolhido);
    } else if (meia < comprar) {
        inteira = comprar - meia;
        total = calcular_total(inteira, meia, filme_escolhido);
    } else {
        printf("\nA quantidade de ingresso de meia entrada ultrapassa os ingressos comprados");
    }

    limpartela();
    Assentos(filme_escolhido);

    for (int i = 0; i < capacidade; i++) {
        if (ass_ingresso[i] != 0) {
            printf("\nAssento comprado numero: %d", ass_ingresso[i]);
        }
    }

    printf("\n\nTotal a pagar: R$%.2f\n\n\n", total);


    pag_novo->id = rand() % 200 + 1;
    for (int i = 0; i < comprar; i++) {
        pag_novo->assento[i] = ass_ingresso[i];
    }
    strcpy(pag_novo->nome, cli->nome);
    strcpy(pag_novo->cpf, cli->cpf);
    pag_novo->filme = filme_escolhido;
    pag_novo->quantidade = comprar;
    pag_novo->ingresso_interios = inteira;
    pag_novo->ingresso_meia = meia;
    pag_novo->valor = total;
    
    // criando a lista encadeada
    pag_novo->proximo = pessoa;
    pessoa = pag_novo;
    

}

void imprimirIngresso(pagamento *pag) {
    printf("\n**** INGRESSO COMPRADO ****\n\n");
    printf("\nId do Pagamento: %d\n", pag->id);
    printf("Cliente: %s\n", pag->nome);
    printf("CPF: %s\n", pag->cpf);
    printf("Filme: %s\n", pag->filme->nome);
    printf("Hora: %s\n", pag->filme->hora);
    printf("Quantidade de ingressos: %d\n", pag->quantidade);
    printf("Quantidade de inteira: %d\n", pag->ingresso_interios);
    printf("Quantidade de meia: %d\n", pag->ingresso_meia);
    printf("Numero do assento comprado: ");
    
    for (int i = 0; i < pag->quantidade; i++) {
        printf(" %0.2d ", pag->assento[i]);
    }

    printf("\nValor Total: R$%.2f\n\n", pag->valor);
    printf("****************************\n\n\n");
}

void imprimirRelatorio(struct pagamento *lista_pagamentos) {
    struct pagamento *atual = lista_pagamentos;

    while (atual != NULL) {
        printf("\n------------------------------\n");
        printf("ID: %d\n", atual->id);
        printf("Nome: %s\n", atual->nome);
        printf("CPF: %s\n", atual->cpf);
        printf("Filme: %s\n", atual->filme->nome);
        printf("Horario: %s\n", atual->filme->hora);
        printf("Quantidade de ingressos: %d\n", atual->quantidade);
        printf("Ingressos Inteiros: %d\n", atual->ingresso_interios);
        printf("Ingressos Meia: %d\n", atual->ingresso_meia);
        printf("Valor Total: R$%.2f\n", atual->valor);
        printf("Assentos: ");
        for (int i = 0; i < atual->quantidade; i++) {
            printf("%02d ", atual->assento[i]);
        }
        printf("\n------------------------------\n\n");

        atual = atual->proximo;  // Avança para o próximo pagamento
    }
}
