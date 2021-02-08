#include "board.h"
#include "helper.h"


void clearHelperStructure(struct helperStructure *hs) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        hs->usedValues[i] = 0;
    }
}

int sizeOfHelper(struct helperStructure hs) {
    for (int i = 0; i < BOARD_SIZE;  i++) {
        if (hs.usedValues[i] == 0) {
            return i;
        }
    }
    return 9;
}

void fillHelperStructureWithPossibleValues(struct helperStructure *hs, struct sudokuBoard board, int x, int y) {
    bool column[BOARD_SIZE];
    bool row[BOARD_SIZE];
    bool subSquare[BOARD_SIZE];

    clearHelperStructure(hs);

    if (board.cells[y][x].value != 0) return;

    isValueUsedInColumn(board, x, column);
    isValueUsedInRow(board, y, row);
    isValueUsedInSubSquare(board, x, y, subSquare);

    for (int value = 0; value < BOARD_SIZE; value++) { //faktyczna wartość value jest przesunięta o 1
        if (!(column[value] || row[value] || subSquare[value])) {

            addToArrayOfBoardSize(hs->usedValues, value + 1);
        }
    }

}

bool isInArray(int *arr, int value) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}


//Probuje dodac do tablicy o rozmiarze BOARD_SIZE wartość value. Jezeli spowodowaloby to zapelnienie tablicy, zwraca false.
bool tryAddToArray(int arr[], int value) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (arr[i] == 0) {
            if (i + 1 != BOARD_SIZE) {
                arr[i] = value;
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

//funkcja analogiczna do poprzedniej, ale pozwala na zapis do ostatniej wartości, i nic nie zwraca
void addToArrayOfBoardSize(int arr[], int value) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (arr[i] == 0) {
            arr[i] = value;
            return;
        }
    }
}

int fillWithValuesNotIncluded(int *input, int *output) {
    int x = 0;
    for (int i = 1; i < BOARD_SIZE + 1; i++) {
        if (isInArray(input, i) == false) {
            output[x] = i;
            x++;
        }
    }
    for (int a = x; a < BOARD_SIZE; a++) {
        output[a] = 0;
    }
    return x;
}

bool areHelpersIdentical(struct helperStructure hs1, struct helperStructure hs2) {
    if (sizeOfHelper(hs1) != sizeOfHelper(hs2)) return false;
    for (int i = 0; i < sizeOfHelper(hs1); i++) {
        if (!doesHelperContain(hs2, hs1.usedValues[i])) return false;
    }
    return true;
}

bool doesHelperContain(struct helperStructure hs, int value) {
    for (int i = 0; i < sizeOfHelper(hs); i++) {
        if (hs.usedValues[i] == value) return true;
    }
    return false;
}

void difference(struct helperStructure *deleteFrom, struct helperStructure deleteWhat) {
    for (int i = 0; i < sizeOfHelper(deleteWhat); i++) {
        deleteValueFromHelper(deleteFrom, deleteWhat.usedValues[i]);
    }
}

void deleteValueFromHelper(struct helperStructure *hs, int value) {
    int i = 0;
    bool deleted = false;
    for (i = 0; i < BOARD_SIZE; i++) {
        if (hs->usedValues[i] == value) {
            hs->usedValues[i] = 0;
            deleted = true;
            break;
        }
    }
    if (!deleted) return;

    for (; i + 1 < BOARD_SIZE; i++) {
        hs->usedValues[i] = hs->usedValues[i + 1];
    }
    hs->usedValues[BOARD_SIZE - 1] = 0;
}