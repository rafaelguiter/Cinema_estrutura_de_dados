#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cinema.h"

pagamento *pessoa = NULL;

Filme filmes[CATALOGO] = {
    {"OS VINGADORES", "20:00", {{0}}, 35},
    {"VELOZES E FURIOSOS", "21:00", {{0}}, 25.0},
    {"VIVA LA VIDA UMA FESTA", "19:30", {{0}}, 25.0},
    {"ATE ONDE IREMOS ?", "20:00", {{0}}, 35.0},
    {"LARACROFT", "23:00", {{0}}, 40.0}
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

    printf("\nMapa dos assentos para o filme '  %s  '  Ingresso R$%.2f \n\n", filme->nome, filme->valor);

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
    int meia = 0, inteira = 0;
    float total = 0;
    Filme *filme_escolhido;
    
    
    pagamento *pag_novo = (pagamento *)malloc(sizeof(pagamento));
    if (pag_novo == NULL) {
        printf("Erro ao alocar memória para novo pagamento.\n");
        return;
    }


    escolherFilme(filmes, &filme_escolhido);

    Assentos(filme_escolhido);

    printf("\nQuantos ingressos deseja comprar ?  ");
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


    do {
        printf("\nNome: ");
        fgets(cli->nome, sizeof(cli->nome), stdin);
        cli->nome[strcspn(cli->nome, "\n")] = '\0';
        if (strlen(cli->nome) < 3) printf("Nome muito curto!\n");
    } while (strlen(cli->nome) < 3);
    


    do {
        printf("\nCPF(somente numeros ou formato 123.456.789-09): ");
        fgets(cli->cpf, sizeof(cli->cpf), stdin);
        cli->cpf[strcspn(cli->cpf, "\n")] = '\0';
        
        if (!validarCPF(cli->cpf) || !validarDigitosCPF(cli->cpf)) {

            limpartela();
            Assentos(filme_escolhido);
            printf("\nCPF invalido! Use 11 digitos ou formato 123.456.789-09\n");
        }
    } while (!validarCPF(cli->cpf) || !validarDigitosCPF(cli->cpf));
    
    


    do {
        printf("\nQuantos ingressos sao meia entrada? ");
        scanf("%d", &meia);
        limparBuffer();
    
        if (meia < 0) {

            limpartela();
            Assentos(filme_escolhido);
            printf("\nQuantidade de meia entrada invalida!\n");

        } else if (meia > comprar) {

            limpartela();
            Assentos(filme_escolhido);

            printf("\nA quantidade de ingresso de meia entrada ultrapassa os ingressos comprados\n");
        }
    } while (meia < 0 || meia > comprar);


    
    inteira = comprar - meia;
    total = calcular_total(inteira, meia, filme_escolhido);




    limpartela();
    Assentos(filme_escolhido);

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
    
    
    pag_novo->proximo = pessoa;
    pessoa = pag_novo;

    imprimirIngresso(pessoa);
    

}

void imprimirIngresso(pagamento *pag) {
    printf("\n**** INGRESSO COMPRADO ****\n");
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
    printf("****************************\n\n");
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

int contarElementos(pagamento *lista) {
    int count = 0;
    while (lista != NULL) {
        count++;
        lista = lista->proximo;
    }
    return count;
}

int compararPagamentos(const void *a, const void *b) {
    pagamento *pag1 = *(pagamento **)a;
    pagamento *pag2 = *(pagamento **)b;
    return pag1->id - pag2->id;
}

int ordenarDecrescente(const void *a, const void *b) {
    pagamento *pag1 = *(pagamento **)a;
    pagamento *pag2 = *(pagamento **)b;
    return pag2->id - pag1->id;
}

int compararPorMeiaEntrada(const void *a, const void *b) {
    pagamento *pag1 = *(pagamento **)a;
    pagamento *pag2 = *(pagamento **)b;

    if (pag1->ingresso_meia > 0 && pag2->ingresso_meia == 0) return -1;
    if (pag1->ingresso_meia == 0 && pag2->ingresso_meia > 0) return 1;
    return 0;
}

int compararPorInteiraEntrada(const void *a, const void *b) {
    pagamento *pag1 = *(pagamento **)a;
    pagamento *pag2 = *(pagamento **)b;

    if (pag1->ingresso_meia == 0 && pag2->ingresso_meia > 0) return -1;
    if (pag1->ingresso_meia > 0 && pag2->ingresso_meia == 0) return 1;
    return 0;
}

pagamento* buscarIngressoBinario(pagamento *lista, int id) {
    if (lista == NULL) return NULL;
    
    // 1. Contar elementos na lista
    int tamanho = contarElementos(lista);
    
    // 2. Criar array temporário de ponteiros
    pagamento **array = (pagamento **)malloc(tamanho * sizeof(pagamento *));
    if (array == NULL) return NULL;
    
    // 3. Preencher array com os elementos da lista
    pagamento *atual = lista;
    for (int i = 0; i < tamanho && atual != NULL; i++) {
        array[i] = atual;
        atual = atual->proximo;
    }
    
    // 4. Ordenar array por ID
    qsort(array, tamanho, sizeof(pagamento *), compararPagamentos);
    
    // 5. Implementação da busca binária
    int esquerda = 0;
    int direita = tamanho - 1;
    pagamento *resultado = NULL;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        
        if (array[meio]->id == id) {
            resultado = array[meio];
            break;
        }
        
        if (array[meio]->id < id) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    free(array); // Liberar memória do array temporário
    return resultado;
}

void imprimirRelatorioOrdenado(pagamento *lista_pagamentos) {
    int tamanho = contarElementos(lista_pagamentos);
    if (tamanho == 0) {
        printf("Nenhum ingresso vendido ainda!\n");
        return;
    }

    // Criar array temporário de ponteiros para ordenar
    pagamento **array = (pagamento **)malloc(tamanho * sizeof(pagamento *));
    if (array == NULL) {
        printf("Erro ao alocar memória para ordenação do relatório.\n");
        return;
    }

    pagamento *atual = lista_pagamentos;
    for (int i = 0; i < tamanho && atual != NULL; i++) {
        array[i] = atual;
        atual = atual->proximo;
    }

    // Ordenar por ID
    qsort(array, tamanho, sizeof(pagamento *), compararPagamentos);

    // Imprimir relatório ordenado
    printf("\n   *****   RELATORIO ORDENADO POR ID   *****   \n\n");
    for (int i = 0; i < tamanho; i++) {
        pagamento *pag = array[i];
        
        printf("\nID: %d\n", pag->id);
        printf("Nome: %s\n", pag->nome);
        printf("CPF: %s\n", pag->cpf);
        printf("Filme: %s\n", pag->filme->nome);
        printf("Horario: %s\n", pag->filme->hora);
        printf("Quantidade de ingressos: %d\n", pag->quantidade);
        printf("Ingressos Inteiros: %d\n", pag->ingresso_interios);
        printf("Ingressos Meia: %d\n", pag->ingresso_meia);
        printf("Valor Total: R$%.2f\n", pag->valor);
        printf("Assentos: ");
        for (int j = 0; j < pag->quantidade; j++) {
            printf("%02d ", pag->assento[j]);
        }
        printf("\n------------------------------\n");
    }

    free(array); // Liberar memória
}

void imprimir_Relatorio_Id_Decrescente(pagamento *lista_pagamentos) {
    int tamanho = contarElementos(lista_pagamentos);
    if (tamanho == 0) {
        printf("Nenhum pagamento encontrado.\n");
        return;
    }

    // Criar array de ponteiros
    pagamento **array = malloc(tamanho * sizeof(pagamento *));
    if (array == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    pagamento *atual = lista_pagamentos;
    for (int i = 0; i < tamanho && atual != NULL; i++) {
        array[i] = atual;
        atual = atual->proximo;
    }

    // Ordenar array por ID decrescente
    qsort(array, tamanho, sizeof(pagamento *), ordenarDecrescente);

    // Imprimir relatório ordenado
    printf("\n\n  *****    RELATORIO ORDENADO POR ID DECRESCENTE   *****  \n\n");
    for (int i = 0; i < tamanho; i++) {
        pagamento *p = array[i];

        
        printf("\nID: %d\n", p->id);
        printf("Nome: %s\n", p->nome);
        printf("CPF: %s\n", p->cpf);
        printf("Filme: %s\n", p->filme->nome);
        printf("Horário: %s\n", p->filme->hora);
        printf("Quantidade Ingressos: %d \n", p->quantidade);
        printf("Ingressos Inteiro: %d \n", p->ingresso_interios);
        printf("Ingressos meia: %d \n", p->ingresso_meia);
        printf("Valor: R$%.2f\n", p->valor);
        printf("Assentos: ");
        for (int j = 0; j < p->quantidade; j++) {
            printf("%02d ", p->assento[j]);
        }
        printf("\n---------------------------\n");
    }

    free(array);
}

void imprimir_Relatorio_meia_primeiro(pagamento *lista_pagamentos) {
    int tamanho = contarElementos(lista_pagamentos);
    if (tamanho == 0) {
        printf("Nenhum pagamento encontrado.\n");
        return;
    }

    pagamento **array = malloc(tamanho * sizeof(pagamento *));
    if (array == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    pagamento *atual = lista_pagamentos;
    for (int i = 0; i < tamanho && atual != NULL; i++) {
        array[i] = atual;
        atual = atual->proximo;
    }

    qsort(array, tamanho, sizeof(pagamento *), compararPorMeiaEntrada);

    int encontrou = 0, total = 0, qtd =0;
    float valor=0, pagar=0;

    printf("\n***** RELATORIO - MEIA ENTRADA *****\n\n\n");
    for (int i = 0; i < tamanho; i++) {
        pagamento *p = array[i];

        if(p->ingresso_meia > 0){
        
        printf("ID: %d | Nome: %s | Ingresso: R$%.2f |  Meia: %d\n", p->id, p->nome,(p->filme->valor / 2),p->ingresso_meia);
        printf("--------------------------------------------------------------------------------\n");

        total += p->ingresso_meia;
        qtd = p->ingresso_meia;
        valor = p->filme->valor / 2;
        pagar += qtd * valor; 
        encontrou = 1;
    }
}

if(!encontrou){
    printf("\n\n Nenhum pagamento com meia entrada foi encontrado\n\n");
}else{
    printf("\n\nO numero total de meia entrada comprada foi - %d", total);
    printf("\n\nO valor total arrecadado foi - R$%.2f", pagar);
}

    free(array);
}

void imprimir_Relatorio_inteira_primeiro(pagamento *lista_pagamentos) {
    int tamanho = contarElementos(lista_pagamentos);
    if (tamanho == 0) {
        printf("Nenhum pagamento encontrado.\n");
        return;
    }

    pagamento **array = malloc(tamanho * sizeof(pagamento *));
    if (array == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    pagamento *atual = lista_pagamentos;
    for (int i = 0; i < tamanho && atual != NULL; i++) {
        array[i] = atual;
        atual = atual->proximo;
    }

    qsort(array, tamanho, sizeof(pagamento *), compararPorInteiraEntrada);

    printf("\n***** RELATORIO - ENTRADA INTEIRA *****\n\n\n");

    int encontrou = 0, total = 0, qtd = 0;
    float valor=0, pagar=0;

    for (int i = 0; i < tamanho; i++) {
        pagamento *p = array[i];

        if (p->ingresso_meia >= 0 && p->ingresso_interios > 0) {

        printf("ID: %d | Nome: %s | Ingresso: R$%.2f |  Inteira: %d\n", p->id, p->nome,p->filme->valor,p->ingresso_interios);
        printf("------------------------------------------------------------------------------------\n");
        
        total += p->ingresso_interios;
        qtd = p->ingresso_interios;
        valor = p->filme->valor;
        pagar += qtd * valor;
        encontrou = 1;
    }
}

if(!encontrou){
    printf("\n\n Nenhum pagamento entrada inteira foi encontrado\n\n");
}else{
    printf("\n\nO numero total de entradas Inteiras compradas foi  -  %d", total);
    printf("\n\nO valor total arrecadado foi - R$%.2f", pagar);
}

    free(array);
}

int validarDigitosCPF(const char *cpf) {
    for (int i = 0; cpf[i] != '\0'; i++) {
        if (!(cpf[i] >= '0' && cpf[i] <= '9') && cpf[i] != '.' && cpf[i] != '-') {
            return 0;
        }
    }
    return 1;
}

int validarCPF(const char *cpf) {
    return (strlen(cpf) == 11 || strlen(cpf) == 14);
}


