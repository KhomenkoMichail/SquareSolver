#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "solvingFunctions.h"
#include "helpingFunctions.h"
#include "structsAndEnum.h"

void solveSquare (struct equation* quadratic) { //функция решения заданного квадратного уравнения
    assert (isDouble(quadratic->arguments.a));
    assert (isDouble(quadratic->arguments.b));
    assert (isDouble(quadratic->arguments.c));
    assert (quadratic);

    double d = NAN; //дискриминант квадратного уравнения
    double sqrtD = NAN;
    if (compareDouble(quadratic->arguments.a, 0)) {
        if (compareDouble(quadratic->arguments.b, 0)) {
            if (compareDouble(quadratic->arguments.c, 0))
                quadratic->roots.nRoots = infinityRoots;
            else quadratic->roots.nRoots = noRoots;
        }
        else {
            quadratic->roots.x1 = solveLinear(quadratic->arguments.b, quadratic->arguments.c);
            quadratic->roots.nRoots = oneRoot;
        }
    }
    else {
        if (compareDouble(quadratic->arguments.c, 0)) {      // при с == 0
            if (compareDouble(quadratic->arguments.b, 0)) {
                quadratic->roots.x1 = noRoots;
                quadratic->roots.nRoots = oneRoot;
            }
            else {
                quadratic->roots.x1 = noRoots;
                quadratic->roots.x2 = solveLinear(quadratic->arguments.a, quadratic->arguments.b);
                rootsInAscendingOrder (&(quadratic->roots.x1), &(quadratic->roots.x2));
                quadratic->roots.nRoots = twoRoots;
            }
        }

        else {                    // при а != 0 и с != 0
            d = quadratic->arguments.b * quadratic->arguments.b - 4 * quadratic->arguments.a * quadratic->arguments.c;      //вычисление дискриминанта

            if (d < 0)
                quadratic->roots.nRoots = noRoots;

            else if (compareDouble(d, 0)) {    //при  d == 0
                quadratic->roots.x1 = -quadratic->arguments.b/(2*quadratic->arguments.a);
                quadratic->roots.nRoots = oneRoot;
                }

            else {   //при d > 0
                sqrtD = sqrt(d);
                quadratic->roots.x1 = (-quadratic->arguments.b - sqrtD) / (2*quadratic->arguments.a);
                quadratic->roots.x2 = (-quadratic->arguments.b + sqrtD) / (2*quadratic->arguments.a);
                rootsInAscendingOrder (&(quadratic->roots.x1), &(quadratic->roots.x2));
                quadratic->roots.nRoots = twoRoots;
            }
        }
    }
    if (compareDouble(quadratic->roots.x1, 0))
        quadratic->roots.x1 = fabs(quadratic->roots.x1);

    if (compareDouble(quadratic->roots.x2, 0))
        quadratic->roots.x2 = fabs(quadratic->roots.x2);
}

double solveLinear (double k, double b) {
    assert(isDouble(k));
    assert(isDouble(b));

    double x = NAN;
    x = -b / k;
    return x;
}

void rootsInAscendingOrder (double* x1, double* x2) {
    assert(x1);
    assert(x2);

    if(isnan(*x1) || isnan(*x2))
        return;
    if(*x1 > *x2) {
        double cell = *x1;
        *x1 = *x2;
        *x2 = cell;
    }
}

