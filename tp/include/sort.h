struct Item {
    int id;
    char str[15][201];
    double num[10];
};

void quicksortRec(Item *regs, int size);
void quicksortMed(Item *regs, int size, int n);
void quicksortSelect(Item *regs, int size, int m);
void quicksortNRec();
void quicksortSmartStack();