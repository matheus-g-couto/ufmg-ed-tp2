#include <getopt.h>
#include <string.h>

#include <cstdlib>
#include <iostream>

#include "memlog.h"
#include "msgassert.h"
#include "sort.h"

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
        : input_file("assets/in/entrada.txt"),
          output_file("assets/out/saida.txt"),
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

    avisoAssert(has_in, "Usando o arquivo de entrada padrao: assets/in/entrada.txt");
    avisoAssert(has_out, "Usando o arquivo de saida padrao: assets/out/saida.txt");
    avisoAssert(has_log, "Usando o arquivo de log padrao: bin/log.out");
    avisoAssert(has_type, "Realizando o quicksort recursivo padrão");
    avisoAssert(has_seed, "Utilizando seed padrão (77)");
    avisoAssert(!(f->type == 2 && !has_median_k), "Realizando o quicksort com mediana de 3 elementos");
    avisoAssert(!(f->type == 3 && !has_select_stop), "Utilizando o selection sort a partir de partições de 10 elementos");
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

    delete f;
    return 0;
}
