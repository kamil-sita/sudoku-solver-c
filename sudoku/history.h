#ifndef SUDOKUTEKSTOWE_HISTORY_H
#define SUDOKUTEKSTOWE_HISTORY_H


/// Dynamiczna struktura listowa reprezentująca historię ruchów przy rozwiązywaniu sudoku przez użytkownika
struct moveHistory {
	///poprzednia wartosc
    short int previousValue; 
///pozycja poprzedniej wartosci
    short int y; 
///pozycja poprzedniej wartosci
    short int x; 
///wskaznik na kolejny element listy
    struct moveHistory *next; 
};

/**
 * Dodaje element do listy.
 * @param historyOfMoves podwójny wskaźnik na listę
 * @param y pozycja y komórki
 * @param x pozycja x komórki
 * @param value poprzednia wartość w komórce
 */
void addHistory(struct moveHistory **historyOfMoves, short int y, short int x, short int value);

/**
 * Zwalnia całą pamięć wykorzystaną na listę, usuwając jej zawartość.
 * @param historyOfMoves podwójny wskaźnik na listę
 */
void freeHistory (struct moveHistory **historyOfMoves);

/**
 * Zwraca rozmiar listy.
 * @param historyOfMoves lista
 * @return rozmiar listy
 */
int historySize(struct moveHistory *historyOfMoves);

/**
 * Zwraca element listy o odpowiednim indeksie.
 * @param history lista
 * @param index index elementu
 * @return szukany element listy
 */
struct moveHistory* elementAt(struct moveHistory *history, int index);

/**
 * Usuwa ostatni element listy.
 * @param history lista
 */
void deleteLast(struct moveHistory **history);

/**
 * Cofa ostatni ruch gracza: na podstawie ostatniego elementu listy zmienia stan planszy, i usuwa ostatni element listy.
 * @param historyOfMoves lista
 * @param sboard plansza sudoku
 */
void undo(struct moveHistory **historyOfMoves, struct sudokuBoard *sboard);

#endif
