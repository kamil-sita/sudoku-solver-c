#if _WIN32
#include <mem.h>
#else
#include <memory.h>
#endif
#include <solver.h>
#include <stdio.h>
#include "args.h"

void printNoArgs() {
    puts("Nie zostaly wprowadzone zadne argumenty. Zostanie uzyta domyslna metoda rozwiazywania sudoku");
    puts("Dostepne argumenty:");
    puts("0 - backtrack (brute forcing)");
    puts("1 - algorytm klasyczny");
    puts("u - wymagaj unikalnego rozwiazania");
    puts("n = nie wymagaj unikalnego rozwiazania");
}

bool parseArgs(char *arg, enum solvingAlgorithm *alg, bool *requireUniqueSolution) {
    if (strcmp("0", arg) == 0) {
        *alg = backtracking;
        return true;
    } else if (strcmp("1", arg ) == 0) {
        *alg = classic;
        return true;
    } else if (strcmp("u", arg) == 0) {
        *requireUniqueSolution = true;
        return true;
    } else if (strcmp("n", arg) == 0) {
        *requireUniqueSolution = false;
        return true;
    }
    return false;
}