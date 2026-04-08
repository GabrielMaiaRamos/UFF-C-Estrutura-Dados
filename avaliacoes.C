#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNoA
{
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;
} TNoA;

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

int main()
{
    getchar();
    getchar();
};