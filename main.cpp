 /*!
 \file

 */

#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>


#include "testingFunctions.h"
#include "helpingFunctions.h"
#include "solvingFunctions.h"
#include "interfaceFunctions.h"
#include "inputFunctions.h"
#include "structsAndEnum.h"
//TODO: rus -> eng

int main (void) {
    struct equation quadratka;

    testFromFileByBuffer(&quadratka);
    testsFromFile(&quadratka);
    testSolveSquare ();


    int keepSolving = 1;
    while (keepSolving) {

        initQuadratka (&quadratka);

        introMessage();

        getArguments (&quadratka);

        solveSquare (&quadratka);

        announcementOfResults (quadratka);

        requestToContinue (&keepSolving);
    }

    printf ("The program ended!\n");
    return 0;
}

