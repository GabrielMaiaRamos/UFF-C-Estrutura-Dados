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

    if (m_dir != NULL && m_dir->info > maior_no->info) // faz as comparacoes com a raiz
        maior_no = m_dir;
    if (m_esq != NULL && m_esq->info > maior_no->info)
        maior_no = m_esq;

    return maior_no;
}

// Escreva uma função em C que retorna o menor elemento da árvore
TAB *encontrar_menor(TAB *a)
{
    if (a == NULL)
        return NULL;
    TAB *menor_no = a;
    TAB *m_esq = encontrar_menor(a->esq);
    TAB *m_dir = encontrar_menor(a->dir);

    if (m_esq != NULL && m_esq->info < menor_no->info)
        menor_no = m_esq;
    if (m_dir != NULL && m_dir->info < menor_no->info)
        menor_no = m_dir;

    return menor_no;
}

/* Escreva uma função em C que, dadas duas árvores deste tipo, testa se estas árvores
são iguais. A função retorna um se elas são iguais e zero, caso contrário. A função
deve obedecer ao seguinte protótipo: int igual (TAB* a1, TAB* a2) */

int *igual(TAB *a1, TAB *a2)
{
    if (a1 == NULL && a2 == NULL) // se ambos forem null, eh igual (retorna 1)
        return 1;
    if (a1 != NULL || a2 != NULL) // se apenas UM for null, eh diferente (retorna 0)
        return 0;
    if (a1->info != a2->info) // se a info eh diferente, retorna 0
        return 0;

    // quando os dois forem iguais, retorna a verificacao pra cada lado, junto com um
    //  "AND" para verificar se ambos os lados sao iguais
    return igual(a1->dir, a2->dir) && igual(a1->esq, a2->esq);
}

/* Escreva uma função em C que, dada uma árvore binária qualquer, retire todos os
elementos pares da árvore original. A função deve ter o seguinte protótipo: TAB*
retira_pares (TAB* arv) */
TAB *retira_pares(TAB *arv)
{
    if (arv == NULL)
        return NULL;

    retira_pares(arv->dir);
    retira_pares(arv->esq);

    if (arv->info % 2 == 0)
    {
        // CASO A: NENHUM FILHO (NO FOLHA)
        if (arv->dir == NULL && arv->esq == NULL)
            free(arv);
        // CASO B1: SO UM FILHO NA ESQUEDA
        else if (arv->dir == NULL)
        {
            TAB *temp = arv->esq;
            free(arv);
            return temp;
        }
        // CASO B2: SO UM FILHO NA DIREITA
        else if (arv->esq == NULL)
        {
            TAB *temp = arv->dir;
            free(arv);
            return temp;
        }
        // CASO C: TEM OS DOIS FILHOS (o da esquerda vira raiz e o da direita entra no espaco vazio p direita)
        else
        {
            TAB *nova_raiz = arv->esq; // o filho da esquerda vira a raiz
            TAB *aux = nova_raiz;      // ponteiro para andar pela nova raiz
            // descer ate o galho mais a direita possivel da nova raiz
            while (aux->dir != NULL)
                aux = aux->dir;
            // aloca o filho da direita (que perdeu o no raiz) nesse local encontrado
            aux->dir = arv->dir;
            free(arv);
            return nova_raiz;
        }
    }
    return arv;
}