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

// so pra nao dar erro
TVet *le_cliente(FILE *arq)
{
    return NULL;
}

char *gera_nome_particao(int particao)
{
    return NULL;
}

void salva_cliente(TCliente *cliente, FILE *arq_part)
{
    return;
}
//===//

int selecao_substituicao(char *nome_arquivo_entrada, int tam_memoria)
{
    FILE *arq = fopen(nome_arquivo_entrada, "r");
    if (arq == NULL)
        return 0; // se nao existir, retorna 0

    TVet *memoria = (TVet *)malloc(tam_memoria * sizeof(TVet)); // aloca o vetor com o tamanho

    int reg_validos = 0; // quantos registros que podem ser usados na memoria

    for (int i = 0; i < tam_memoria; i++) // comeca a ler a memoria (com os primeiros registros)
    {
        memoria[i].cli = le_cliente(arq);
        if (memoria[i].cli != NULL)
        {
            memoria[i].congelado = 0; // descongela
            reg_validos += 1;
        }
        else
            memoria[i].congelado = 1; // se for vazio, congela
    }

    // primeira particao
    int particao = 1;
    char *nome_particao = gera_nome_particao(particao);
    FILE *arq_part = fopen(nome_particao, "w");

    // ler todo o arquivo
    while (reg_validos > 0)
    {
        int idx_menor = -1;
        // acha o INDICE do menor elemento (obs: nunca procura entre os congelados)
        for (int i = 0; i < tam_memoria; i++)
        {
            if (memoria[i].cli != NULL && memoria[i].congelado == 0) // se nao for null E nao estive congelado
            {
                if (idx_menor == -1) // se o index for -1, é o primeiro elemento, entao é o menor
                    idx_menor = i;
                if (memoria[i].cli->cod_cliente < memoria[idx_menor].cli->cod_cliente)
                    idx_menor = i; // ve qual eh o menor e vai guardando o index
            }
        }

        if (idx_menor == -1) // se for -1: nao trocou em nenhum momento, entao todos estao congelados
        // reiniciamos o que foi feito para um novo arquivo de particao, e depois voltamos pro comeco do while
        {
            fclose(arq_part); // fecha a particao
            // abre a proxima (mesma forma que foi feita na primeira vez)
            particao++;
            nome_particao = gera_nome_particao(particao);
            arq_part = fopen(nome_particao, "w");

            for (int i = 0; i < tam_memoria; i++) // descongela TODOS pra reiniciar
            {
                if (memoria[i].cli != NULL)
                    memoria[i].congelado = 0;
            }
        }
        else
        {
            // se mudou o index, entao escreve o menor na particao
            salva_cliente(memoria[idx_menor].cli, arq_part);
            int chave_salva = memoria[idx_menor].cli->cod_cliente;
            free(memoria[idx_menor].cli);

            memoria[idx_menor].cli = le_cliente(arq); // le o proximo cliente direto
            if (memoria[idx_menor].cli == NULL)       // se chegou ao fim do arquivo, um cliente a menos
                reg_validos--;
            else
            {
                // logica de congelar
                if (memoria[idx_menor].cli->cod_cliente < chave_salva)
                    memoria[idx_menor].congelado = 1;
                else
                    memoria[idx_menor].congelado = 0;
            }
        }
    }
    fclose(arq);
    fclose(arq_part);
    free(memoria);

    return particao; // total de particoes
}

int main()
{
    getchar();
    getchar();
};
