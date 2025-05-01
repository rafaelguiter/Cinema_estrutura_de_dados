#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cinema.h"

// Vari�vel global para armazenar os pagamentos
pagamento *pessoa = NULL;

// Cat�logo de filmes pr�-definido
Filme filmes[CATALOGO] = {
    {"OS VINGADORES", "20:00", {{0}}, 35},
    {"VELOZES E FURIOSOS", "21:00", {{0}}, 25.0},
    {"VIVA LA VIDA UMA FESTA", "19:30", {{0}}, 25.0},
    {"ATE ONDE IREMOS ?", "20:00", {{0}}, 35.0},
    {"LARACROFT", "23:00", {{0}}, 40.0}
};

// Fun��o para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fun��o para mostrar a lista de filmes
void mostrarFilmes() {
    for(int i = 0; i < CATALOGO; i++) {
        printf("\n%d - %s \nHor�rio: %s\n", i+1, filmes[i].nome, filmes[i].hora);
        printf("Valor: R$ %.2f\n", filmes[i].valor);
    }
}

// Fun��o para escolher um filme
void escolherFilme(Filme filmes[], Filme **filme_escolhido) {
    int escolha;
    mostrarFilmes();
    printf("\nEscolha o filme (1-%d): ", CATALOGO);
    scanf("%d", &escolha);
    limparBuffer();
    *filme_escolhido = &filmes[escolha - 1];
}

// Fun��o para calcular o valor total
float calcular_total(float inteira, float meia, Filme *film) {
    return (inteira * film->valor) + (meia * (film->valor / 2.0));
}

// Fun��o para mostrar os assentos
void Assentos(Filme *filme) {
    printf("\n=== ASSENTOS DISPON�VEIS ===\n");
    printf("Filme: %s\n", filme->nome);
    printf("[ ] = Livre   [X] = Ocupado\n\n");
    
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%02d%s ", (i*COLUNAS)+j+1, filme->sala[i][j] ? "[X]" : "[ ]");
        }
        printf("\n");
    }
}

// Fun��o para validar d�gitos do CPF
int validarDigitosCPF(const char *cpf) {
    for (int i = 0; cpf[i] != '\0'; i++) {
        if (!(cpf[i] >= '0' && cpf[i] <= '9') && cpf[i] != '.' && cpf[i] != '-') {
            return 0; // Caractere inv�lido
        }
    }
    return 1; // CPF v�lido (formato)
}

// Fun��o principal para comprar assentos
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
        printf("Erro ao alocar mem�ria!\n");
        return;
    }

    escolherFilme(filmes, &filme_escolhido);
    Assentos(filme_escolhido);

    do {
        printf("\nQuantos ingressos deseja? (1-70): ");
        scanf("%d", &comprar);
        limparBuffer();
        if (comprar < 1 || comprar > 70) printf("Quantidade inv�lida!\n");
    } while (comprar < 1 || comprar > 70);

    while(i < comprar) {
        printf("\nEscolha o assento (1-%d): ", capacidade);
        scanf("%d", &cadeira);
        limparBuffer();

        lugar = cadeira - 1;
        lin = lugar / COLUNAS;
        col = lugar % COLUNAS;

        if (filme_escolhido->sala[lin][col] == 0) {
            filme_escolhido->sala[lin][col] = 1;
            ass_ingresso[i] = cadeira;
            i++;
            system("cls");
            Assentos(filme_escolhido);
        } else {
            printf("Assento %d ocupado!\n", cadeira);
        }
    }

    do {
        printf("\nNome: ");
        fgets(cli->nome, sizeof(cli->nome), stdin);
        cli->nome[strcspn(cli->nome, "\n")] = '\0';
        if (strlen(cli->nome) < 3) printf("Nome muito curto!\n");
    } while (strlen(cli->nome) < 3);

    do {
        printf("\nCPF (somente n�meros ou formato 123.456.789-09): ");
        fgets(cli->cpf, sizeof(cli->cpf), stdin);
        cli->cpf[strcspn(cli->cpf, "\n")] = '\0';
        
        if (!validarCPF(cli->cpf) || !validarDigitosCPF(cli->cpf)) {
            printf("CPF inv�lido! Use 11 d�gitos ou formato 123.456.789-09\n");
        }
    } while (!validarCPF(cli->cpf) || !validarDigitosCPF(cli->cpf));

    printf("\nQuantos s�o meia-entrada? ");
    scanf("%f", &meia);
    limparBuffer();

    if (meia < 0 || meia > comprar) {
        printf("Quantidade inv�lida de meias!\n");
        meia = 0;
    }
    inteira = comprar - meia;
    total = calcular_total(inteira, meia, filme_escolhido);

    system("cls");
    printf("\n=== RESUMO DA COMPRA ===\n");
    printf("Filme: %s\n", filme_escolhido->nome);
    printf("Assentos: ");
    for (int i = 0; i < comprar; i++) {
        printf("%02d ", ass_ingresso[i]);
    }
    printf("\nTotal: R$ %.2f\n", total);

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
}

// Fun��o para imprimir um ingresso
void imprimirIngresso(pagamento *pag) {
    if (pag == NULL) {
        printf("Ingresso inv�lido!\n");
        return;
    }
    printf("\n=== INGRESSO ===\n");
    printf("ID: %d\n", pag->id);
    printf("Filme: %s\n", pag->filme->nome);
    printf("Cliente: %s\n", pag->nome);
    printf("CPF: %s\n", pag->cpf);
    printf("Assentos: ");
    for (int i = 0; i < pag->quantidade; i++) {
        printf("%02d ", pag->assento[i]);
    }
    printf("\nValor: R$ %.2f\n", pag->valor);
}

// Fun��o para gerar relat�rio
void imprimirRelatorio(pagamento *lista_pagamentos) {
    if (lista_pagamentos == NULL) {
        printf("Nenhum ingresso vendido!\n");
        return;
    }
    printf("\n=== RELAT�RIO ===\n");
    while (lista_pagamentos != NULL) {
        imprimirIngresso(lista_pagamentos);
        lista_pagamentos = lista_pagamentos->proximo;
    }
}

// Fun��o auxiliar para contar elementos na lista - NOVA FUN��O ADICIONADA
int contarElementos(pagamento *lista) {
    int count = 0;
    while (lista != NULL) {
        count++;
        lista = lista->proximo;
    }
    return count;
}

// Fun��o de compara��o para qsort - NOVA FUN��O ADICIONADA
int compararPagamentos(const void *a, const void *b) {
    pagamento *pagA = *(pagamento **)a;
    pagamento *pagB = *(pagamento **)b;
    return (pagA->id - pagB->id);
}

// Fun��o de busca bin�ria - FUN��O COMPLETAMENTE REFEITA
pagamento* buscarIngressoBinario(pagamento *lista, int id) {
    if (lista == NULL) return NULL;
    
    // 1. Contar elementos na lista
    int tamanho = contarElementos(lista);
    
    // 2. Criar array tempor�rio de ponteiros
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
    
    // 5. Implementa��o da busca bin�ria
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
    
    free(array); // Liberar mem�ria do array tempor�rio
    return resultado;
}

// Fun��o para ordenar pagamentos (mantida por compatibilidade, mas n�o � mais necess�ria)
void ordenarPagamentos(pagamento **lista) {
    if (*lista == NULL) return;
    
    int trocado;
    pagamento *ptr1;
    pagamento *lptr = NULL;
    
    do {
        trocado = 0;
        ptr1 = *lista;
        
        while (ptr1->proximo != lptr) {
            if (ptr1->id > ptr1->proximo->id) {
                int temp = ptr1->id;
                ptr1->id = ptr1->proximo->id;
                ptr1->proximo->id = temp;
                trocado = 1;
            }
            ptr1 = ptr1->proximo;
        }
        lptr = ptr1;
    } while (trocado);
}

// Fun��o para validar formato do CPF
int validarCPF(const char *cpf) {
    return (strlen(cpf) == 11 || strlen(cpf) == 14);
}

// Fun��o para validar nome
int validarNome(const char *nome) {
    return (strlen(nome) >= 3 && strlen(nome) <= 70);
}
