#ifndef SUDOKUTEKSTOWE_SOLVER_H
#define SUDOKUTEKSTOWE_SOLVER_H

#include "board.h"

#define LIMIT_REACHED -1
#define NO_SOLUTIONS 0
#define ONE_SOLUTION 1
#define MULTIPLE_SOLUTIONS 2

enum solvingAlgorithm {
    backtracking, 
    classic 
};

/**
 * Rozwiązuje planszę sudoku korzystając z wybranego algorytmu
 * @param board plansza sudoku
 * @param limit maksymalna liczba iteracji
 * @param alg wybrany algorytm
 * @return LIMIT_REACHED - limit has been reached (timeout)
 * @return NO_SOLUTIONS - no solutions have been found
 * @return ONE_SOLUTION - one solution has been found
 * @return MULTIPLE_SOLUTIONS - two or more solutions have been found
 */
int solveUsingFunction(struct sudokuBoard *board, int limit, enum solvingAlgorithm alg);

#endif
