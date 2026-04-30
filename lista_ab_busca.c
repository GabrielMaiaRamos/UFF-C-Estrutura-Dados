#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TABB;

/*[1] Escreva uma função em C para encontrar o maior elemento da árvore: TABB* maior(TAB *a);*/
TABB *maior(TABB *a)
{
    if (a == NULL)
        return NULL;

    TABB *aux = a;
    while (aux->dir != NULL)
        aux = aux->dir;
    return aux;
}

/*[2] Escreva uma função em C para encontrar o menor elemento da árvore: TABB* menor(TAB *a);*/
TABB *menor(TABB *a)
{
    if (a == NULL)
        return NULL;

    TABB *aux = a;
    while (aux->esq != NULL)
        aux = aux->esq;
    return aux;
}