#include <TXLib.h>
#include <stdio.h>
#include <assert.h>

#include "helpingFunctions.h"
#include "helpingFunctions.h"
#include "structsAndEnum.h"

const double EPSILON = 1e-10;

void bufferCleaner (void) { //функция пропуска входных данных
    int ch = 0;
    while ((ch = getchar()) != '\n')
        continue;
}

int compareDouble (double first, double second) {
    if (isnan(first) && isnan(second))      //оба nan
        return 1;
    else if (isinf(first) && isinf(second))      //оба inf
        return 1;
    else {
        double fabsOfDifference = NAN;
        fabsOfDifference = fabs(first - second);

        if (fabsOfDifference < EPSILON)
            return 1;
        return 0;
    }
}

void initQuadratic (struct equation* quadratic) {
    assert(quadratic);
    *quadratic = {
        .arguments = {
            .a = NAN,
            .b = NAN,
            .c = NAN
        },
        .roots = {
            .x1 = NAN,
            .x2 = NAN,
            .nRoots = indefinityRoots
        }
    };
}

int isDouble (double x) {
    if (isnan(x) || isinf(x))
        return 0;
    return 1;
}
