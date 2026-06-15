#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pai(int n, int indice_filho)
{
    if (indice_filho <= 1)
        return 0;
    return (indice_filho - 2) / n + 1;
}

int filho_i(int n, int indice_pai, int i)
{
    return n * (indice_pai - 1) + 1 + i;
}

void subir(int *heap, int n, int i)
{
    while (i > 1)
    {
        int p = pai(n, i);
        if (heap[i] > heap[p])
        {
            int aux = heap[i];
            heap[i] = heap[p];
            heap[p] = aux;
            i = p;
        }
        else
        {
            break;
        }
    }
}

void descer(int *heap, int ultimo_indice, int n, int i)
{
    // Fica em loop até o nó achar o seu lugar correto
    while (1)
    {
        int indice_maior = i; // Começamos assumindo que o pai (i) é o maior de todos

        // Vamos olhar para os 'n' filhos desse nó
        for (int j = 1; j <= n; j++)
        {
            // Usa a função do exercício anterior para achar onde está o filho 'j'
            int f = filho_i(n, i, j);

            // O filho existe? (Não ultrapassou o tamanho do vetor?)
            // E o valor desse filho é MAIOR do que o nosso "campeão" atual?
            if (f <= ultimo_indice && heap[f] > heap[indice_maior])
            {
                indice_maior = f; // Temos um novo campeão!
            }
        }

        // Se o maior valor de todos for um dos filhos, e não o pai original...
        if (indice_maior != i)
        {
            // Rebaixamento! Troca o pai com esse maior filho
            int aux = heap[i];
            heap[i] = heap[indice_maior];
            heap[indice_maior] = aux;

            // Atualiza o 'i' para continuar descendo a partir da nova posição
            i = indice_maior;
        }
        else
        {
            // Se o pai original for maior que todos os filhos, ele achou o lugar dele!
            break;
        }
    }
}
int exclui(int *heap, int ultimo_indice, int n)
{
    // Se a heap já estiver vazia, não há o que excluir
    if (ultimo_indice < 1)
    {
        return ultimo_indice;
    }

    // 1. Opcional: Se você quisesse saber quem foi excluído, poderia salvar:
    // int removido = heap[1];

    // 2. Pega o cara da ÚLTIMA posição e joga ele na RAIZ (posição 1)
    heap[1] = heap[ultimo_indice];

    // 3. Diminui o tamanho da heap (o último cara original foi apagado/movido)
    ultimo_indice--;

    // 4. Manda o cara que foi pro topo "descer" até arrumar a árvore
    // Só chamamos o descer se ainda sobrar alguém na árvore!
    if (ultimo_indice > 0)
    {
        descer(heap, ultimo_indice, n, 1);
    }

    // 5. Retorna o novo tamanho da heap
    return ultimo_indice;
}