#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>


#include "solvingFunctions.h"
#include "helpingFunctions.h"
#include "structsAndEnum.h"

void solveSquare (struct equation* quadratka) { //функция решения заданного квадратного уравнения
    assert (!(isnan(quadratka->arguments.a)));
    assert (!(isnan(quadratka->arguments.b)));
    assert (!(isnan(quadratka->arguments.c)));
    assert (quadratka);

    double d = NAN; //дискриминант квадратного уравнения
    double sqrtD = NAN;

    if (compareDouble(quadratka->arguments.a, 0)) {
        if (compareDouble(quadratka->arguments.b, 0)) {
            if (compareDouble(quadratka->arguments.c, 0))
                quadratka->roots.nRoots = infinityRoots;
            else quadratka->roots.nRoots = noRoots;
        }
        else {
            quadratka->roots.x1 = solveLinear(quadratka->arguments.b, quadratka->arguments.c);
            quadratka->roots.nRoots = oneRoot;
        }
    }
    else {
        if (compareDouble(quadratka->arguments.c, 0)) {      // при с == 0
            if (compareDouble(quadratka->arguments.b, 0)) {
                quadratka->roots.x1 = noRoots;
                quadratka->roots.nRoots = oneRoot;
            }
            else {
                quadratka->roots.x1 = noRoots;
                quadratka->roots.x2 = solveLinear(quadratka->arguments.a, quadratka->arguments.b);
                rootsInAscendingOrder (&(quadratka->roots.x1), &(quadratka->roots.x2));
                quadratka->roots.nRoots = twoRoots;
            }
        }

        else {                    // при а != 0 и с != 0
            d = quadratka->arguments.b * quadratka->arguments.b - 4 * quadratka->arguments.a * quadratka->arguments.c;      //вычисление дискриминанта

            if (d < 0)
                quadratka->roots.nRoots = noRoots;

            else if (compareDouble(d, 0)) {    //при  d == 0
                quadratka->roots.x1 = -quadratka->arguments.b/(2*quadratka->arguments.a);
                quadratka->roots.nRoots = oneRoot;
                }

            else {   //при d > 0
                sqrtD = sqrt(d);
                quadratka->roots.x1 = (-quadratka->arguments.b - sqrtD) / (2*quadratka->arguments.a);
                quadratka->roots.x2 = (-quadratka->arguments.b + sqrtD) / (2*quadratka->arguments.a);
                rootsInAscendingOrder (&(quadratka->roots.x1), &(quadratka->roots.x2));
                quadratka->roots.nRoots = twoRoots;
            }
        }
    }
    if (compareDouble(quadratka->roots.x1, 0))
        quadratka->roots.x1 = fabs(quadratka->roots.x1);

    if (compareDouble(quadratka->roots.x2, 0))
        quadratka->roots.x2 = fabs(quadratka->roots.x2);
}

double solveLinear (double k, double b) {
    assert(!(isnan(k) || isnan(b)));
    double x = NAN;
    //k == 0
    x = -b / k;
    return x;
}

void rootsInAscendingOrder (double* x1, double* x2) {
    assert(!(x1 == NULL || x2 == NULL));
    if(!(isnan(*x1)))
        if(!(isnan(*x2)))
            if(*x1 > *x2) {
                double cell = *x1;
                *x1 = *x2;
                *x2 = cell;
            }
}

