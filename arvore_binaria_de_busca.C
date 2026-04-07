#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int info;
    int key;
    struct no *esq;
    struct no *dir;
} TNoA;

void print_tree(TNoA *node, int tab)
{
    for (int i = 0; i < tab; i++)
        printf("-");
    if (node != NULL)
    {
        printf("%d\n", node->key);
        print_tree(node->esq, tab + 2);
        printf("\n");
        print_tree(node->dir, tab + 2);
    }
    else
        printf("vazio");
}

void pre_ordem_iterativo(TNoA *raiz)
{
    if (raiz == NULL)
        return;
    TNoA *pilha[1000];
    int topo = -1;

    pilha[++topo] = raiz;

    while (topo >= 0)
    {
        TNoA *atual = pilha[topo--];

        // Visita a raiz do subproblema atual
        printf("%d ", atual->key);

        // Empilha direita antes da esquerda
        if (atual->dir != NULL)
            pilha[++topo] = atual->dir;
        if (atual->esq != NULL)
            pilha[++topo] = atual->esq;
    }
}

void ordem_simetrica_iterativa(TNoA *raiz)
{
    if (raiz == NULL)
        return;
    TNoA *pilha[1000];
    int topo = -1;

    TNoA *atual = raiz;

    while (atual != NULL || topo >= 0)
    {
        // percorre totalmente a esquerda (adicionando na pilha)
        while (atual != NULL)
        {
            pilha[++topo] = atual;
            atual = atual->esq;
        }
        // visita o topo, printando e removendo da pilha
        atual = pilha[topo--];
        printf("%d ", atual->key);
        // passa pra direita
        atual = atual->dir;
    }
}

void pos_ordem_iterativa(TNoA *raiz)
{
    TNoA *pilha[1000];
    int topo = -1;
    TNoA *atual = raiz;
    TNoA *ultimoVisitado = NULL;

    while (atual != NULL || topo >= 0)
    {
        if (atual != NULL)
        {
            pilha[++topo] = atual;
            atual = atual->esq;
        }
        else
        {
            TNoA *peek = pilha[topo];

            if (peek->dir != NULL && ultimoVisitado != peek->dir)
            {
                atual = peek->dir;
            }
            else
            {
                printf("%d ", peek->key);
                ultimoVisitado = pilha[topo--];
            }
        }
    }
}

TNoA *busca_iterativa(TNoA *node, int key) // complexidade: altura da arvore (pior caso)
{
    TNoA *aux = node;
    while (aux != NULL)
    {
        if (aux->key == key)
            return aux;
        else if (aux->key > key)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    return NULL;
}

int busca_recursiva(TNoA *node, int key) // complexidade: altura da arvore (pior caso)
{
    if (node == NULL)
        return NULL;
    else if (node->key == key)
        return key;
    else if (node->key > key)
        return busca_recursiva(node->esq, key);
    else
        return busca_recursiva(node->dir, key);
}

TNoA *insere(TNoA *node, int key)
{
    if (node == NULL) // pra no vazio
    {
        node = (TNoA *)malloc(sizeof(TNoA));
        node->key = key;
        node->esq = NULL;
        node->dir = NULL;
    }
    else if (key < node->key)
        node->esq = insere(node->esq, key);
    else if (key > node->key)
        node->dir = insere(node->dir, key);
    else // se a chave for igual, nao pode inserir
    {
        printf("Insercao invalida! Chave ja existe!\n");
        exit(1);
    }
    return node;
}


TNoA *arvore_balanceada(TNoA *raiz, int v[], int inicio, int fim)
{
    // se o inicio ainda nao estiver passado do fim, ainda precisa fazer
    if (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        raiz = insere(raiz, v[meio]);
        arvore_balanceada(raiz, v, inicio, meio - 1); // repete pra cada lado
        arvore_balanceada(raiz, v, meio + 1, fim);
    }
    return raiz;
}

int arvore_cheia(TNoA *node)
{
    if (node == NULL)
        return 1;
    if (node->esq == NULL && node->dir == NULL)
        return 1;
    else if (node->dir != NULL && node->esq != NULL)
        return (arvore_cheia(node->esq) && arvore_cheia(node->dir));
    return 0;
}

void inverte_arvore(TNoA *node)
{
    if (node == NULL)
        return;
    // faz pro no atual
    TNoA *temp = node->dir;
    node->dir = node->esq;
    node->esq = temp;
    // repete pra ambos os ladoss
    inverte_arvore(node->esq);
    inverte_arvore(node->dir);
}

TNoA *maior(TNoA *no)
{
    if (no->dir == NULL)
        return no;
    return maior(no->dir);
}

int main()
{
    int v[7] = {1111, 2, 10, 4, 8, 6, 7};
    TNoA *raiz = NULL;

    raiz = arvore_balanceada(raiz, v, 0, 6);
    print_tree(raiz, 0);
    printf("\n\n\n");
    pos_ordem_iterativa(raiz);
    printf("\nMaior: %d", maior(raiz)->key);
    getchar();
    getchar();
    return 0;
};
