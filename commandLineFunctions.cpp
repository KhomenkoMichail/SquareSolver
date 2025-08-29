#include <TXLib.h>
#include <stdio.h>

#include "colors.h"
#include "testingFunctions.h"
#include "helpingFunctions.h"
#include "solvingFunctions.h"
#include "interfaceFunctions.h"
#include "inputFunctions.h"
#include "structsAndEnum.h"
#include "commandLineFunctions.h"

int processingCommandLineArguments (int numberOfArguments, char* arguments[]) {
    int continueTheProgram = 1;
    switch (numberOfArguments) {
        case 1:
            break;

        case 2:
            if (!strcmp(arguments[1], "--help"))
                continueTheProgram = modeHelp();
            else if (!strcmp(arguments[1], "--version"))
                continueTheProgram = modeVersion();
            else if (!strcmp(arguments[1], "--single"))
                continueTheProgram = modeSingle();
            else
                continueTheProgram = errorInput();
            break;

        case 3:
            if (!strcmp(arguments[1], "--test"))
                continueTheProgram = modeTest(arguments[2]);
            else
                continueTheProgram = errorInput();
            break;

        default:
                continueTheProgram = errorInput();
    }
    return continueTheProgram;
}

int modeHelp (void) {
    printf(CYAN "Available command line arguments:\n");
    printf("--help - Prints available command line arguments and their description\n");
    printf("--version - Prints program description\n");
    printf("--single - Runs a single solution of a quadratic equation\n");
    printf("--test pathToFile - Runs tests of the function solveSquare,"
            "needs pathToFile as third argument\n" RESET);
    return 0;
}

int modeVersion (void) {
    printf(YELLOW "PROGRAM: SolveSquare\n");
    printf("DESCRIPTION: This program was created to solve quadratic equations\n");
    printf("AUTHOR: Khomenko Michail\n");
    printf("DATE_OF_CREATION: letka rt, august 2025\n" RESET);
    return 0;
}

int modeSingle (void) {
    struct equation quadratic;
    initQuadratic (&quadratic);

    introMessage ();

    getArguments (&quadratic);

    solveSquare (&quadratic);

    announcementOfResults (quadratic);
    return 0;
}

int modeTest (char* pathToFile) {
    struct equation quadratic;
    initQuadratic (&quadratic);

    dynamicBufferFileTests (&quadratic, pathToFile);
    scanningFileTestsSolveSquare (&quadratic, pathToFile);
    integratedTestSolveSquare ();
    return 0;
}

int errorInput (void) {
    printf (RED "Input error, use only available modes:\n");
    printf ("--test pathToFile\n--help\n--version\n--single\n" RESET);
    return 0;
}

