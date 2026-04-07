#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int info;
    int key;
    struct no *esq;
    struct no *dir;
} TNoA;

TNoA *exclusao(TNoA *node, int key)
{
    if (node == NULL)
        return NULL;
    // procura o nó pra excluir
    while (node != NULL)
    {
        if (node->key == key)
            break;
        else if (node->key < key)
            node = node->dir;
        else
            node = node->esq;
    }
    if (node == NULL)
        return NULL;

    if (node->dir != NULL && node->esq != NULL)
    {
        TNoA *maior = node->esq; // maior da esquerda
        while (maior->dir != NULL)
            maior = maior->dir;
        node->key = maior->key;                      // copia apenas a key
        node->esq = exclusao(node->esq, maior->key); // exclui o original
    }
    else
    {
        TNoA *temp = node;
        if (node->dir != NULL)
            node = node->dir;
        else
            node = node->esq;
        free(temp);
    }
    return node;
}

int main()
{
    getchar();
    getchar();
}