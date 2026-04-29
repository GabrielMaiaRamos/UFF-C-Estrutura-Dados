#include <stdio.h>
#include <stdlib.h>

typedef struct ab
{
    int cor; // pro ex7
    int info;
    struct ab *esq, *dir;
} TAB;

//[1] Escreva uma função em C que faz a cópia de uma árvore
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

/*[2] Escreva uma função em C que faz o espelho de uma árvore (o que está a esquerda
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

//[3] Escreva uma função em C que retorna o maior elemento da árvore
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

//[4] Escreva uma função em C que retorna o menor elemento da árvore
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

/*[5] Escreva uma função em C que, dadas duas árvores deste tipo, testa se estas árvores
são iguais. A função retorna um se elas são iguais e zero, caso contrário. A função
deve obedecer ao seguinte protótipo: int igual (TAB* a1, TAB* a2) */

int igual(TAB *a1, TAB *a2)
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

/*[6] Escreva uma função em C que, dada uma árvore binária qualquer, retire todos os
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

/*[7] Suponha que a estrutura TAB tenha um campo cor (int cor). Escreva uma função em C que, ao receber uma árvore binária “sem cor”
e totalmente balanceada (isto é, a distância da raiz a qualquer folha da árvore é sempre a mesma), retorne esta árvore com os
nós coloridos somente de vermelho e preto, sendo que o nó pai NUNCA pode ter a mesma cor de seus filhos. A função deve possuir
o seguinte protótipo: void colore (TAB* arv); */
void colore(TAB *arv)
{
    if (arv == NULL)
        return;
    int cor_filhos;

    if (arv->cor != 1 && arv->cor != 2) // se for o no raiz, tem que pintar a si mesmo
        arv->cor = 1;

    if (arv->cor == 1) // se tiver a cor 1, pinta os filhos de 2
        cor_filhos = 2;
    else if (arv->cor == 2) // se tiver a cor 2, pinta os filhos de 1
        cor_filhos = 1;

    if (arv->dir != NULL)
        arv->dir->cor = cor_filhos;
    if (arv->esq != NULL)
        arv->esq->cor = cor_filhos;

    colore(arv->dir);
    colore(arv->esq);
}

/*[8] Escreva uma função em C que retorna a quantidade de nós internos: int ni(TAB *a)*/
int ni(TAB *a)
{
    if (a == NULL) // obviamente nao conta se for null
        return 0;
    if (a->dir == NULL && a->esq == NULL) // nao conta se for no folha
        return 0;

    return 1 + ni(a->dir) + ni(a->esq);
}

/*[9] Escreva uma função em C que retorna a quantidade de nós folha: int nf(TAB*a);*/
int nf(TAB *a)
{
    if (a == NULL)
        return 0;
    if (a->dir == NULL && a->esq == NULL)
        return 1;

    return nf(a->dir) + nf(a->esq);
}

/*[10] Escreva uma função em C para testar se uma árvore é zigue-zague, isto é, se todos
os nós internos possuem exatamente uma sub-árvore vazia: int zz(TAB *a);*/
int zz(TAB *a)
{
    if (a == NULL) // se for null, respeita a condicao
        return 1;
    if (a->dir == NULL && a->esq == NULL) // se for no folha, respeita a condicao NEM PRECISA DESSA, MAS FICA MAIS ORGANIZADO
        return 1;
    if (a->esq == NULL) // se tiver somente caminho pra direita, segue
        return zz(a->dir);
    if (a->dir == NULL) // se tiver somente caminho pra esquerda, segue
        return zz(a->esq);

    return 0; // se tiver caminho pra direita E esquerda,
}

/*[11] Escreva uma função em C para verificar se uma árvore é estritamente binária, isto é, se os nós dessa
árvore possuem ou zero ou dois filhos: int estbin(TAB*a);*/
int estbin(TAB *a)
{
    if (a == NULL)
        return 1;

    if (a->dir == NULL && a->esq == NULL) // no folha -> respeita
        return 1;
    if (a->dir != NULL && a->esq != NULL) // dois filhos -> respeita e seguimos na arvore
        return estbin(a->dir) && estbin(a->esq);

    return 0; // se for no com um filho apenas -> nao respeita
}

/*[12] Escreva uma função em C para testar se duas árvores possuem os mesmos nós: int mesmos_nos(TAB *a1, TAB *a2).*/

int conta_nos(TAB *a)
{
    if (a == NULL)
        return 0;
    return 1 + conta_nos(a->dir) + conta_nos(a->esq);
}

void preenche_vetor(TAB *a, int *vet, int *pos)
{
    if (a != NULL)
    {
        vet[*pos] = a->info;              // coloca o valor do no na posicao pos do vetor
        (*pos)++;                         // passa pra proxima posicao do vetor
        preenche_vetor(a->esq, vet, pos); // preenche com todos da esquerda
        preenche_vetor(a->dir, vet, pos); // preenche com todos da direita
    }
}

int compara(const void *a, const void *b) // auxiliar do qsort obrigatoria
{
    return (*(int *)a - *(int *)b);
}

int mesmos_nos(TAB *a1, TAB *a2)
{
    if (a1 == NULL && a2 == NULL) // se ambas sao nulas -> sao iguais
        return 1;
    if (a1 == NULL || a2 == NULL) // se apenas uma eh nula -> sao diferentes
        return 0;

    int n1 = conta_nos(a1);
    int n2 = conta_nos(a2);

    if (n1 != n2) // se tem quantidade de nos diferentes -> sao diferentes
        return 0;

    int *v1 = malloc(n1 * sizeof(int)); // aloca memoria de acordo com a quant de nos
    int *v2 = malloc(n2 * sizeof(int));

    int pos1 = 0, pos2 = 0;
    preenche_vetor(a1, v1, &pos1); // preenche os vetores com os nos
    preenche_vetor(a2, v2, &pos2);

    qsort(v1, n1, sizeof(int), compara); // usa o quicksort nativo do C
    qsort(v2, n2, sizeof(int), compara);

    int possui_mesmos_nos = 1; // verifica se os vetores sao iguais
    for (int i = 0; i < n1; i++)
        if (v1[i] != v2[i])
        {
            possui_mesmos_nos = 0;
            break;
        }

    free(v1);
    free(v2);

    return possui_mesmos_nos;
}
