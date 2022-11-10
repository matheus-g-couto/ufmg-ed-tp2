#include "sort.h"
#include <cstdlib>

void Swap(Item *a, Item *b) {
    Item c;
    c = *a;
    *a = *b;
    *b = c;
}

void Partition(int left, int right, int *i, int *j, Item *regs) {
    Item pivot;
    *i = left;
    *j = right;
    pivot = regs[(*i + *j) / 2];

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
    Partition(left, right, &i, &j, regs);
    if (left < j)
        Order(left, j, regs);
    if (i < right)
        Order(i, right, regs);
}

void quicksortRec(Item *regs, int size) { Order(0, size - 1, regs); }

void quicksortMed(Item *regs, int size, int n) {}

void quicksortSelect() {}
void quicksortNRec() {}
void quicksortSmartStack() {}