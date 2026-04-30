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

/*3. Escreva uma função em C que, dada uma árvore binária de busca qualquer, retire todos os elementos ímpares
da árvore original. A função deve ter o seguinte protótipo: TABB* retira_impares(TABB* a);*/

TABB *retira_maior(TABB *a, int *valor_substituido) // auxiliar pra retirar o no maior da esquerda e ja guardar o valor dele
{
    if (a->dir == NULL)
    {
        *valor_substituido = a->info; // pega o valor substituido
        TABB *temp = a->esq;
        free(a);
        return temp;
    }
    a->dir = retira_maior(a->dir, valor_substituido); // passa pra direita caso ainda tenha no na direita
    return a;
}

TABB *retira_impares(TABB *a)
{
    if (a == NULL)
        return NULL;

    retira_impares(a->esq);
    retira_impares(a->dir);

    if (a->info % 2 != 0)
    {
        // CASO A: NO FOLHA
        if (a->dir == NULL && a->esq == NULL)
        {
            free(a);
            return NULL;
        }
        // CASO B1: NO COM UM FILHO NA DIREITA
        else if (a->esq == NULL)
        {
            TABB *temp = a->dir;
            free(a);
            return temp;
        }
        // CASO B2: NO COM UM FILHO NA ESQUERDA
        else if (a->dir == NULL)
        {
            TABB *temp = a->esq;
            free(a);
            return temp;
        }
        // CASO C: NO COM DOIS FILHOS
        else
        {
            int valor_substituido;
            // retira o maior no da arvore da esquerda e tras o valor dele
            a->esq = retira_maior(a->esq, &valor_substituido);
            a->info = valor_substituido;
        }
    }
    else
        return a; // se for par, retorna o no sem excluir
}