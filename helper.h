#ifndef SUDOKUTEKSTOWE_POMOCNICZE_H
#define SUDOKUTEKSTOWE_POMOCNICZE_H


///struktura pomocnicza, która może być wykorzystana przy sprawdzaniu rozwiązania/generowania planszy. Zapełniania jest od zerowej komórki.
struct helperStructure {
///tablica użytych wartości
    int usedValues[BOARD_SIZE]; 
};

/**
 * Czyści strukturę pomocniczą (ustawia wszystkie wartości w tablicy na 0).
 * @param hs wskaźnik na strukturę pomocniczą
 */
void clearHelperStructure(struct helperStructure *hs);

/**
 * Zwraca rozmiar struktury pomocniczej (liczba niezerowych komórek).
 * @param hs struktura pomocnicza
 * @return rozmiar struktury pmocniczej
 */
int sizeOfHelper(struct helperStructure hs);

/**
 * Sprawdza czy w tablicy o rozmiarze BOARD_SIZE znajduje się wartość value
 * @param arr tablica
 * @param value wartość
 * @return true jeżeli wartość występuje
 * @return false jeżeli wartość nie występuje
 */
bool isInArray(int *arr, int value);

/**
 * Próbuje dodać wartość value do tablicy. Jeżeli nie jest to możliwe, zwraca false. Tablica wypełniana jest od zerowej komórki
 * @param arr tablica
 * @param value wartość
 * @return true jeżeli udało się dodać do tablicy
 * @return false jeżeli nie udało się dodać to tablicy
 */
bool tryAddToArray(int *arr, int value);

/**
 * Dodaje wartość value do tablicy arr o rozmiarze BOARD_SIZE. Tablica wypełniania jest od zerowej komórki
 * @param arr tablica
 * @param value wartość
 */
void addToArrayOfBoardSize(int arr[], int value);

/**
 * Sprawdza które wartości z zakresu (0; BOARD_SIZE) nie znajdują się w tablicy input, i zwraca je przez output
 * @param input tablica sprawdzana
 * @param output tablica wyjściowa
 * @return liczba wartości
 */
int fillWithValuesNotIncluded(int *input, int *output);

/**
 * Sprawdza dla planszy board, jakie wartości mogą być wpisane do komórki - zwraca je do hs
 * @param hs wskaźnik strutur pomocniczych
 * @param board plansza sudoku
 * @param x pozycja x
 * @param y pozycja y
 */
void fillHelperStructureWithPossibleValues(struct helperStructure *hs, struct sudokuBoard board, int x, int y);

/**
 * Funkcja poszukuje wartości w strukturze pomocniczej
 * @param hs struktura pomocnicza
 * @param value wartość
 * @return true jeżeli wartość występuje
 * @return false jeżeli wartość nie występuje
 */
bool doesHelperContain(struct helperStructure hs, int value);

/**
 * Sprawdza czy wszystkie wartości w strukturach pomocniczych są takie same. Nie porównuje ich położenia, a jedynie ich wartości - przykładowo (2, 4, 6) i (6, 2, 4) są takie same.
 * @param hs1 struktura pomocnicza
 * @param hs2 struktura pomocnicza
 * @return true jeżeli struktury są takie same
 * @return false jeżeli struktury różnią się
 */
bool areHelpersIdentical(struct helperStructure hs1, struct helperStructure hs2);

/**
 * Usuwa wartość value ze struktury pomocniczej. Przesuwa wszystkie następne wartości na poprzednie pozycje).
 * @param hs struktura pomocnicza
 * @param value wartość
 */
void deleteValueFromHelper(struct helperStructure *hs, int value);

/**
 * Usuwa wszystkie wartości ze struktury pomocniczej, które występują w drugiej strukturze pomocniczej.
 * @param deleteFrom struktura pomocnicza z której należy usunąć wartości
 * @param deleteWhat struktura pomocnicza z wartościami do usunięcia
 */
void difference(struct helperStructure *deleteFrom, struct helperStructure deleteWhat);

#endif
