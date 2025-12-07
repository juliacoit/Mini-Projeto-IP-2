#ifndef TERRENOS_H
#define TERRENOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRENOS 100

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    char nome[50];
    char cpf[15];
    Data data_nascimento;
    char telefone[15];
} Pessoa;

typedef struct {
    int id;
    Pessoa dono;
    Data data_compra;
    float largura;
    float comprimento;
    float area;
    float preco_m2;
    float valor_total;
    int ocupado;
} Terreno;

void inicializarVetor(Terreno *lista[]);
void limparBuffer();
int buscarPosicaoLivre(Terreno *lista[]);
int buscarPorID(Terreno *lista[], int id);

void criarTerreno(Terreno *lista[]);
void editarTerreno(Terreno *lista[]);
void removerTerreno(Terreno *lista[]);
void mostrarPorID(Terreno *lista[]);
void mostrarEstatisticas(Terreno *lista[]);

// Arquivos
void salvarDados(Terreno *lista[], char *nomeArquivo);
void carregarDados(Terreno *lista[], char *nomeArquivo);
void liberarMemoria(Terreno *lista[]);

#endif