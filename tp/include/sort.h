struct Item {
    int id;
    char str[15][201];
    double num[10];
};

void quicksortRec(Item *regs, int tam);
void quicksortMed(Item *regs, int size, int n);
void quicksortSelect();
void quicksortNRec();
void quicksortSmartStack();