/*!
    \file
    \brief Main file
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "colors.h"
#include "testingFunctions.h"
#include "helpingFunctions.h"
#include "solvingFunctions.h"
#include "interfaceFunctions.h"
#include "inputFunctions.h"
#include "structsAndEnum.h"

int main (void) {
    struct equation quadratic;

    testFromFileByBuffer (&quadratic);
    testsFromFile (&quadratic);
    testSolveSquare ();

    int keepSolving = 1;
    while (keepSolving) {

        initQuadratic (&quadratic);

        introMessage ();

        getArguments (&quadratic);

        solveSquare (&quadratic);

        announcementOfResults (quadratic);

        requestToContinue (&keepSolving);
    }

    printf ("%sThe program ended!%s\n",MAGENTA, RESET);
    return 0;
}

