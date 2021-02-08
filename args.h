#ifndef SUDOKUTEKSTOWE_ARGS_H
#define SUDOKUTEKSTOWE_ARGS_H

#include <stdbool.h>

/**
 * Drukuje ostrzeżenie przy braku argumentów.
 */
void printNoArgs();

/**
 * Sprawdza argumenty podane przez użytkownika w celu wybrania odpowiedniego algorytmu rozwiązywania sudoku i zdecydowania czy rozwiązanie powinno być unikalne.
 * @param arg argument
 * @param alg algorytm rozwiązywania
 * @param requireUniqueSolution czy rozwiązanie powinno być unikalne
 */
bool parseArgs(char *arg, enum solvingAlgorithm *alg, bool *requireUniqueSolution);


#endif