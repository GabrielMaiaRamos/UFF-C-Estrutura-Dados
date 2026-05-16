#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

typedef struct sNoA
{
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

typedef struct vizinho
{
    int id_vizinho;
    int peso;
    struct vizinho *prox;
} TVizinho;

typedef struct grafo
{
    int id_vertice;
    int cor;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

#define TAM_NOME 100

typedef struct Cliente
{
    int cod_cliente;
    char nome[TAM_NOME];
} TCliente;

typedef struct vetor
{
    TCliente *cli;
    int congelado;
} TVet;

int ehZigueZague(TNoA *raiz)
{
    if (raiz == NULL)
        return 1;
    while (raiz != NULL)
    {
        if (raiz->dir != NULL && raiz->esq != NULL)
            return 0;
        else if (raiz->dir != NULL)
            raiz = raiz->dir;
        else if (raiz->esq != NULL)
            raiz = raiz->esq;
        else
            return 1;
    }
    return 0;
}

int ehNaoOrientado(TGrafo *g)
{
    TGrafo *v1 = g, *v2 = NULL;
    while (v1 != NULL)
    {
        TVizinho *v1Viz = v1->prim_vizinho;
        while (v1Viz != NULL) // enquanto houverem arestas, roda
        {
            v2 = busca_vertice(g, v1Viz->id_vizinho); // encontra o vertice original desse vizinho
            TVizinho *v2Viz = busca_vizinho(v2->prim_vizinho, v1->id_vertice);

            if (v2Viz == NULL) // se NEM encontrar a aresta, nao eh ordenado
                return 0;
            if (v1Viz->peso != v2Viz->peso) // se os pesos forem diferentes, nao eh ordenado
                return 0;
            // se nao forem os casos, esta correto e passa pro proximo
            v1Viz = v1Viz->prox;
        }
        v1 = v1->prox;
    }
    return 1;
}

int main()
{
    getchar();
    getchar();
};

int selecao_substituicao(char *nome_arquivo_entrada, int tam_memoria)
{
    FILE *arq = fopen(nome_arquivo_entrada, "r");
    if (arq == NULL)
        return 0; // se nao existir, retorna 0
}