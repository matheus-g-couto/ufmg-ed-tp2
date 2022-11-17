#include "memlog.h"
#include "msgassert.h"
#include "sort.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv) {
    Item c[50];
    int size = 50;
    for (int i = 0; i < size; i++) {
        c[i].id = rand() % 100;
    }

    for (int i = 0; i < size; i++) {
        std::cout << c[i].id << " ";
    }
    std::cout << std::endl;

    // quicksortRec(c, 10);
    // quicksortSelect(c, size, 10);
    // quicksortMed(c, 10, 3);
    // quicksortNRec(c, size);
    quicksortSmartStack(c, size);

    for (int i = 0; i < size; i++) {
        std::cout << c[i].id << " ";
    }
    std::cout << std::endl;

    return 0;
}
