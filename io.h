#ifndef SUDOKUTEKSTOWE_IO_H
#define SUDOKUTEKSTOWE_IO_H

/**
 * Wczytuje planszę sudoku z pliku. Plansze sudoku są w formacie pliku tekstowego, w którym kolumny oddzielone są spacjami, a wiersze nowymi liniami.
 * @param sBoard plansza sudoku
 * @param fileLocation lokalicja pliku
 * @return 0 - nie udało się pobrać
 * @return 1 - udało się pobrać planszę
 * @return 2 - udało się pobrać planszę, jednak ma ona złe rozmiary
 */
int loadFromFile(struct sudokuBoard *sBoard, char *fileLocation);

/**
 * Pobiera ciąg znaków od użytkownika.
 * @param string ciąg znaków
 * @param maxSize maksymalny rozmiar ciągu znaków
 */

bool getStringInputFromUser(char *string, int maxSize);

/**
 * Pobiera liczbę całkowitą od użytkownika.
 * @return liczba całkowita
 */
int getIntInputFromUser();

/**
 * Zapisuje planszę sudoku do pliku. Plansze sudoku są w formacie pliku tekstowego, w którym kolumny oddzielone są spacjami, a wiersze nowymi liniami.
 * @param sBoard plansza sudoku
 * @param fileLocation lokalicja błędu
 * @return 0 - błąd otwierania pliku
 * @return 1 - udało się zapisać
 */
int saveToFile(struct sudokuBoard sBoard, char *fileLocation);

#endif
