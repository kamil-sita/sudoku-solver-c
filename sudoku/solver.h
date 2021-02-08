#ifndef SUDOKUTEKSTOWE_SOLVER_H
#define SUDOKUTEKSTOWE_SOLVER_H

#include "board.h"


///Enum służący do wybierania metody rozwiązania
enum solvingAlgorithm {
///metoda brute force (algorytm z nawrotami)
    backtracking, 
///metoda klasyczna
    classic 
};

/**
 * Rozwiązuje planszę sudoku korzystając z wybranego algorytmu
 * @param board plansza sudoku
 * @param limit maksymalna liczba iteracji
 * @param alg wybrany algorytm
 * @return -1 - osiągnięto limit
 * @return 0 - brak rozwiązań
 * @return 1 - istnieje jedno rozwiązanie
 * @return 2 - 2 lub więcej rozwiązania
 */
int solveUsingFunction(struct sudokuBoard *board, int limit, enum solvingAlgorithm alg);

#endif
