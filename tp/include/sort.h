#ifndef SORT_H
#define SORT_H

#include <string>

#include "memlog.h"

struct Item {
    int id;
    std::string str[15];
    double num[10];
};

void quicksortRec(Item *regs, int size);
void quicksortMed(Item *regs, int size, int n);
void quicksortSelect(Item *regs, int size, int m);
void quicksortNRec(Item *regs, int size);
void quicksortSmartStack(Item *regs, int size);
void mergesort(Item *regs, int size);
void heapsort(Item *regs, int size);

#endif