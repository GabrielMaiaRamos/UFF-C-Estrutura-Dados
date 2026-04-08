#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNoA
{
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

int zigAtual(TNoA *no, int dir)
{
    if (no == NULL)
        return 1;
    if (dir == -1) // veio da esquerda (precisa ir pra direita)
    {
        printf("no veio da esquerda %d\n", no->chave);
        if (no->dir == NULL)
            return 0;
        else
        {
            printf("vou passar pra direita agora\n");
            return zigAtual(no->dir, 1);
        }
    }
    else if (dir == 1)
    { // veio da direita (precisa ir pra esquerda)
        printf("vim da direita %d\n", no->chave);
        if (no->esq == NULL)
            return 0;
        else
        {
            printf("vou passar pra esquerda agora");
            return zigAtual(no->esq, -1);
        }
    }
    return 0;
}

int ehZigueZague(TNoA *raiz)
{
    if (raiz == NULL)
        return 0;
    if (raiz->esq != NULL && raiz->dir == NULL)
        return zigAtual(raiz->esq, -1);
    else if (raiz->esq == NULL && raiz->dir != NULL)
        return zigAtual(raiz->dir, 1);
    else
        return 0;
    return 0;
}

void imprime(TNoA *nodo, int tab)
{
    for (int i = 0; i < tab; i++)
    {
        printf("-");
    }
    if (nodo != NULL)
    {
        printf("%d\n", nodo->chave);
        imprime(nodo->esq, tab + 2);
        printf("\n");
        imprime(nodo->dir, tab + 2);
    }
    else
        printf("vazio");
}

TNoA *insere(TNoA *no, int chave)
{
    if (no == NULL)
    {
        no = (TNoA *)malloc(sizeof(TNoA));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
    }
    else if (chave < (no->chave))
        no->esq = insere(no->esq, chave);
    else if (chave > (no->chave))
    {
        no->dir = insere(no->dir, chave);
    }
    else
    {
        printf("Inserção inválida! ");
        exit(1);
    }
    return no;
}

int main(void)
{

    /* A função main lê os dados de entrada, cria a árvore e chama a função solicitada no problema
     * depois imprime o resultado solicitado
     * ELA NÃO DEVE SER MODIFICADA
     * */
    TNoA *raiz;
    raiz = NULL;

    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int valor;

    /* lê valores para criar a arvore
     * valores devem ser informados separados por traço
     * exemplo: 1-3-5-2-7-9-21-6 */
    scanf("%s", l);
    // quebra a string de entrada
    ptr = strtok(l, delimitador);
    while (ptr != NULL)
    {
        valor = atoi(ptr);
        raiz = insere(raiz, valor);
        ptr = strtok(NULL, delimitador);
    }
    imprime(raiz, 0);
    // Chama função
    printf("%d", ehZigueZague(raiz));

    getchar();
    getchar();
};