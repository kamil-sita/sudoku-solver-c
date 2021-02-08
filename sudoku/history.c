#include <malloc.h>
#include <board.h>
#include "history.h"

void addHistory(struct moveHistory **historyOfMoves, short int y, short int x, short int value) {

    if (*historyOfMoves == NULL) { //nowy element to pierwszy element listy
        *historyOfMoves = malloc(sizeof(struct moveHistory));
        (*historyOfMoves)->previousValue = value;
        (*historyOfMoves)->y = y;
        (*historyOfMoves)->x = x;
        (*historyOfMoves)->next = NULL;
    } else {
        struct moveHistory *tmp = *historyOfMoves;

        //przesuwanie wskaźnika na ostatni element
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }

        tmp->next = malloc(sizeof(struct moveHistory));
        tmp = tmp->next;
        tmp->previousValue = value;
        tmp->y = y;
        tmp->x = x;
        tmp->next = NULL;

    }
}

void freeHistory(struct moveHistory **historyOfMoves) {
    //rekurencyjnie zwalniamy historię
    if (*historyOfMoves != NULL) {
        freeHistory(&(*historyOfMoves)->next);
        free(*historyOfMoves);
        *historyOfMoves = NULL;
    }
}

int historySize(struct moveHistory *historyOfMoves) {
    if (historyOfMoves == NULL) return 0;
    int size = 0;
    struct moveHistory *tmp;
    tmp = historyOfMoves;
    while (tmp != NULL) {
        tmp = tmp->next;
        size++;
    }
    return size;
}

struct moveHistory* elementAt(struct moveHistory *history, int index) {
    if (history == NULL) return NULL;
    if (index < 0 || index > historySize(history)) return NULL;

    int pos = index;
    struct moveHistory *tmp;
    tmp = history;
    while (pos != 0) {
        tmp = tmp->next;
        pos--;
    }
    return tmp;
}

void deleteLast(struct moveHistory **history) {
    if (history == NULL) return;
    int size = historySize(*history);
    if (size == 0) return;
    if (size == 1) {
        free(*history);
        *history = NULL;
        return;
    }
    struct moveHistory *searchedValue = elementAt(*history, size - 1);
    struct moveHistory *tmp = *history;
    while (tmp->next != searchedValue) {
        tmp = tmp->next;
    }
    free(tmp->next);
    tmp->next = NULL;
}

void undo(struct moveHistory **historyOfMoves, struct sudokuBoard *sboard) {
    if (historySize(*historyOfMoves) == 0) return;
    struct moveHistory *toUndo = elementAt(*historyOfMoves, historySize(*historyOfMoves) - 1);
    sboard->cells[toUndo->y][toUndo->x].value = toUndo->previousValue;
    deleteLast(historyOfMoves);
}