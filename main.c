#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#if _WIN32
#include <mem.h>
#else
#include <memory.h>
#endif
#include <solver.h>
#include <stdbool.h>
#include "test.h"
#include "main.h"
#include "args.h"
#include "gameGui.h"

int main(int argc, char **argv) {

    srand(time(0)); //ustawianie ziarna losowości
    //testy(); //testy

    //parsowanie argumentów z linii poleceń
    enum solvingAlgorithm alg = backtracking;
    bool uniqueSolution = true;
    bool flag = false;

    if (argc <= 1) {
        printNoArgs();
    } else {
        for (int i = 1; i < argc; i++) {
            if (parseArgs(argv[i], &alg, &uniqueSolution)) flag = true;
        }
    }

    if (!flag && argc > 1)  puts("Nie udalo sie odczytac argumentow");

    //koniec parsowania

    runGame(alg, uniqueSolution);

    return 0;
}