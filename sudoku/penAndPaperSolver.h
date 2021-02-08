#ifndef SUDOKUTEKSTOWE_H_PENANDPAPERSOLVER
#define SUDOKUTEKSTOWE_H_PENANDPAPERSOLVER

#include "board.h"
#include "../helper.h"

/**
 * Rozwiązuje planszę sudoku korzystając z klasycznego algorytmu rozwiązywania.
 * @param board plansza sudoku do rozwiązania
 * @param limit maksymalna liczba rozwiązań
 * @return -1 - osiągnięto limit
 * @return 0 - brak rozwiązań
 * @return 1 - istnieje jedno rozwiązanie
 * @return 2 - 2 lub więcej rozwiązania

 */
int penAndPaperSolver(struct sudokuBoard *board, int limit);

/**
 * Szuka i rozwiązuje 'nagie pary', trójki, etc.
 * @param board sudoku
 * @param hs tablica struktury pomocniczej
 * @param failed zwraca true w wypadku błędu
 * @return true jeżeli dokonano jakiegokolwiek wykrycia
 * @return false jeżeli się nie powiodło
 */
bool searchAndSolvePreemptiveSets(struct sudokuBoard board, struct helperStructure *hs, bool *failed);

/**
 * Wypełnia strukturę pomocniczą wartościami które można wpisać w odpowiadające komórki.
 * @param board plansza sudoku
 * @param helper struktura pomocnicza
 * @param valuesLeftToFill liczba pól które są jeszcze niezapełnione
 * @return 1 jeżeli została wypełniona plansza w 100%
 */
int updateValuesLeftToFill(struct sudokuBoard *board, struct helperStructure *helper, int *valuesLeftToFill);

/**
 * Przesuwa pos na pozycje pierwszej niezapełnionej komórki.
 * @param board plansza sudoku
 * @param flag zmienna pomocnicza
 * @param pos pozycja niezapełnionej komórki
 * @param x indeks X
 * @param y indeks Y
 */
void findFirstUnknownValue(const struct sudokuBoard *board, bool flag, int *pos, int *x, int *y);

/**
 * Szuka i rozwiązuje ukryte jedynki.
 * @param helper struktura pomocznicza
 */
void searchAndSolveSingleValues(struct helperStructure *helper);

/**
 * Wyszukuje ukryte jedynku w kolumnach lub wierszach
 * @param helper struktura pomocnicza
 * @param inRow czy wyszukiwać w wierszach (false - wyszukiwanie w kolumnach)
 */
void singleValuesInRowsOrColumns(struct helperStructure *helper, bool inRow);

/**
 * Znajduje 'nagie pary'.
 * @param board plansza sudoku
 * @param hs struktura pomocnicza
 * @param failed czy wystąpił błąd
 * @param i id komórki
 * @param possibleValuesCount liczba możliwych do przyjęcia wartości
 * @param inRow czy wykryto w wierszu
 * @param inCol czy wykryto w kolumnie
 * @param inSub czy wykryto w podkwadracie
 */
void findPreemptiveSets(struct sudokuBoard *board, struct helperStructure *hs, bool *failed, int i, int possibleValuesCount, bool *inRow, bool *inCol, bool *inSub);

#endif
