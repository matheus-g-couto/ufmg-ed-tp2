struct Item {
    int id;
    char str[15][201];
    double num[10];
};

void quicksortRec(Item *regs, int size);
void quicksortMed(Item *regs, int size, int n);
void quicksortSelect(Item *regs, int size, int m);
void quicksortNRec(Item *regs, int size);
void quicksortSmartStack(Item *regs, int size);
void mergesort(Item *regs, int size);
void heapsort(Item *regs, int size);