#ifndef SUDOKUTEKSTOWE_GAMEGUI_H
#define SUDOKUTEKSTOWE_GAMEGUI_H

#include "solver.h"

/**
 * Główna pętla gry i interakcji z użytkownikiem.
 * @param alg algorytm rozwiązywania
 * @param uniqueSolution czy rozwiązanie powinno być unikalne
 */
void runGame(enum solvingAlgorithm alg, bool uniqueSolution);

/**
 * Wypisywanie interfejsu tekstowego.
 * @param sboard plansza sudoku
 * @param yCursor pozycja Y kursora
 * @param xCursor pozycja X kursora
 */
void render(struct sudokuBoard *sboard, int yCursor, int xCursor);

/**
 * Sprawdzenie czy dwa ciągi znaków są jednakowe.
 * @param val1 ciąg znaków
 * @param val2 ciąg znaków
 * @return true jeżeli ciągi są takie same
 * @return false jeżeli ciągi są różne
 */
bool isEqual(char val1[], char val2[]);

/**
 * Pętla generowania planszy sudoku na podstawie podawanych przez użytkownika parametrów.
 * @param sboard plansza sudoku
 * @param uniqueSolution czy rozwiązanie powinno być unikalne
 */
void generate(struct sudokuBoard *sboard, bool uniqueSolution);

/**
 * Konwertowanie cyfry do znaku.
 * @param value cyfra
 * @return odpowiadający znak
 */
char toChar(int value);

/**
 * Wypisuje przerwę (wielokrotne _).
 */
void renderLineBreaker();

/**
 * Pętla zapisywania do pliku do lokalizacji wybranej przez użytkownika.
 * @param sboard plansza sudoku
 * @param msg wiadomość zwrotna
 */
void saveToFileUserInteraction(struct sudokuBoard sboard, char msg[]);

/**
 * Pętla wczytywania z pliku z lokalizacji podanej przez użytkownika.
 * @param sboard plansza sudoku
 * @param msg wiadomość zwrotna
 */
void loadFromFileUserInteraction(struct sudokuBoard *sboard, char msg[]);

#endif
