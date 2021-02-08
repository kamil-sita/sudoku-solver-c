#include <stdio.h>
#include "penAndPaperSolver.h"
#include "board.h"
#include "../helper.h"


int penAndPaperSolver(struct sudokuBoard *board, int limit) {
    struct helperStructure helper[BOARD_SIZE * BOARD_SIZE];

    bool flagSimpleSolution;
    bool solvingPossible = true;
    int valuesLeftToFill = BOARD_SIZE * BOARD_SIZE;

    if (!isBoardCorrect(*board)) return 0; //złe podstawienie przy rekurencji może wywołać tą linię

    int iteration = 0;

    while (solvingPossible) {
        if (iteration == limit) return -1;
        iteration++;
        solvingPossible = false;

        if (updateValuesLeftToFill(board, helper, &valuesLeftToFill) == 1) return 1;

        bool failed = false;

        searchAndSolvePreemptiveSets(*board, helper, &failed);
        searchAndSolveSingleValues(helper);

        //jeżeli gdzieś struktura pomocnicza ma rozmiar 1, oznacza to, że możemy wpisać taką wartość
        do {
            flagSimpleSolution = false;
            for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
                int y = i / BOARD_SIZE;
                int x = i % BOARD_SIZE;
                if ((board->cells[y][x].constantCell == false) && (board->cells[y][x].value == 0)) {
                    if (sizeOfHelper(helper[i]) == 1) {
                        flagSimpleSolution = true;
                        solvingPossible = true;
                        board->cells[y][x].value = (short) helper[i].usedValues[0];
                        valuesLeftToFill--;
                        if (valuesLeftToFill == 0) return 1;
                    }
                }
            }
            if (!isBoardCorrect(*board)) return 0;
        } while (flagSimpleSolution);

    }

    if (valuesLeftToFill == 0) return 1;

    //algorytm nie może już rozwiązywać tej części klasycznie - resztę robimy rekurencyjnie, podstawiając różne wartości
    int pos = 0;
    int solutionCount = 0;
    struct sudokuBoard solution;
    bool flag = true;
    int x;
    int y;

    //musimy znaleźć jakąś pustą komórkę, w którą będziemy wpisywać nasze zgadnięcia. Równie dobrze może to być pierwsza znaleziona komórka
    findFirstUnknownValue(board, flag, &pos, &x, &y);

    for (int j = 0; j < sizeOfHelper(
            helper[pos]); j++) { //dla każdej możliwej wartości w tej komórce wywołujemy inne odwołanie rekurencyjne
        struct sudokuBoard copyForRecursion;
        copyFromTo(board, &copyForRecursion);
        copyForRecursion.cells[y][x].value = (short) helper[pos].usedValues[j];
        int solutionFromRecursion = penAndPaperSolver(&copyForRecursion, 100 - iteration);
        if (solutionFromRecursion == -1)
            return -1; //osiągnęliśmy granicę w podfunkcji, więc tutaj też - nic ciekawego już się nie dowiemy
        solutionCount += solutionFromRecursion;
        if (solutionFromRecursion >= 1) copyFromTo(&copyForRecursion, &solution);

        if (solutionCount >= 2) {
            copyFromTo(&solution, board);
            return 2;
        }
    }

    if (solutionCount == 1) {
        copyFromTo(&solution, board);
        return 1;
    }

    return 0;
}

void singleValuesInRowsOrColumns(struct helperStructure *helper, bool inRow) {
    int position = 0;
    for (int b = 0; b < BOARD_SIZE; b++) {
        //tablica przedstawia liczbę wystąpień wartości 1...BOARD_SIZE (domyślnie więc 9)
        int tab[BOARD_SIZE] = {0};
        for (int a = 0; a < BOARD_SIZE; a++) {
            int x, y;
            if (inRow) {
                y = b;
                x = a;
            } else {
                y = a;
                x = b;
            }
            position = y * BOARD_SIZE + x;
            for (int value = 0; value < BOARD_SIZE; value++) {
                if (doesHelperContain(helper[position], value + 1)) tab[value]++;
            }
        }

        for (int i = 0; i < BOARD_SIZE; i++) {
            if (tab[i] == 1) {
                //znależliśmy wartość występującą tylko raz (i+1)
                int searchedValue = i + 1;
                //nieważne, co innego jest w jej pomocniku, w komórce musi być ta wartość
                //usuniemy więc wszystkie inne wartości z jej pomocnika

                //najpierw musimy ponownie znaleźć tą wartość
                for (int a = 0; a < BOARD_SIZE; a++) {
                    int x, y;
                    if (inRow) {
                        y = b;
                        x = a;
                    } else {
                        y = a;
                        x = b;
                    }
                    if (doesHelperContain(helper[y * BOARD_SIZE + x], searchedValue)) {
                        position = y * BOARD_SIZE + x;
                        break;
                    }
                }

                //teraz usuwamy wszystkie inne wartości
                for (int value = 1; value < BOARD_SIZE + 1; value++) {
                    if (value == searchedValue) continue;
                    if (doesHelperContain(helper[position], value)) {
                        deleteValueFromHelper(helper + position, value);
                    }
                }
            }
        }

    }
}

void searchAndSolveSingleValues(struct helperStructure helper[]) {
    int position = 0;
    //sprawdzanie wierszy
    singleValuesInRowsOrColumns(helper, false);

    //sprawdzanie kolumn
    singleValuesInRowsOrColumns(helper, true);

    //sprawdzanie podkwadratów


    //iterowanie po kwadratach
    for (int yg = 0; yg < SUBSQUARE_SIZE; yg++) {
        for (int xg = 0; xg < SUBSQUARE_SIZE; xg++) {

            int tab[BOARD_SIZE] = {0};
            for (int xl = 0; xl < SUBSQUARE_SIZE; xl++) {
                for (int yl = 0; yl < SUBSQUARE_SIZE; yl++) {
                    position = (yg * SUBSQUARE_SIZE + yl) * BOARD_SIZE + xg * SUBSQUARE_SIZE + xl;
                    for (int value = 0; value < BOARD_SIZE; value++) {
                        if (doesHelperContain(helper[position], value + 1)) tab[value]++;
                    }
                }
            }

            for (int i = 0; i < BOARD_SIZE; i++) {
                if (tab[i] != 1) continue;
                int searchedValue = i + 1;
                position;

                for (int xl = 0; xl < SUBSQUARE_SIZE; xl++) {
                    for (int yl = 0; yl < SUBSQUARE_SIZE; yl++) {

                        if (doesHelperContain(helper[(yg * SUBSQUARE_SIZE + yl) * BOARD_SIZE + xg * SUBSQUARE_SIZE + xl], searchedValue)) {
                            position = (yg * SUBSQUARE_SIZE + yl) * BOARD_SIZE + xg * SUBSQUARE_SIZE + xl;
                            break;
                        }
                    }
                }

                //teraz usuwamy wszystkie inne wartości
                for (int value = 1; value < BOARD_SIZE + 1; value++) {
                    if (value == searchedValue) continue;
                    if (doesHelperContain(helper[position], value))deleteValueFromHelper(helper + position, value);
                }


            }

        }
    }

}

void findFirstUnknownValue(const struct sudokuBoard *board, bool flag, int *pos, int *x, int *y) {
    while (flag) {
        (*y) = (*pos) / BOARD_SIZE;
        (*x) = (*pos) % BOARD_SIZE;
        if ((board->cells[(*y)][(*x)].constantCell == false) && (board->cells[(*y)][(*x)].value == 0)) {
            flag = false;
        } else {
            (*pos)++;
        }
    }
}

int updateValuesLeftToFill(struct sudokuBoard *board, struct helperStructure *helper, int *valuesLeftToFill) {
    *valuesLeftToFill = BOARD_SIZE * BOARD_SIZE;
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        int y = i / BOARD_SIZE;
        int x = i % BOARD_SIZE;
        if (board->cells[y][x].constantCell || board->cells[y][x].value != 0) {
            (*valuesLeftToFill)--;
            if (*valuesLeftToFill == 0) return 1;
        }
        fillHelperStructureWithPossibleValues(&helper[i], *board, x, y);
    }
    return 0;
}


void findPreemptiveSets(struct sudokuBoard *board, struct helperStructure *hs, bool *failed, int i, int possibleValuesCount, bool *inRow, bool *inCol, bool *inSub) {
    int count = 0;
    //sprawdzanie w kolumnie

    int x = i % BOARD_SIZE;
    int y = i / BOARD_SIZE;

    for (int j = y + 1; j < BOARD_SIZE; j++) {
        int pos = x + j * BOARD_SIZE;
        if ((*board).cells[j][x].constantCell) continue;
        if (areHelpersIdentical(hs[i], hs[pos])) count++;
    }
    if (count + 1 > possibleValuesCount) {
        *failed = true;
        return;
    }
    if (count + 1 == possibleValuesCount) (*inCol) = true;

    //sprawdzanie w wierszu
    count = 0;
    for (int j = x + 1; j < BOARD_SIZE; j++) {
        int pos = j + y * BOARD_SIZE;
        if ((*board).cells[y][j].constantCell) continue;
        if (areHelpersIdentical(hs[i], hs[pos])) count++;
    }
    if (count + 1 > possibleValuesCount) {
        *failed = true;
        return;
    }
    if (count + 1 == possibleValuesCount)(*inRow) = true;

    //sprawdzanie w kwadracie
    count = 0;

    int xa = x / SUBSQUARE_SIZE;
    int ya = y / SUBSQUARE_SIZE;

    for (int xb = 0; xb < SUBSQUARE_SIZE; xb++) {
        for (int yb = 0; yb < SUBSQUARE_SIZE; yb++) {
            int pos = (yb + ya) * BOARD_SIZE + xb + xa;
            if ((*board).cells[yb + ya][xb + xa].constantCell) continue;
            if (areHelpersIdentical(hs[i], hs[pos])) count++;
        }
    }

    if (count > possibleValuesCount) {
        *failed = true;
        return;
    }
    if (count == possibleValuesCount)
        (*inSub) = true;
}

bool searchAndSolvePreemptiveSets(struct sudokuBoard board, struct helperStructure *hs, bool *failed) {
    *failed = false;

    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {

        int x = i % BOARD_SIZE;
        int y = i / BOARD_SIZE;

        int possibleValuesCount = sizeOfHelper(hs[i]);
        if (possibleValuesCount <= 1 || possibleValuesCount == BOARD_SIZE || board.cells[y][x].constantCell)
            continue; //nic nam nie da operowanie na takich wartościach
        //będziemy musieli znaleźć łącznie possibleValueCount pól w tym samym wierszu kolumnie lub podkwadracie (czyli potrzebujemy jeszcze possibleValueCount - 1)

        bool inRow = false;
        bool inCol = false;
        bool inSub = false;

        findPreemptiveSets(&board, hs, failed, i, possibleValuesCount, &inRow, &inCol, &inSub);
        if (*failed == true) return false;

        if (!(inCol || inRow || inSub)) continue;

        //odpowiednie ścieżki

        if (inRow) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                int pos = y * BOARD_SIZE + j;
                if (!areHelpersIdentical(hs[pos], hs[i])) difference(&hs[pos], hs[i]);
            }
        }

        if (inCol) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                int pos = j * BOARD_SIZE + x;
                if (!areHelpersIdentical(hs[pos], hs[i])) difference(&hs[pos], hs[i]);
            }
        }

        int xa, ya;

        if (inSub) {
            xa = x / SUBSQUARE_SIZE;
            ya = y / SUBSQUARE_SIZE;
            for (int xb = 0; xb < SUBSQUARE_SIZE; xb++) {
                for (int yb = 0; yb < SUBSQUARE_SIZE; yb++) {
                    int pos = (yb + ya) * BOARD_SIZE + xb + xa;
                    if (!areHelpersIdentical(hs[pos], hs[i])) difference(&hs[pos], hs[i]);
                }
            }
        }

        return true;

    }

    return false;

}