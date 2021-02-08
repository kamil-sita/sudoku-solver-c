
#include <stdio.h>
#include "generator.h"
#include "board.h"
#include "../helper.h"
#include "backTrackingSolver.h"
#include "penAndPaperSolver.h"
#include "../gameGui.h"
#include "../random.h"

//poniższa liczba została wybrana w sposób sztuczny i nie ma żadnego zastosowania w algorytmie, poza mieszaniem pól w celu wygenerowania sudoku do rozwiązania
//(może być zastąpiona dowolną inną stałą - najlepiej dość dużą)
#define SWAP_COUNT (BOARD_SIZE*BOARD_SIZE*3)

//algorytm backtrackujący https://www.codeproject.com/Articles/23206/Sudoku-Algorithm-Generates-a-Valid-Sudoku-in
//w celu wygenerowania planszy, będziemy stosowali algorytm generujący losowe liczby, i sprawdzający
//czy do tej pory wszystko co zostało wygenerowane, nadal działa - w wypadku wyczerapnia opcji
//algorytm powróci do pierwotnego stanu

void generateFilledSudokuBoard(struct sudokuBoard *board) {

    //inicjalizacja pomocnika, który będzie wykorzystany przy generowaniu planszy
    struct helperStructure helper[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) clearHelperStructure(&(helper[i]));

    //inicjalizacja planszy zerami
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board->cells[i][j].value = 0;
            board->cells[i][j].constantCell = false;
        }
    }

    int cell = 0;

    while (true) {

        int freeValues[BOARD_SIZE];

        int max = fillWithValuesNotIncluded(helper[cell].usedValues, freeValues); //sprawdzenie jakie wartości nie zostały wykorzystane przy próbowaniu "wsadzenia" wartości w cell

        int number = freeValues[generateInteger(0, max - 1)]; //losowa wartość z niewykorzystanych

        if (isInArray(helper[cell].usedValues, number)) continue; //musimy znalezc inna liczbę

        //obliczanie koordynatów komórki -> transformacja 1 wymiaru w 2
        int xPos = cell % BOARD_SIZE;
        int yPos = cell / BOARD_SIZE;

        //wpisywanie wartości do komórki
        board->cells[yPos][xPos].value = (short) number;

        if (isBoardCorrect(*board)) { //udało się wpisać do komórki - przechodzimy do następnej
            cell++;
            if (cell == BOARD_SIZE * BOARD_SIZE) break;
        } else {
            if (!tryAddToArray(helper[cell].usedValues, number)) { //nie ma liczby, ktorej nie sprobawno wpisac, trzeba sprobowac gdzies indziej
                goBackFromCell(&cell, yPos, xPos, &helper[cell], board);
                while (true) {
                    xPos = cell % BOARD_SIZE;
                    yPos = cell / BOARD_SIZE;
                    if (tryAddToArray(helper[cell].usedValues, board->cells[yPos][xPos].value)) break;
                    board->cells[yPos][xPos].value = 0; //dla wszystkich danej liczb w tej komorce nie istnieje rozwiazanie - nalezy sprobowac poprzednia
                    cell--;
                }
            }
        }

    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board->cells[i][j].constantCell = true;
        }
    }
}

bool selectCluesForSudokuBoard(struct sudokuBoard *alreadyFilledSudokuBoard, int numberOfConstantCells, int maxTries, bool uniqueSolution) {

    struct sudokuBoard backupCopy;
    copyFromTo(alreadyFilledSudokuBoard, &backupCopy);
    int iterationCount = 0;
    while (true) {
        if (iterationCount >= maxTries) return false;

        iterationCount++;
        copyFromTo(&backupCopy, alreadyFilledSudokuBoard);

        bool isConst[BOARD_SIZE * BOARD_SIZE];

        //zapełniamy pierwsze numberOfConstantCells komórek podpowiedziami
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) isConst[i] = (i < numberOfConstantCells) ? true : false;

        //losowo zamieniamy te pozycje
        for (int j = 0; j < SWAP_COUNT; j++) {
            int x1 = 0;
            int x2 = 0;
            while (x1 == x2) {
                x1 = generateInteger(0, BOARD_SIZE * BOARD_SIZE);
                x2 = generateInteger(0, BOARD_SIZE * BOARD_SIZE);
            }

            bool tmp = isConst[x1];
            isConst[x1] = isConst[x2];
            isConst[x2] = tmp;
        }

        int i = 0;

        //wpisywanie tych wartości w faktyczną planszę
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                alreadyFilledSudokuBoard->cells[y][x].constantCell = isConst[i];
                i++;
            }
        }

        //delikatnie zwiększamy szansę istnienia rozwiązania
        cheatToMakeEasier(alreadyFilledSudokuBoard);

        struct sudokuBoard tmpCopyToCheckIfSolvable;
        copyOnlyClues(alreadyFilledSudokuBoard, &tmpCopyToCheckIfSolvable);
        int x = penAndPaperSolver(&tmpCopyToCheckIfSolvable, -1);
        if ((x >= 1 && !uniqueSolution) || (x == 1 && uniqueSolution)) {
            struct sudokuBoard tmp;
            copyOnlyClues(alreadyFilledSudokuBoard, &tmp);
            copyFromTo(&tmp, alreadyFilledSudokuBoard);
            return true;
        }
    }

}

bool generateBoard(struct sudokuBoard *board, int constantCells, bool uniqueSolution) {
    renderLineBreaker();
    puts("Szukanie rozwiazywalnych plansz: ");
    for (int i = 0; i < 100; i++) {
        printf(".");
        generateFilledSudokuBoard(board);
        if (selectCluesForSudokuBoard(board, constantCells, 100, uniqueSolution)) { //jeżeli podczas takiej ilości prób nie udało się, może z inną planszą będzie lepiej?
            printf("\n");
            return true;
        }
    }
    printf("\n");
    return false;
}

void cheatToMakeEasier(struct sudokuBoard *sudoku) {
    if (BOARD_SIZE * BOARD_SIZE != 81) return;

    //geometria wskazówek ma sens tylko dla planszy o rozmiarze 9 * 9. Większość rzeczy w tej funkcji jest "zhardkodowana"
    int x = 0;
    int y = 0;
    bool flag = false;

    //sprawdzamy czy można zastosować tutaj geometrię wskazówek
    for (int i = 3; i < 6; i++) {
        for (int j = 3; j < 6; j++) {

            if (!(i == 4 && j == 4)) {
                if (sudoku->cells[i][j].constantCell) flag = true;
            }

        }
    }
    if (!flag) return;
    //zamieniamy pierwsze znalezione pole z podpowiedzią i wracamy
    for (y = 0; y < 9; y++) {
        for (x = 0; x < 9; x++) {
            if (sudoku->cells[y][x].constantCell) {
                sudoku->cells[3][3].constantCell = true;
                sudoku->cells[y][x].constantCell = false;
                return;
            }
        }
    }

}
