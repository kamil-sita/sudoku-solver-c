#ifndef SUDOKUTEKSTOWE_PLANSZA_H
#define SUDOKUTEKSTOWE_PLANSZA_H

///rozmiar glowny planszy sudoku (szerokość, wysokość, liczba podkwadratów)
#define BOARD_SIZE 9
///Rozmiar tzw podplanszy, podkwadratu, subkwadratu. Dla kwadratowych sudoku (k x k) SUBSQUARE_SIZE^2 = BOARD_SIZE
#define SUBSQUARE_SIZE 3

#include <stdbool.h>
#include <malloc.h>
#include "board.h"


///Struktura reprezentująca pojedynczą komórkę w planszy sudoku
struct cell {
	///wartość komórki
    short int value; 
	///czy komórka jest podpowiedzią (jeżeli jest podpowiedzią, nie może zostać zmieniona)
    bool constantCell; 
};


///Struktura reprezentująca planszę - dwuwymiarowa tablica komórek
struct sudokuBoard {
///tablica komórek
    struct cell cells[BOARD_SIZE][BOARD_SIZE];
};

/**
 * Kopiuje planszę tylko z podpowiedziami. W miejsce innych komórek wstawia 0.
 * @param source plansza źródłowa
 * @param target plansza do której należy skopiować
 */
void copyOnlyClues(const struct sudokuBoard *source, struct sudokuBoard *target);

/**
 * Kopiuje planszę.
 * @param source plansza źródłowa
 * @param target plansza do której należy skopiować
 */
void copyFromTo(struct sudokuBoard *source, struct sudokuBoard *target);

/**
 * Sprawdza poprawność planszy, przy czym nie zgłasza pustych pól jako błąd, a tylko powtarzające się wartości.
 * @param board plansza sudoku
 * @return true jeżeli plasnza poprawna
 * @return false jeżeli plansza błędna
 */
bool isBoardCorrect(struct sudokuBoard board);

/**
 * Sprawdza czy wartość była wykorzystana w danym wierszu. Wykorzystuje tablicę bool row[] o rozmiarze BOARD_SIZE. Jeżeli np wartość 3 występowała, to row[3 - 1] == true.
 * @param sboard plansza sudoku
 * @param y wiersz
 * @param row tablica zwracana przez referencję
 */
void isValueUsedInRow(struct sudokuBoard sboard, int y, bool *row);

/**
 * Sprawdza czy wartość była wykorzystana w danej kolumnie. Wykorzystuje tablicę bool col[] o rozmiarze BOARD_SIZE. Jeżeli np wartość 3 występowała, to col[3 - 1] == true.
 * @param sboard plansza sudoku
 * @param x kolumna
 * @param column tablica zwracana przez referencję
 */
void isValueUsedInColumn(struct sudokuBoard sboard, int x, bool *column);

/**
 * Sprawdza czy wartość była wykorzystana w danym podkwadracie. Wykorzystuje tablicę bool subs[] o rozmiarze BOARD_SIZE. Jeżeli np wartość 3 występowała, to subs[3 - 1] == true.
 * @param sboard plansza sudoku
 * @param y wiersz
 * @param x kolumna
 * @param row tablica zwracana przez referencję
 */
void isValueUsedInSubSquare(struct sudokuBoard sboard, int x, int y, bool *subSquare);

/**
 * Wypełnia planszę zerami
 * @param sboard  plansza sudoku
 */
void initializeBoard(struct sudokuBoard *sboard);

/**
 * Kopiuje planszę, przy czym wszystkie wartości różne od zera ustawia jako wartości stałe
 * @param source plansza oryginalna
 * @param target plansza docelowa
 */
void copyBoardWithFilledValuesAsConstantClues(struct sudokuBoard *source, struct sudokuBoard *target);

/**
 * Kopijue planszę, przy czym wszystkie wartości ustawia jako wartości niestałe.
 * @param source planzsa oryginalna
 * @param target plansza docelowa
 */
void copyBoardWithAllValuesAsNonConstant(struct sudokuBoard *source, struct sudokuBoard *target);

#endif
