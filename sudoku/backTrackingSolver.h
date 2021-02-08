#ifndef SUDOKUTEKSTOWE_BACKTRACKINGSOLVER_H
#define SUDOKUTEKSTOWE_BACKTRACKINGSOLVER_H

#include "board.h"
#include "../helper.h"

/** Rozwiązuje sudoku metodą z nawrotami (brute-force)
 * @param board sudoku do rozwiązania (następuje zwrot przez referencję)
 * @param limit maksymalna liczba iteracji (ignorowane dla liczb ujemnych)
 * @return -1 - osiągnięto limit
 * @return 0 - brak rozwiązań
 * @return 1 - istnieje jedno rozwiązanie
 * @return 2 - 2 lub więcej rozwiązania

 */
int bruteForceSolver(struct sudokuBoard *board, int limit);

/**
 * Powrót z komórki algorytmu z nawrotami, po znalezieniu rozwiązania.
 * @param cell id komórki
 * @param solutionCount liczba rozwiązań
 * @param board plansza sudoku
 * @param solution rozwiązane sudoku
 */
void goBackFromCorrectSolutionBacktrackingSolver(int *cell, int *solutionCount, struct sudokuBoard *board,
                                                 struct sudokuBoard *solution);

/**
 * Funkcja odpowiedzialna za powrót z komórki algorytmu z nawrotami.
 * @param cell id komórki
 * @param yPos pozycja Y
 * @param xPos pozycja X
 * @param helper struktura pomocnicza
 * @param board sudoku
 */
void goBackFromCell(int *cell, int yPos, int xPos, struct helperStructure *helper,
                    struct sudokuBoard *board);

/**
 * Funkcja wywoływana na początku każdej iteracji, w przypadku gdy komórka jest stała.
 * @param board plansza sudoku
 * @param solution rozwiązanie (może być zwrócone przez referencję)
 * @param cell id komórki
 * @param solutionCount liczba rozwiązań
 * @param goingBackFromConstCell czy należy się wycofać
 * @param number wartość która może być zwrócona jeżeli odwiedziliśmy ostatnią komórkę - jej wartość
 * @return id odpowiedniego rozkazu dla algorytmu z nawrotami
 */
int constantCellSubroutine(struct sudokuBoard *board, struct sudokuBoard *solution, int *cell, int *solutionCount, bool *goingBackFromConstCell, int *number);

/**
 * Funkcja wywoływana na początku każdej iteracji, w przypadku gdy komórka nie jest stała. Wybiera liczbę do wpisania do komórki i sprawdza czy plansza nadal jest poprawna.
 * @param board plansza sudoku
 * @param helper struktura pomocnicza
 * @param cell id komórki
 * @param xPos pozycja X komórki
 * @param yPos pozycja Y komórki
 * @param filledCell czy udało się wpisać do komórki
 * @param number liczba którą chcemy wpisać
 * @return odpowiedni rozkaz dla algorytmu z nawrotami
 */
bool nonConstantCellSubroutine(struct sudokuBoard *board, struct helperStructure *helper, int cell, int xPos, int yPos, bool *filledCell, int *number);

/**
 * Funkcja pomocnicza algorytmu z nawrotami: powrót z komórki spowodowany wykorzystaniem wszystkich możliwości.
 * @param board plansza sudoku
 * @param helper
 * @param cell
 * @param xPos
 * @param yPos
 * @param filledCell
 */
void allNumbersTriedSubroutine(struct sudokuBoard *board, struct helperStructure *helper, int *cell, int xPos, int yPos,
                               bool filledCell);

#endif