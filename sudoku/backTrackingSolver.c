#include "backTrackingSolver.h"
#include "board.h"
#include "../helper.h"
#include "../random.h"

int bruteForceSolver(struct sudokuBoard *board, int limit) {
    struct sudokuBoard solution;
    struct sudokuBoard previousSolution;
    //inicjalizacja pomocnika, który będzie wykorzystany przy rozwiazywaniu planszy - będzie przechowywał wartości które algorytm
    //próbował już użyć
    struct helperStructure helper[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        clearHelperStructure(&(helper[i]));
    }

    int cell = 0;
    int solutionCount = 0;
    int iteration = 0;

    while (true) {
        if (iteration == limit) return -1; //osiągneliśmy limit i nie możemy już rozwiązywać tego sudoku
        iteration++;

        if (cell < 0) {
            //jeżeli znajdujemy się tutaj, to znaczy że sprawdziliśmy wszystkie rozwiązania - należy zwrócić ich liczbę, i ewentualne rozwiązanie
            copyFromTo(&solution, board);
            return solutionCount; //prawdopodobnie 0 albo 1.
        }

        //obliczanie koordynatów komórki -> transformacja 1 wymiaru w 2
        int xPos = cell % BOARD_SIZE;
        int yPos = cell / BOARD_SIZE;

        bool goingBackFromConstCell = false;
        bool filledCell = false;
        int number;

        if (board->cells[yPos][xPos].constantCell) { //jezeli value w tej komorce jest stala, nie ma sensu jej zmieniac
            if (solutionCount == 1) copyFromTo(&solution, &previousSolution);
            int control = constantCellSubroutine(board, &solution, &cell, &solutionCount, &goingBackFromConstCell,
                                                 &number);
            if (control == 1) continue; //do następnej komórki
            if (control == 2) return 2; //znaleziono kolejne rozwiązanie, zwróć 2
        } else {
            bool tryAgain = nonConstantCellSubroutine(board, helper, cell, xPos, yPos, &filledCell, &number);
            if (tryAgain) continue;
        }

        if (filledCell) { //udało się wpisać do komórki - przechodzimy do następnej
            cell++;
            if (cell == BOARD_SIZE * BOARD_SIZE) {
                goBackFromCorrectSolutionBacktrackingSolver(&cell, &solutionCount, board, &solution);
                if (solutionCount == 2) return 2;
                filledCell = false;
            } else {
                continue;
            }
        }

        //sprawdzanie czy sprobowano wpisac wszystkie liczby do tego pola. Zapisywanie informacji o probie wpisania liczby do komorki
        if (!goingBackFromConstCell) filledCell = tryAddToArray(helper[cell].usedValues, number);
        //nie ma liczby, ktorej nie sprobawno wpisac, trzeba sprobowac gdzies indziej
        if (!filledCell) allNumbersTriedSubroutine(board, helper, &cell, xPos, yPos, filledCell);

    }

}

void allNumbersTriedSubroutine(struct sudokuBoard *board, struct helperStructure *helper, int *cell, int xPos, int yPos,
                               bool filledCell) {
    goBackFromCell(cell, yPos, xPos, &helper[(*cell)], board);
    while (true) {
        //obliczanie poyzcji tej komorki
        xPos = (*cell) % BOARD_SIZE;
        yPos = (*cell) / BOARD_SIZE;
        if (board->cells[yPos][xPos].constantCell == true) {
            (*cell)--;
            continue;
        }
        if ((*cell) >= 0) {
            filledCell = tryAddToArray(helper[(*cell)].usedValues,
                                       board->cells[yPos][xPos].value); //informacja, ze dla danej liczby nie istnieje rozwiazanie
        } else {
            break;
        }
        if (filledCell) {
            break;
        } else {
            goBackFromCell(cell, yPos, xPos, &helper[(*cell)], board);
        }
    }
}

bool nonConstantCellSubroutine(struct sudokuBoard *board, struct helperStructure *helper, int cell, int xPos, int yPos,
                               bool *filledCell, int *number) {
    int freeValues[BOARD_SIZE];
    int max = fillWithValuesNotIncluded(helper[cell].usedValues,
                                        freeValues); //sprawdzenie jakie wartości nie zostały wykorzystane przy próbowaniu "wsadzenia" wartości w cell
    (*number) = freeValues[generateInteger(0, max -
                                              1)]; //losowa wartość z niewykorzystanych. Pomaga przy planszach zaprojektowanych przeciwko temu typowi rozwiązania, ale poza tym nie ma zastosowania
    if (isInArray(helper[cell].usedValues, (*number))) return true;
    //wpisywanie wartości do komórki
    board->cells[yPos][xPos].value = (short) (*number);
    (*filledCell) = isBoardCorrect(*board);
    return false;
}

int constantCellSubroutine(struct sudokuBoard *board, struct sudokuBoard *solution, int *cell, int *solutionCount,
                           bool *goingBackFromConstCell, int *number) {
    (*cell)++;
    if ((*cell) == BOARD_SIZE * BOARD_SIZE) {
        goBackFromCorrectSolutionBacktrackingSolver(cell, solutionCount, board, solution);
        if ((*solutionCount) == 2) return 2;
        (*number) = board->cells[BOARD_SIZE - 1][BOARD_SIZE - 1].value;
        (*goingBackFromConstCell) = true;
    } else {
        return 1;
    }
    return 0;
}

void goBackFromCorrectSolutionBacktrackingSolver(int *cell, int *solutionCount, struct sudokuBoard *board,
                                                 struct sudokuBoard *solution) {
    copyFromTo(board, solution);
    (*solutionCount)++;
    (*cell)--;
}

void goBackFromCell(int *cell, int yPos, int xPos, struct helperStructure *helper, struct sudokuBoard *board) {
    clearHelperStructure(helper);
    if (!board->cells[yPos][xPos].constantCell) board->cells[yPos][xPos].value = 0;
    (*cell)--;
}