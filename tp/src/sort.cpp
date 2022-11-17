#include "sort.h"
#include <cstdlib>
#include <iostream>

void Swap(Item *a, Item *b) {
    Item c;
    c = *a;
    *a = *b;
    *b = c;
}

void Partition(int left, int right, int *i, int *j, Item *regs, Item pivot) {
    *i = left;
    *j = right;

    do {
        while (pivot.id > regs[*i].id)
            (*i)++;
        while (pivot.id < regs[*j].id)
            (*j)--;

        if (*i <= *j) {
            Swap(&regs[*i], &regs[*j]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Order(int left, int right, Item *regs) {
    int i, j;
    Partition(left, right, &i, &j, regs, regs[(left + right) / 2]);
    if (left < j)
        Order(left, j, regs);
    if (i < right)
        Order(i, right, regs);
}

void quicksortRec(Item *regs, int size) { Order(0, size - 1, regs); }

void selectionSort(int left, int size, Item *regs) {
    for (int i = left; i < size; i++) {
        int smaller = i;
        for (int j = i + 1; j < size; j++) {
            if (regs[j].id < regs[smaller].id)
                smaller = j;
        }

        Swap(&regs[i], &regs[smaller]);
    }
}

Item MedianPivot(int left, int right, int k, Item *regs) {
    Item *pivots = new Item[k];
    for (int i = 0; i < k; i++) {
        pivots[i] = regs[rand() % (right - left) + left];
    }

    selectionSort(0, k, pivots);
    return pivots[k / 2];
}

void MedianOrder(int left, int right, int k, Item *regs) {
    int i, j;
    Partition(left, right, &i, &j, regs, MedianPivot(left, right, k, regs));
    if (left < j)
        Order(left, j, regs);
    if (i < right)
        Order(i, right, regs);
}

void quicksortMed(Item *regs, int size, int k) {
    MedianOrder(0, size - 1, k, regs);
}

void SelectOrder(int left, int right, int m, Item *regs) {
    int i, j;

    if (right - left <= m) {
        selectionSort(left, right + 1, regs);
        return;
    }

    Partition(left, right, &i, &j, regs, regs[(left + right) / 2]);
    if (left < j)
        SelectOrder(left, j, m, regs);
    if (i < right)
        SelectOrder(i, right, m, regs);
}

void quicksortSelect(Item *regs, int size, int m) {
    SelectOrder(0, size - 1, m, regs);
}

void quicksortNRec(Item *regs, int size) {
    // pilha que armazena as partições a serem ordenadas
    int idx_stack[size];
    int top = -1;

    int left = 0, right = size - 1, i, j;
    idx_stack[++top] = left;
    idx_stack[++top] = right;

    // itera até que a pilha esteja vazia
    while (top >= 0) {
        right = idx_stack[top--];
        left = idx_stack[top--];

        Partition(left, right, &i, &j, regs, regs[(left + right) / 2]);
        if (left < j) {
            idx_stack[++top] = left;
            idx_stack[++top] = j;
        }

        if (i < right) {
            idx_stack[++top] = i;
            idx_stack[++top] = right;
        }
    }
}

struct ItemPos {
    int left, right;
};

struct No {
    ItemPos it;
    No *prox;
};

struct Pilha {
    No *topo;
    int tam;

    Pilha() : topo(NULL), tam(0) {}
    void empilha(ItemPos it) {
        No *n = new No();
        n->it = it;
        n->prox = topo;
        topo = n;
        tam++;
    }

    ItemPos desempilha() {
        if (tam == 0)
            throw("Pilha vazia!");
        No *aux = topo;
        ItemPos item = topo->it;
        topo = topo->prox;
        delete aux;
        tam--;
        return item;
    }
};

void quicksortSmartStack(Item *regs, int size) {
    Pilha *p = new Pilha();
    ItemPos item;
    int left = 0, right = size - 1, i, j;

    item.left = left;
    item.right = right;
    p->empilha(item);

    do {
        if (right > left) {
            Partition(left, right, &i, &j, regs, regs[(left + right) / 2]);
            if ((j - left) > (i - right)) {
                item.left = left;
                item.right = j;
                p->empilha(item);
                left = i;
            } else {
                item.left = i;
                item.right = right;
                p->empilha(item);
                right = j;
            }
        } else {
            item = p->desempilha();
            right = item.right;
            left = item.left;
        }
    } while (p->tam > 0);
}

// MergeSort from: https://www.programiz.com/dsa/merge-sort
void MergesortMerge(Item *regs, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    Item A[n1], B[n2];

    for (int i = 0; i < n1; i++)
        A[i] = regs[left + i];
    for (int j = 0; j < n2; j++)
        B[j] = regs[mid + 1 + j];

    // mantém controle do index dos subarrays e array principal
    int i = 0, j = 0, k = left;

    // coloca os elementos dos subarrays no vetor principal
    while (i < n1 && j < n2) {
        if (A[i].id <= B[j].id) {
            regs[k] = A[i];
            i++;
        } else {
            regs[k] = B[j];
            j++;
        }
        k++;
    }

    // adiciona os elementos faltantes após acabarem os elementos de um dos
    // vetores
    while (i < n1) {
        regs[k] = A[i];
        i++;
        k++;
    }

    while (j < n2) {
        regs[k] = B[j];
        j++;
        k++;
    }
}

void MergesortDivide(Item *regs, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    MergesortDivide(regs, left, mid);
    MergesortDivide(regs, mid + 1, right);
    MergesortMerge(regs, left, mid, right);
}

void mergesort(Item *regs, int size) { MergesortDivide(regs, 0, size - 1); }

// HeapSort from: https://www.geeksforgeeks.org/cpp-program-for-heap-sort/
void HeapMake(Item *regs, int size, int idx) {
    int largest = idx; // idx do maior elemento inicializado como a raiz do heap
    int left = 2 * idx + 1, right = 2 * idx + 2;

    if (left < size && regs[left].id > regs[largest].id)
        largest = left;

    if (right < size && regs[right].id > regs[largest].id)
        largest = right;

    if (largest != idx) {
        Swap(&regs[idx], &regs[largest]);

        HeapMake(regs, size, largest);
    }
}

void heapsort(Item *regs, int size) {
    // constrói o heap
    for (int i = size / 2 - 1; i >= 0; i--)
        HeapMake(regs, size, i);

    for (int i = size - 1; i >= 0; i--) {
        Swap(&regs[0], &regs[i]);
        HeapMake(regs, i, 0);
    }
}