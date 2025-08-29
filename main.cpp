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
#include "commandLineFunctions.h"

int main (int argc, char* argv[]) {
    int keepSolving = processingCommandLineArguments (argc, argv);

    struct equation quadratic;
    initQuadratic (&quadratic);

    if (keepSolving) {
        dynamicBufferFileTests (&quadratic, "tests.txt");
        scanningFileTestsSolveSquare (&quadratic, "tests.txt");
        integratedTestSolveSquare ();
    }

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

