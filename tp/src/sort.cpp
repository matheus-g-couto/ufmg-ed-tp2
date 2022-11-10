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

void selectionSort(int left, int right, Item *regs) {
    for (int i = left; i < right; i++) {
        int smaller = i;
        for (int j = i + 1; j < right; j++) {
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

void SelectOrder(int left, int right, Item *regs) {}

void quicksortSelect(Item *regs, int size, int m) {}
void quicksortNRec() {}
void quicksortSmartStack() {}