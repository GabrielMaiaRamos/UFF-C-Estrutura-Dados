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

    TAB *novo = malloc(sizeof(TAB)); // aloca espaco na memoria e preenche o novo no
    novo->info = a->info;
    novo->dir = copia(a->dir); // preenche a direita e a esquerda recursivamente
    novo->esq = copia(a->esq);
    return novo;
}

/*Escreva uma função em C que faz o espelho de uma árvore (o que está a esquerda
na árvore original, estará a direita no espelho, e vice-versa) */
TAB *espelho(TAB *a)
{
    if (a == NULL)
        return NULL;

    TAB *temp = a->esq;
    a->esq = a->dir;
    a->dir = temp;

    espelho(a->dir);
    espelho(a->esq);
}

// Escreva uma função em C que retorna o maior elemento da árvore
TAB *encontrar_maior(TAB *a)
{
    if (a == NULL)
        return NULL;

    TAB *maior_no = a;

    TAB *m_esq = encontrar_maior(a->esq); // acha os maiores da esq e direita
    TAB *m_dir = encontrar_maior(a->dir);

    if (m_dir != NULL && m_dir > maior_no) // faz as comparacoes com a raiz
        maior_no = m_dir;
    if (m_esq != NULL && m_esq > maior_no)
        maior_no = m_esq;

    return maior_no;
}