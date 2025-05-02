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


// funcoes

void limparBuffer();
void limpartela();
void mostrarFilmes();
void escolherFilme(Filme filmes[], Filme **filme_escolhido);
float calcular_total(float inteira, float meia, Filme *film);
void Assentos(Filme *filme);
void comprar_assentos(Cliente *cli, Filme filmes[]);
void imprimirIngresso(pagamento *pag);
void imprimirRelatorio(struct pagamento *lista_pagamentos);
int contarElementos(pagamento *lista);
int compararPagamentos(const void *a, const void *b);
int ordenarDecrescente(const void *a, const void *b);
int compararPorMeiaEntrada(const void *a, const void *b);
int compararPorInteiraEntrada(const void *a, const void *b);
pagamento* buscarIngressoBinario(pagamento *lista, int id);
void imprimirRelatorioOrdenado(pagamento *lista_pagamentos);
void imprimir_Relatorio_Id_Decrescente(pagamento *lista_pagamentos);
void imprimir_Relatorio_meia_primeiro(pagamento *lista_pagamentos);
void imprimir_Relatorio_inteira_primeiro(pagamento *lista_pagamentos);
int validarDigitosCPF(const char *cpf);
int validarCPF(const char *cpf);

#endif
