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