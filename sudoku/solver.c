#include "solver.h"
#include "penAndPaperSolver.h"
#include "backTrackingSolver.h"

int solveUsingFunction(struct sudokuBoard *board, int limit, enum solvingAlgorithm alg) {
    int (*pf) (struct sudokuBoard*, int);
    switch (alg) {
        case classic:
            pf = penAndPaperSolver;
            break;
        case backtracking:
            pf = bruteForceSolver;
            break;
    }
    return pf(board, limit);
}