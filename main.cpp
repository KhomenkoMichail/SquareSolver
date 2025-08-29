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

//--test <path/to/file>
// --help
// --version
// --

int main (void) {
    struct equation quadratic;

    dynamicBufferFileTests (&quadratic);
    scanningFileTestsSolveSquare (&quadratic);
    integratedTestSolveSquare ();

    int keepSolving = 1;
    while (keepSolving) {

        initQuadratic (&quadratic);

        introMessage ();

        getArguments (&quadratic);

        solveSquare (&quadratic);

        announcementOfResults (quadratic);

        requestToContinue (&keepSolving);
    }

    printf (MAGENTA "The program ended!\n" RESET);
    return 0;
}

