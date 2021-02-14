#if _WIN32
#include <mem.h>
#else
#include <memory.h>
#endif
#include <solver.h>
#include <stdio.h>
#include "args.h"

void printNoArgs() {
    puts("No argumens have been provided.");
    puts("Available arguments:");
    puts("0 - solve using backtracking/brute force");
    puts("1 - pen and paper algorithm");
    puts("u - require unique solution");
    puts("n = don't require unique solution");
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