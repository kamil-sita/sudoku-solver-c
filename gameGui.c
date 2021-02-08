#include <solver.h>
#include <stdio.h>
#include <history.h>
#include <generator.h>
#include <ctype.h>
#include "gameGui.h"
#include "../sudoku/solver.h"
#include "../io.h"

#if _WIN32
#include <mem.h>
#else
#include <memory.h>
#endif

//stałe dotyczące rozmiarów różnych buforów tekstu
#define USER_TEXT_INPUT_SIZE 256
#define MAX_MSG_LENGTH 256

void runGame(enum solvingAlgorithm alg, bool uniqueSolution) {
    struct sudokuBoard sboard;
    initializeBoard(&sboard);
    struct moveHistory *history = NULL;

    //kursor wskazujący pozycję wpisywania wartości na planszę
    short yCursor = BOARD_SIZE / 2;
    short xCursor = BOARD_SIZE / 2;

    bool resultsFromLastCall = false; //czy powinno wypisać jakąś informację dla użytkownika
    char resultsFromLastCallString[MAX_MSG_LENGTH]; //zawartość informacji
    char userInput[USER_TEXT_INPUT_SIZE];

    while (true) {
        render(&sboard, yCursor, xCursor); //wypisywanie interfejsu

        if (resultsFromLastCall) printf("%s \n", resultsFromLastCallString); //drukowanie wiadomości z poprzedniego przebiegu pętli
        resultsFromLastCall = false;

        while(!getStringInputFromUser(userInput, USER_TEXT_INPUT_SIZE));
        //poniżej znajdują się ścieżki zależne od tekstu wpisanego przez użytkownika

        if (isEqual(userInput, "z")) { //zapisywanie do pliku
            resultsFromLastCall = true;
            saveToFileUserInteraction(sboard, resultsFromLastCallString);
            continue;
        }
        if (isEqual(userInput, "l")) { //wczytywanie z pliku
            resultsFromLastCall = true;
            loadFromFileUserInteraction(&sboard, resultsFromLastCallString);
            freeHistory(&history);
            continue;
        }
        if (isEqual(userInput, "u")) { //cofnij
            undo(&history, &sboard);
            continue;
        }
        if (isEqual(userInput, "e")) { //wyjscie z programu
            freeHistory(&history);
            return;
        }
        if (isEqual(userInput, "g")) { //generowanie planszy
            freeHistory(&history);
            initializeBoard(&sboard);
            generate(&sboard, uniqueSolution);
            continue;
        }
        if (isEqual(userInput, "c")) { //sprawdzanie poprawności planszy
            if (isBoardCorrect(sboard)) {
                strcpy(resultsFromLastCallString, "Podana plansza nie ma blednych pol");
                resultsFromLastCall = true;
            } else {
                strcpy(resultsFromLastCallString, "Podana plansza ma bledne pola");
                resultsFromLastCall = true;
            }
            continue;
        }
        if (isEqual(userInput, "p")) { //restartowanie planszy do pozycji początkowej (cała pusta)
            freeHistory(&history);
            initializeBoard(&sboard);
            continue;
        }
        if (isEqual(userInput, "r")) { //rozwiąż planszę
            resultsFromLastCall = true;
            struct sudokuBoard tmp;
            copyBoardWithFilledValuesAsConstantClues(&sboard, &tmp);
            int s = solveUsingFunction(&tmp, -1, alg);
            if (s >= 1) {
                copyBoardWithAllValuesAsNonConstant(&tmp, &sboard);
                strcpy(resultsFromLastCallString, "Plansza zostala rozwiazana.");
                freeHistory(&history);
            } else {
                strcpy(resultsFromLastCallString, "Plansza nie zostala rozwiazana. Rozwiazanie nie istnieje.");
            }
        }

        //Poruszanie się
        if (isEqual(userInput, "a")) {
            xCursor--;
            if (xCursor < 0) {
                xCursor = 0;
            }
            continue;
        }

        if (isEqual(userInput, "d")) {
            xCursor++;
            if (xCursor >= BOARD_SIZE) {
                xCursor = BOARD_SIZE - 1;
            }
            continue;
        }

        if (isEqual(userInput, "w")) {
            yCursor--;
            if (yCursor < 0) {
                yCursor = 0;
            }
            continue;
        }

        if (isEqual(userInput, "s")) {
            yCursor++;
            if (yCursor >= BOARD_SIZE) {
                yCursor = BOARD_SIZE - 1;
            }
            continue;
        }

        //parsowanie cyfr
        if (isdigit(userInput[0])) {
            addHistory(&history, yCursor, xCursor, sboard.cells[yCursor][xCursor].value);
            sboard.cells[yCursor][xCursor].value = (short) (userInput[0] - '0');
        }

    }

}

void render(struct sudokuBoard *sboard, int yCursor, int xCursor) {

    //zdecydowałem się "zhardcodować" tą funkcję, ponieważ przy różnych rozmiarach planszy pojawiłyby się jeszcze inne problemy powodujące rozjeżdżanie
    // się planszy
    puts("/--------------------------------\\");
    puts("|  z - zapisz plansze            |");
    puts("|  l - wczytaj plansze           |");
    puts("|  g - wygeneruj plansze         |");
    puts("|  c - sprawdz plansze           |");
    puts("|  r - rozwiaz plansze           |");
    puts("|  p - porzuc plansze            |");
    puts("|  u - cofnij ruch               |");
    puts("|  e - wyjdz                     |");
    puts("+--------------------------------+");
    puts("| wasd - poruszaj sie po planszy |");
    puts("|0...9 - wpisz wartosc do planszy|");

    int y = 0;
    int x = 0;

    for (int i = 0; i < SUBSQUARE_SIZE; i++) {
        puts("+----+-------+-------+-------+---+");
        for (int u = 0; u < SUBSQUARE_SIZE; u++) {
            if (yCursor == y && xCursor == 0) {
                printf("|    |[");
            } else {
                printf("|    | ");
            }

            for (int j = 0; j < SUBSQUARE_SIZE; j++) {
                for (int a = 0; a < 3; a++) {
                    if (yCursor == y && xCursor == x) {
                        printf("%c]", toChar(sboard->cells[y][x].value));
                    } else if (yCursor == y && xCursor == x + 1 && (x + 1) % 3 != 0) {
                        printf("%c[", toChar(sboard->cells[y][x].value));
                    } else {
                        printf("%c ", toChar(sboard->cells[y][x].value));
                    }
                    x++;
                }

                x %= BOARD_SIZE;
                if (yCursor == y && xCursor == x && xCursor != 0) {
                    printf("|[");
                } else {
                    printf("| ");
                }

            }
            printf("  |\n");
            y++;
        }

    }
    puts("\\----+-------+-------+-------+---/");


};

bool isEqual(char val1[], char val2[]) {
    return (strcmp(val1, val2) == 0);
}

void saveToFileUserInteraction(struct sudokuBoard sboard, char msg[]) {
    char userInput[USER_TEXT_INPUT_SIZE];
    puts("Podaj lokalizacje zapisu");
    while (!getStringInputFromUser(userInput, USER_TEXT_INPUT_SIZE));
    int status = saveToFile(sboard, userInput);
    switch (status) {
        case 0:
            strcpy(msg, "Nie udalo sie otworzyc pliku. Sprawdz czy plik istnieje i czy masz odpowiednie uprawnienia.");
            break;
        case 1:
            strcpy(msg, "Udalo sie zapisac do pliku.");
            break;
    }
}

void loadFromFileUserInteraction(struct sudokuBoard *sboard, char msg[]) {
    char userInput[USER_TEXT_INPUT_SIZE];
    puts("Podaj lokalizacje pliku");
    while (!getStringInputFromUser(userInput, USER_TEXT_INPUT_SIZE));
    int status = loadFromFile(sboard, userInput);
    switch (status) {
        case 0:
            strcpy(msg, "Nie udalo sie otworzyc pliku. Sprawdz czy plik istnieje i czy masz odpowiednie uprawnienia.");
            break;
        case 1:
        case 2:
            strcpy(msg, "Udalo sie otworzyc z pliku.");
            break;
    }
}

void generate(struct sudokuBoard *sboard, bool uniqueSolution) {
    char userInput[USER_TEXT_INPUT_SIZE];
    while (true) {
        puts("Podaj liczbe stalych komorek (zalecane min 30, niemozliwe ponizej 17)");
        int v = getIntInputFromUser();
        if (v >= 25) {
            if (generateBoard(sboard, v, uniqueSolution)) {
                break;
            }
            puts("Nie udalo sie wygenerowac planszy w pewnym czasie.");
        } else if (v >= 17 || !uniqueSolution) {
            puts("Czy na pewno? (Y/n)");
            while (!getStringInputFromUser(userInput, USER_TEXT_INPUT_SIZE));
            if (isEqual("Y", userInput)) {
                if (generateBoard(sboard, v, uniqueSolution)) {
                    break;
                }
                puts("Nie udalo sie wygenerowac planszy w pewnym czasie.");
            }
        } else {
            puts("Niemozliwe jest wygenerowanie planszy dla takiej wartosci.");
        }
    }
}

char toChar(int value) {
    if (value == 0) {
        return '.';
    } else {
        return (char) (value + '0');
    }
}

void renderLineBreaker() {
    puts("____________________________________________________________________________________________");
    puts("");
}