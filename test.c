#if _WIN32
#include <mem.h>
#else
#include <memory.h>
#endif
#include <assert.h>
#include <backTrackingSolver.h>
#include <stdio.h>
#include <penAndPaperSolver.h>
#include <generator.h>
#include "test.h"
#include "io.h"
#include "sudoku/history.h"
#include "gameGui.h"

#define ROZMIAR_BUFORA 64

void testy() {
    char lokacja[ROZMIAR_BUFORA];
    struct sudokuBoard plansza;

    //testy sudoku backtracing

    strncpy(lokacja, "daneTestowe/planszaZwykla1Rozwiazanie.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(bruteForceSolver(&plansza, -1) == 1);

    strncpy(lokacja, "daneTestowe/planszaDuzoRozwiazan.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(bruteForceSolver(&plansza, -1) == 2);

    strncpy(lokacja, "daneTestowe/plansza0rozwiazan.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(bruteForceSolver(&plansza, -1) == 0);

    strncpy(lokacja, "daneTestowe/trudnaPlansza.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(bruteForceSolver(&plansza, -1) == 1);

    strncpy(lokacja, "daneTestowe/brak.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(bruteForceSolver(&plansza, -1) == 1);


    //testy sudoku klasyczne

    strncpy(lokacja, "daneTestowe/planszaZwykla1Rozwiazanie.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(penAndPaperSolver(&plansza, -1) == 1);

    strncpy(lokacja, "daneTestowe/trudnaPlansza.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(penAndPaperSolver(&plansza, -1) == 1);

    strncpy(lokacja, "daneTestowe/btrudnaplansz.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(penAndPaperSolver(&plansza, -1) == 1);

    strncpy(lokacja, "daneTestowe/plansza0rozwiazan.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(penAndPaperSolver(&plansza, -1) == 0);

    strncpy(lokacja, "daneTestowe/planszaDuzoRozwiazan.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(penAndPaperSolver(&plansza, -1) == 2);


    strncpy(lokacja, "daneTestowe/plansza2Rozwiazania.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(penAndPaperSolver(&plansza, -1) == 2);

    strncpy(lokacja, "daneTestowe/brak.txt", ROZMIAR_BUFORA);
    loadFromFile(&plansza, lokacja);
    assert(penAndPaperSolver(&plansza, -1) == 1);

    render(&plansza, -1, -1);

    //inne testy

    //testowanie moveHistory
    struct moveHistory *h = NULL;
    addHistory(&h, 1, 2, 3);
    addHistory(&h, 5, 6, 7);
    addHistory(&h, 155, 14, 13);

    assert(elementAt(h, 0)->x == 2);
    assert(elementAt(h, 1)->y == 5);
    assert(historySize(h) == 3);

    deleteLast(&h);

    assert(historySize(h) == 2);

    assert(elementAt(h, 1)->y == 5);

    freeHistory(&h);

    assert(historySize(h) == 0);

    //test generatora
    struct sudokuBoard sb;
    generateBoard(&sb, 40, true);
    generateBoard(&sb, 28, true);
    generateBoard(&sb, 25, false);
}
