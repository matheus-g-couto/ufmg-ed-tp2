#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "memlog.h"
#include "msgassert.h"
#include "sort.h"

int comparisons_count = 0;
int copies_count = 0;

std::string tipos_sort[] = {"Quicksort recursivo",
                            "Quicksort recursivo com mediana",
                            "Quicksort recursivo com selection",
                            "Quicksort não recursivo",
                            "Quicksort não recursivo com pilha inteligente",
                            "Mergesort",
                            "Heapsort"};

struct Flags {
    std::string input_file;
    std::string output_file;
    char log_file[100];
    bool regmem;
    int type;
    int random_seed;
    int median_k;
    int select_stop;

    Flags()
        : input_file("assets/in/entrada_padrao.txt"),
          output_file("bin/saida.txt"),
          log_file("bin/log.out"),
          regmem(false),
          type(1),
          random_seed(77),
          median_k(3),
          select_stop(10) {}
};

void parse_args(int argc, char **argv, Flags *f) {
    int opt;
    bool has_in = false, has_out = false, has_log = false, has_seed = false, has_type = false, has_median_k = false,
         has_select_stop = false;
    while ((opt = getopt(argc, argv, "i:o:p:l:v:s:k:m")) != -1) {
        switch (opt) {
            case 'i':
                // recebeu arquivo de entrada
                has_in = true;
                f->input_file = optarg;
                break;

            case 'o':
                // recebeu arquivo de saída
                has_out = true;
                f->output_file = optarg;
                break;

            case 'p':
                // recebeu arquivo para logs de memória e tempo de execução
                has_log = true;
                strcpy(f->log_file, optarg);
                break;

            case 'l':
                // usuário deseja registrar logs de acesso à memória
                f->regmem = true;
                break;

            case 'v':
                // versão do quicksort desejada
                has_type = true;
                f->type = atoi(optarg);
                break;

            case 's':
                // seed aleatória
                has_seed = true;
                f->random_seed = atoi(optarg);
                break;

            case 'k':
                // quantidade de elementos considerados pela mediana do
                // quicksort tipo 2
                has_median_k = true;
                f->median_k = atoi(optarg);
                break;

            case 'm':
                // número de elementos nas partições para que seja utilizado o
                // selection sort no quicksort tipo 3
                has_select_stop = true;
                f->select_stop = atoi(optarg);
                break;

            case '?':
                // argumento não reconhecido
                erroAssert(false, "Opcao de linha de comando invalida");
                break;
        }
    }

    avisoAssert(has_in, "Usando o arquivo de entrada padrao: assets/in/entrada_padrao.txt");
    avisoAssert(has_out, "Usando o arquivo de saida padrao: bin/saida.txt");
    avisoAssert(has_log, "Usando o arquivo de log padrao: bin/log.out");
    avisoAssert(has_type, "Realizando o quicksort recursivo padrao (opcao 1)");
    avisoAssert(has_seed, "Utilizando seed padrao (77)");
    avisoAssert(!(f->type == 2 && !has_median_k), "Realizando o quicksort com mediana de 3 elementos");
    avisoAssert(!(f->type == 3 && !has_select_stop), "Utilizando o selection sort a partir de particoes de 10 elementos");
    avisoAssert(f->type <= 7 && f->type > 0, "Opcao de ordenacao nao reconhecida");
}

// fonte: https://codereview.stackexchange.com/questions/29198/random-string-generator-in-c
std::string generate_random_string() {
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string str;

    for (int i = 0; i < 200; i++) {
        int idx = rand() % (int)(sizeof(charset) - 1);
        str += charset[idx];
    }
    str[201] = '\0';

    return str;
}

void fillItemArray(int n, Item *regs) {
    for (int i = 0; i < n; i++) {
        regs[i].id = rand() % n;

        for (int j = 0; j < 15; j++) {
            regs[i].str[j] = generate_random_string();
        }

        for (int j = 0; j < 10; j++) {
            regs[i].num[j] = rand();
        }
    }
}

void sort(Item *regs, int size, const Flags f) {
    switch (f.type) {
        case 1:
            quicksortRec(regs, size);
            break;
        case 2:
            quicksortMed(regs, size, f.median_k);
            break;
        case 3:
            quicksortSelect(regs, size, f.select_stop);
            break;
        case 4:
            quicksortNRec(regs, size);
            break;
        case 5:
            quicksortSmartStack(regs, size);
            break;
        case 6:
            mergesort(regs, size);
            break;
        case 7:
            heapsort(regs, size);
            break;
    }
}

void printResultsHeader(const Flags f, std::ofstream &output) {
    switch (f.type) {
        case 2:
            output << tipos_sort[f.type - 1] << " - Mediana de " << f.median_k << " elementos" << std::endl;
            break;
        case 3:
            output << tipos_sort[f.type - 1] << " - Selection sort a partir de partições de tamanho " << f.select_stop
                   << std::endl;
            break;
        default:
            output << tipos_sort[f.type - 1] << std::endl;
            break;
    }
}

void printResults(const int64_t exec_time, const Flags f, const int size_input, std::ofstream &output) {
    output << size_input << " registros | Tempo de execução médio: " << exec_time << "ms | " << comparisons_count
           << " comparações | " << copies_count << " cópias" << std::endl;

    comparisons_count = 0;
    copies_count = 0;
}

int64_t calcMedia(const int64_t *exec_time, const int n_tests) {
    int64_t sum = 0;
    for (int i = 0; i < n_tests; i++) sum += exec_time[i];

    return sum / n_tests;
}

int main(int argc, char **argv) {
    // recebe os argumentos da linha de comando
    Flags *f = new Flags();
    parse_args(argc, argv, f);

    // inicia registro de acesso
    iniciaMemLog(f->log_file);
    if (f->regmem)
        ativaMemLog();
    else
        desativaMemLog();

    // define o fstream para entrada e saída
    std::ifstream input(f->input_file);
    std::ofstream output(f->output_file);

    if (input.is_open()) {
        // pega a primeira linha do arquivo, que define a quantidade de entradas
        int num_in = 0;
        input >> num_in;

        // as num_in linhas subsequentes do arquivo definem a quantidade de valores N para realizar os testes de ordenação
        int N;
        int tests_per_size = 5;

        printResultsHeader(*f, output);

        for (int i = 0; i < num_in; i++) {
            input >> N;

            // vetor que mantém controle dos tempos de execução em milisegundos
            int64_t exec_time[tests_per_size];

            for (int j = 0; j < tests_per_size; j++) {
                // define a seed aleatória
                srand(f->random_seed + j);

                Item *regs;

                regs = new Item[N];
                fillItemArray(N, regs);

                auto start = std::chrono::steady_clock::now();
                sort(regs, N, *f);
                auto end = std::chrono::steady_clock::now();
                exec_time[j] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                delete[] regs;
            }

            printResults(calcMedia(exec_time, tests_per_size), *f, N, output);
        }
    }

    delete f;
    return finalizaMemLog();
}
