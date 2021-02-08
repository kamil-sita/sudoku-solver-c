#include <stdio.h>
#include <stdbool.h>
#include <board.h>
#if _WIN32
#include <mem.h>
#else
#include <memory.h>
#endif
#include "io.h"


int loadFromFile(struct sudokuBoard *sBoard, char *fileLocation) {
    FILE* plik = fopen(fileLocation, "r");
    if (plik == NULL) {
        perror("Blad otwierania pliku!");
        fclose(plik);
        return 0;
    } else {
        int index = 0;
        while (true) {
            int xPos = index%BOARD_SIZE;
            int yPos = index/BOARD_SIZE;

            index++;
            int tmp;
            int pobrano = fscanf(plik, "%d", &tmp);
            if (pobrano != 1) {
                break;
            }
            if (tmp == 0) {
                sBoard->cells[yPos][xPos].value = 0;
                sBoard->cells[yPos][xPos].constantCell = false;
            } else {
                sBoard->cells[yPos][xPos].value = (short) tmp;
                sBoard->cells[yPos][xPos].constantCell = true;
            }
        }
        if (index == BOARD_SIZE * BOARD_SIZE) {
            fclose(plik);
            return 1;
        } else {
            fclose(plik);
            return 2;
        }
    }
}

int saveToFile(struct sudokuBoard sBoard, char *fileLocation) {
    FILE* file = fopen(fileLocation, "w");
    if (file == NULL) {
        perror("Blad otwierania pliku");
        fclose(file);
        return 0;
    }
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            fprintf(file, "%d ", sBoard.cells[y][x].value);
        }
        if (y + 1 != BOARD_SIZE) {
            fprintf(file, "\n");
        }
    }
    fclose(file);
    return 1;
}

bool getStringInputFromUser(char *string, int maxSize) {
    if (fgets(string, maxSize * sizeof(char), stdin) == NULL) return false;
    if (string[strlen(string) - 1] != '\n') {
        bool overwritten = false;
        int overwrittenChar = 0;
        while (((overwrittenChar = getchar()) != '\n') && (overwrittenChar != EOF)) overwritten = true;
        if (overwritten) {
            puts("Za dlugi ciag znakow!");
            return false;
        } else {
            return true;
        }
    }
    string[strlen(string) - 1] = '\0';
    return true;
}

int getIntInputFromUser() {
    int value;
    scanf("%d", &value);
    getchar();
    return value;
}