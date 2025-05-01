#ifndef CINEMA_H    
#define CINEMA_H   

#define LINHAS 7
#define COLUNAS 10
#define CATALOGO 5

typedef struct{
    char nome[70];
    char cpf[15];
}Cliente;

typedef struct{
    char nome[70];
    char hora[6];
    int sala[LINHAS][COLUNAS];
    float valor;
}Filme;

extern Filme filmes[CATALOGO];

typedef struct pagamento pagamento;
struct pagamento{
    int id;
    char nome[70];
    char cpf[15];
    Filme *filme;
    int quantidade;
    int ingresso_interios;
    int ingresso_meia;
    float valor;
    int assento[70];
    struct pagamento *proximo;
}*pessoa;

// Protótipos originais
void mostrarFilmes();
void escolherFilme(Filme filmes[], Filme **fileme_esolhido);
float calcular_total(float inteira, float meia, Filme *film);
void Assentos(Filme *filmes);
void comprar_assentos(Cliente *cli, Filme filmes[]);
void imprimirIngresso(pagamento *pag);
void imprimirRelatorio(struct pagamento *lista_pagamentos);
void limparBuffer();

// Funções de busca e validação
pagamento* buscarIngressoBinario(pagamento *lista, int id);  // Agora implementa busca binária verdadeira
void ordenarPagamentos(pagamento **lista);
int validarCPF(const char *cpf);
int validarNome(const char *nome); 

#endif
