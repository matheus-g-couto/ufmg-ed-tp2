#include "memlog.h"
#include "msgassert.h"
#include "sort.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv) {
    Item c[10];
    for (int i = 0; i < 10; i++) {
        c[i].id = rand() % 100;
    }

    for (int i = 0; i < 10; i++) {
        std::cout << c[i].id << " ";
    }
    std::cout << std::endl;

    quicksortRec(c, 10);

    for (int i = 0; i < 10; i++) {
        std::cout << c[i].id << " ";
    }
    std::cout << std::endl;
    return 0;
}
