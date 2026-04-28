#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int info;
    struct ab *esq, *dir;
} TAB;

// Escreva uma função em C que faz a cópia de uma árvore
TAB *copia(TAB *a)
{
    if (a == NULL) // se for null, acabou essa linha
        return NULL;

    TAB *novo = malloc(sizeof(TAB));
    novo->info = a->info;
    novo->dir = copia(a->dir);
    novo->esq = copia(a->esq);
    return novo;
}