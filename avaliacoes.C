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
        if (no->dir == NULL)
            return 0;
        else
            return zigAtual(no->dir, 1);
    }
    else if (dir == 1) // veio da direita (precisa ir pra esquerda)
        if (no->esq == NULL)
            return 0;
        else
            return zigAtual(no->esq, -1);
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

int main()
{
    getchar();
    getchar();
};