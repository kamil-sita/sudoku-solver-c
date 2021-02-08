#ifndef SUDOKUTEKSTOWE_GENERATOR_H
#define SUDOKUTEKSTOWE_GENERATOR_H

#include <stdbool.h>
#include "board.h"

/**
 * Generuje wypełnioną planszę sudoku.
 * @param board plansza zwracana przez referencję
 */
void generateFilledSudokuBoard(struct sudokuBoard *board);

/**
 * Na podstawie wypełnionej planszy sudoku, zakrywa niektóre pola. Sprawdza jednocześnie czy plansza ma jedno rozwiązanie (jeżeli jest wymagane).
 * @param alreadyFilledSudokuBoard wypełniona plansza sudoku
 * @param numberOfConstantCells liczba pól, które nie mogą zostać zakryte
 * @param maxTries maksymalna liczba prób
 * @param uniqueSolution unikalne rozwiązanie
 * @return true jeżeli się powiodło
 * @return false jeżeli nie udało się wygenerować planszy
 */
bool selectCluesForSudokuBoard(struct sudokuBoard *alreadyFilledSudokuBoard, int numberOfConstantCells, int maxTries, bool uniqueSolution);

/**
 * Funkcja zmieniająca delikatnie podpowiedzi, żeby spełnić jedną z zasad geometrii wskazówek (clue geometry), dotyczącą niedostatecznej pozycji wskazówek.
 * @param sudoku plansza sudoku
 */
void cheatToMakeEasier(struct sudokuBoard *sudoku);


/**
 * Główna metoda która powinna być użyta przy generowaniu planszy. Generuje planszę sudoku i takie podpowiedzi, że plansza może zostać rozwiązana, zgodnie z warunkami parametru uniqueSolution.
 * @param board zwracana plansza
 * @param constantCells liczba niezakrytych pól
 * @param uniqueSolution wymagaj unikalnego rozwiązania
 * @return true jeżeli się powiodło
 */
bool generateBoard(struct sudokuBoard *board, int constantCells, bool uniqueSolution);

#endif
