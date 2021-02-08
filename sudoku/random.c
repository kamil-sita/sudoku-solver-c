#include <time.h>
#include <stdlib.h>
#include "random.h"

int generateInteger(int min, int max) {
    return (int) ((rand() * 1.0)/RAND_MAX * (1 + max - min) + min);
}