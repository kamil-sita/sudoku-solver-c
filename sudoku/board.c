#include <malloc.h>
#include "board.h"

void isValueUsedInRow(struct sudokuBoard sboard, int y, bool *row) {
    for (int x = 0; x < BOARD_SIZE; x++)  row[x] = false;

    for (int x = 0; x < BOARD_SIZE; x++) {
        int value = sboard.cells[y][x].value;
        if (value != 0) {
            row[value - 1] = true;
        }
    }
}

void isValueUsedInColumn(struct sudokuBoard sboard, int x, bool *column) {
    for (int y = 0; y < BOARD_SIZE; y++) column[y] = false;

    for (int y = 0; y < BOARD_SIZE; y++) {
        int value = sboard.cells[y][x].value;
        if (value != 0) {
            column[value - 1] = true;
        }
    }
}

void isValueUsedInSubSquare(struct sudokuBoard sboard, int x, int y, bool *subSquare) {
    //współrzędne podkwadratu
    int ys = y / SUBSQUARE_SIZE;
    int xs = x /SUBSQUARE_SIZE;
    for (int a = 0; a < BOARD_SIZE; a++) subSquare[a] = false;

    for (int xp = 0; xp < SUBSQUARE_SIZE; xp++) {
        for (int yp = 0; yp < SUBSQUARE_SIZE; yp++) {

            int value = sboard.cells[ys * SUBSQUARE_SIZE + yp][xs * SUBSQUARE_SIZE + xp].value;
            if (value != 0) subSquare[value - 1] = true;

        }
    }

}

void copyOnlyClues(const struct sudokuBoard *source, struct sudokuBoard *target) {

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {

            if (source->cells[y][x].constantCell == false) {
                target->cells[y][x].constantCell = false;
                target->cells[y][x].value = 0;
            } else {
                target->cells[y][x].constantCell = true;
                target->cells[y][x].value = source->cells[y][x].value;
            }

        }
    }
}

void copyFromTo(struct sudokuBoard *source, struct sudokuBoard *target) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            target->cells[y][x].constantCell = source->cells[y][x].constantCell;
            target->cells[y][x].value = source->cells[y][x].value;
        }
    }
}

bool isBoardCorrect(struct sudokuBoard board) {

    bool liczbaWystapila[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        liczbaWystapila[i] = false;
    }
    //sprawdzanie wierszami

    for (int y = 0; y < BOARD_SIZE; y++) {

        for (int x = 0; x < BOARD_SIZE; x++) {
            int liczba = board.cells[y][x].value - 1; //konwertowanie liczby na miejsce w tablicy.
            if (liczba == -1) continue; //-1 oznacza 0, czli puste pole
            if (liczbaWystapila[liczba] == true) return false;
            liczbaWystapila[liczba] = true;
        }

        for (int i = 0; i < BOARD_SIZE; i++) liczbaWystapila[i] = false;

    }

    //sprawdzanie kolumnami

    for (int x = 0; x < BOARD_SIZE; x++) {

        for (int y = 0; y < BOARD_SIZE; y++) {
            int liczba = board.cells[y][x].value - 1;
            if (liczba == -1) continue;
            if (liczbaWystapila[liczba] == true) return false;
            liczbaWystapila[liczba] = true;
        }

        for (int i = 0; i < BOARD_SIZE; i++) liczbaWystapila[i] = false;
    }

    //sprawdzanie kratkami

    for (int i = 0; i < SUBSQUARE_SIZE; i++) {
        for (int j = 0; j < SUBSQUARE_SIZE; j++) {

            for (int x = 0; x < SUBSQUARE_SIZE; x++) {
                for (int y = 0; y < SUBSQUARE_SIZE; y++) {

                    int liczba = board.cells[y + SUBSQUARE_SIZE * j][x + SUBSQUARE_SIZE * i].value - 1;
                    if (liczba == -1) continue;
                    if (liczbaWystapila[liczba] == true) return false;
                    liczbaWystapila[liczba] = true;

                }
            }

            for (int a = 0; a < BOARD_SIZE; a++) liczbaWystapila[a] = false;

        }
    }

    return true;
}

void initializeBoard(struct sudokuBoard *sboard) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            sboard->cells[y][x].value = 0;
            sboard->cells[y][x].constantCell = false;
        }
    }
}

void copyBoardWithFilledValuesAsConstantClues(struct sudokuBoard *source, struct sudokuBoard *target) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (source->cells[y][x].value != 0) {
                target->cells[y][x].value = source->cells[y][x].value;
                target->cells[y][x].constantCell = true;
            } else {
                target->cells[y][x].value = 0;
                target->cells[y][x].constantCell = false;
            }
        }
    }
}

void copyBoardWithAllValuesAsNonConstant(struct sudokuBoard *source, struct sudokuBoard *target) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            target->cells[y][x].value = source->cells[y][x].value;
            target->cells[y][x].constantCell = false;
        }
    }
}