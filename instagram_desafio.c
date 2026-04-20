#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vizinho
{
    char nome[10];
    struct vizinho *prox;
} TVizinho;

typedef struct grafo
{
    char nome[10];
    int idade;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

TGrafo *insere_vertice(TGrafo *g, char *nome, int idade)
{
    TGrafo *vertice = (TGrafo *)malloc(sizeof(TGrafo));
    strcpy(vertice->nome, nome);
    vertice->idade = idade;
    vertice->prox = g;
    vertice->prim_vizinho = NULL;
    return vertice;
}

TGrafo *busca_vertice(TGrafo *vertice, char *nome)
{
    while ((vertice != NULL) && (strcmp(vertice->nome, nome) != 0))
    {
        vertice = vertice->prox;
    }
    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, char *nome)
{
    while ((vizinho != NULL) && (strcmp(vizinho->nome, nome) != 0))
    {
        vizinho = vizinho->prox;
    }
    return vizinho;
}

void insere_aresta(TGrafo *g, char *nome_origem, char *nome_destino)
{
    TGrafo *vertice = busca_vertice(g, nome_origem);
    TVizinho *vizinho = (TVizinho *)malloc(sizeof(TVizinho));
    strcpy(vizinho->nome, nome_destino);
    vizinho->prox = vertice->prim_vizinho;
    vertice->prim_vizinho = vizinho;
}

void imprime(TGrafo *vertice)
{
    while (vertice != NULL)
    {
        printf("Pessoa: %s - %d anos\n", vertice->nome, vertice->idade);
        printf("Segue: ");
        TVizinho *vizinho = vertice->prim_vizinho;
        while (vizinho != NULL)
        {
            printf("%s ", vizinho->nome);
            vizinho = vizinho->prox;
        }
        printf("\n\n");
        vertice = vertice->prox;
    }
}

int numero_seguidos(TGrafo *g, char *nome)
{
    int seguidos = 0;
    TGrafo *aux = g;
    aux = busca_vertice(aux, nome); // busca o nome
    if (aux == NULL)                // se for null para
        return 0;

    TVizinho *auxViz = aux->prim_vizinho;
    while (auxViz != NULL)
    { // comeca um loop buscando os todos vizinhos
        seguidos++;
        auxViz = auxViz->prox; // passa para o prox
    }
    return seguidos;
}

int seguidores(TGrafo *g, char *nome, int imprime)
{
    int seguidores = 0;
    TGrafo *aux = g;
    while (aux != NULL)
    { // enquato houver vertices, percorre
        if (busca_vizinho(aux->prim_vizinho, nome) != NULL)
        { // se achar um vizinho com o nome, conta +1
            seguidores++;
            if (imprime) // se a flag for 1, printa
                printf("%s ", aux->nome);
        }
        aux = aux->prox; // passa para o prox vertice
    }
    if (imprime)
        printf("\n"); // quebra de linha pra nao bugar o output
    return seguidores;
}

TGrafo *mais_popular(TGrafo *g)
{
    int fas = 0, maior = -1;
    TGrafo *aux = g, *popular = NULL;
    while (aux != NULL)
    {
        fas = seguidores(g, aux->nome, 0); // usa a funcao que ja conta os seguidores
        if (fas > maior)                   // se a qnt de seguidores for maior que o MAIOR, muda
        {
            maior = fas;
            popular = aux;
        }
        aux = aux->prox; // passa pro prox vertice
    }
    return popular;
}

int segue_mais_velho(TGrafo *g, int imprime)
{
    int flag = 0, quant = 0;
    TGrafo *aux = g, *pessoa = NULL;
    while (aux != NULL)
    {
        TVizinho *auxViz = aux->prim_vizinho;
        if (auxViz != NULL) // se tiver algum vizinho, considero primeiro que a flag é true, e o while vai provar o contrario
            flag = 1;
        while (auxViz != NULL) // percorre todos os vizinhos
        {
            pessoa = busca_vertice(g, auxViz->nome); // acha o vertice daquele vizinho
            if (pessoa->idade <= aux->idade)
            { // se alguem for mais jovem, quebra e muda a flag
                flag = 0;
                break;
            }
            auxViz = auxViz->prox;
        }
        if (flag)
        {
            quant++;
            if (imprime)
                printf("%s ", aux->nome);
        }
        aux = aux->prox;
    }
    return quant;
}

void libera_vizinho(TVizinho *vizinho)
{
    if (vizinho != NULL)
    {
        libera_vizinho(vizinho->prox);
        free(vizinho);
    }
}

void libera_vertice(TGrafo *vertice)
{
    if (vertice != NULL)
    {
        libera_vizinho(vertice->prim_vizinho);
        libera_vertice(vertice->prox);
        free(vertice);
    }
}

int main()
{
    /* A função main lê os dados de entrada, cria o grafo e chama as funções solicitadas no problema
     * depois imprime os resultados solicitados
     * ELA NÃO DEVE SER MODIFICADA
     * */
    int num_vertices, num_arestas;
    char nome[30];
    char origem[30], destino[30];
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int idade;
    int i;
    TGrafo *g = NULL;

    // le numero de vertices
    scanf("%d", &num_vertices);
    // le e cria os vertices
    for (i = 0; i < num_vertices; i++)
    {
        scanf("%s", l);
        // quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(nome, ptr);
        // printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        idade = atoi(ptr);
        g = insere_vertice(g, nome, idade);
    }

    // Le numero de arestas e depois le os dados de cada aresta
    // Cria as arestas no grafo
    scanf("%d", &num_arestas);
    for (i = 0; i < num_arestas; i++)
    {
        scanf("%s", l);
        // quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(origem, ptr);
        // printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        strcpy(destino, ptr);
        insere_aresta(g, origem, destino);
    }

    // Le nome de pessoa
    scanf("%s", nome);

    // Encontra o número de seguidos dessa pessoa
    printf("SEGUIDOS por %s: %d\n", nome, numero_seguidos(g, nome));

    // Encontra os seguidores de uma determinada pessoa
    printf("SEGUIDORES de %s:\n", nome);
    seguidores(g, nome, 1);

    TGrafo *p;

    // Encontra mais popular
    p = mais_popular(g);
    printf("MAIS POPULAR: %s\n", p->nome);

    // Encontra as pessoas que seguem apenas pessoas mais velhas
    printf("SEGUEM APENAS PESSOAS MAIS VELHAS:\n");
    segue_mais_velho(g, 1);

    libera_vertice(g);

    getchar();
    getchar();
}