#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

double *vizinhancas = NULL;
int numCidades = 0;
double menor_vizinhanca;


// Estrutura para representar uma cidade


Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL) {
        printf("ERRO: não foi possível alocar memória para a estrada!\n");
        exit(1);
    }

    fscanf(arquivo, "%d", &estrada->T);
    if (estrada->T <= 3 || estrada->T >= 1000000) {
        printf("Valor de T inválido\n");
        fclose(arquivo);
        free(estrada);
        return NULL;
    }

    fscanf(arquivo, "%d", &estrada->N);
    if (estrada->N < 2 || estrada->N >= 10000) {
        printf("Valor de N inválido\n");
        fclose(arquivo);
        free(estrada);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (estrada->C == NULL) {
        printf("ERRO: não foi possível alocar memória para as cidades!\n");
        free(estrada);
        exit(1);
    }

    // Ler as informações das cidades do arquivo
    int i,j;
    for ( i = 0; i < estrada->N; i++) {
        fscanf(arquivo, "%d %[^\n]", &estrada->C[i].Posicao, estrada->C[i].Nome);

        // Ordenar as cidades em ordem crescente com base na posição
        for ( j = i; j > 0 && estrada->C[j].Posicao < estrada->C[j - 1].Posicao; j--) {
            // Trocar as posições das cidades
            Cidade temp = estrada->C[j];
            estrada->C[j] = estrada->C[j - 1];
            estrada->C[j - 1] = temp;
        }
    }
    
    fclose(arquivo);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
	
	Estrada *estrada = getEstrada(nomeArquivo);
	
    int tamanho_fronteira = estrada->N - 1;
    float fronteira[tamanho_fronteira];
    double vizinhanca[estrada->N];
	int i;
    for ( i = 0; i < estrada->N - 1; i++) {
        fronteira[i] = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
    }

    vizinhanca[0] = fronteira[0];
    vizinhanca[estrada->N - 1] = estrada->T - fronteira[tamanho_fronteira - 1];

    for ( i = 1; i < tamanho_fronteira; i++) {
        vizinhanca[i] = fronteira[i] - fronteira[i - 1];
    }

    double menorVizinhanca = vizinhanca[0];
	
    for ( i = 1; i < estrada->N; i++) {
        if (vizinhanca[i] < menorVizinhanca) {
            menorVizinhanca = vizinhanca[i];
        }
    }

    
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
	
	Estrada *estrada = getEstrada(nomeArquivo);
	
    int tamanho_fronteira = estrada->N - 1;
    float fronteira[tamanho_fronteira];
    double vizinhanca[estrada->N];
	int i;
    for ( i = 0; i < estrada->N - 1; i++) {
        fronteira[i] = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
    }

    vizinhanca[0] = fronteira[0];
    vizinhanca[estrada->N - 1] = estrada->T - fronteira[tamanho_fronteira - 1];

    for (i = 1; i < tamanho_fronteira; i++) {
        vizinhanca[i] = fronteira[i] - fronteira[i - 1];
    }

    double menorVizinhanca = vizinhanca[0];
    int cidadeMenorVizinhanca = 0;

    for (i = 1; i < estrada->N; i++) {
        if (vizinhanca[i] < menorVizinhanca) {
            menorVizinhanca = vizinhanca[i];
            cidadeMenorVizinhanca = i;
        }
    }

    char* nomeCidade = strdup(estrada->C[cidadeMenorVizinhanca].Nome);

    // Libere a memória alocada para a estrada e cidades
    free(estrada->C);
    free(estrada);

    return nomeCidade;
    
}
