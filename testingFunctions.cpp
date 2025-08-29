#include <TXLib.h>
#include <stdio.h>

#include "myassert.h"
#include "colors.h"
#include "testingFunctions.h"
#include "helpingFunctions.h"
#include "structsAndEnum.h"
#include "solvingFunctions.h"

void integratedTestSolveSquare (void) {
    int failedTests = 0;

    struct equation testingArguments [] = {      //testing equations
      { { 0,  0,  0 }, { NAN, NAN, indefinityRoots } },
      { { 0,  2,  2 }, { NAN, NAN, indefinityRoots } },
      { { 0,  0,  2 }, { NAN, NAN, indefinityRoots } },
      { { 2,  2,  0 }, { NAN, NAN, indefinityRoots } },
      { { 1,  0, -4 }, { NAN, NAN, indefinityRoots } },
      { { 1, -5,  6 }, { NAN, NAN, indefinityRoots } },
      { { 1,  2,  1 }, { NAN, NAN, indefinityRoots } },
      { { 0,  2,  0 }, { NAN, NAN, indefinityRoots } },
      { { 1,  1,  1 }, { NAN, NAN, indefinityRoots } },
      { { 1, -3,  2 }, { NAN, NAN, indefinityRoots } }
    };

    int testNum = sizeof (testingArguments) / sizeof (testingArguments[0]);

    struct solution testSolutions[] = { { infinityRoots, NAN, NAN },   //solutions for testing equations
                                              { oneRoot,  -1, NAN },
                                              { noRoots, NAN, NAN },
                                              { twoRoots,  -1,  0 },
                                              { twoRoots, -2,   2 },
                                              { twoRoots,  2,   3 },
                                              { oneRoot, NAN,  -1 },
                                              { oneRoot,   0, NAN },
                                              { noRoots, NAN, NAN },
                                              { twoRoots,  1,   2 } };

    for (int test = 0; test < testNum; test++)
            failedTests += oneTest (&testingArguments[test], testSolutions[test]);

    printf (GREEN "Number of passed integrated tests = %d\n" RESET, testNum - failedTests);
    printf (BLUE "Number of failed integrated tests  = %d\n\n" RESET, failedTests);
}

int oneTest (struct equation* testingArguments, struct solution testSolutions) {
        MYASSERT(testingArguments);

        solveSquare(testingArguments);

        if (!(testingArguments->roots.nRoots == testSolutions.nAnswers &&
              (compareDouble(testingArguments->roots.x1, testSolutions.firstRoot) || compareDouble(testingArguments->roots.x1, testSolutions.secondRoot)) &&
              (compareDouble(testingArguments->roots.x2, testSolutions.secondRoot) || compareDouble(testingArguments->roots.x2, testSolutions.firstRoot)))) {
            printf (RED "FAILED: solveSquare(%lg, %lg, %lg) --> nRoots = %d, x1 = %lg, x2 = %lg\n",
                    testingArguments->arguments.a, testingArguments->arguments.b, testingArguments->arguments.c,
                    testingArguments->roots.nRoots, testingArguments->roots.x1, testingArguments->roots.x2);
            printf ("should be nRoots = %d, x1 = %lg, x2 = %lg\n\n" RESET,
                    testSolutions.nAnswers, testSolutions.firstRoot, testSolutions.secondRoot);
            return 1;
        }
        return 0;
}

void scanningFileTestsSolveSquare (struct equation* quadratic, const char* pathToFile) {
    MYASSERT(quadratic);

    int failedFileTests = 0;
    int passedFileTests = 0;

    initQuadratic (quadratic);

    struct solution fileSolution;
    initFileSolution (&fileSolution);

    FILE* file = fopen(pathToFile, "rb");
    if (file!= NULL) {
        failedFileTests = readFromFileAndTest(quadratic, &fileSolution, file, &passedFileTests);
        printf (GREEN "Number of passed scanning file tests = %d\n" RESET, passedFileTests);
        printf(BLUE "Number of failed scanning file tests = %d\n\n" RESET, failedFileTests);
        if (fclose(file) != 0)
            printf(RED "Error: the file was not closed! Check the file tests.txt\n" RESET);
    }
    else printf(RED "Error: the file was not opened! Check the file tests.txt\n" RESET);
}

void initFileSolution (struct solution* fileSolution) {
    MYASSERT(fileSolution);

    *fileSolution = { .nAnswers = indefinityRoots,
                      .firstRoot = NAN,
                      .secondRoot = NAN };
}

int readFromFileAndTest(struct equation* quadratic, struct solution* fileSolution, FILE* file, int* passedFileTests) {
    MYASSERT(quadratic);
    MYASSERT(fileSolution);
    MYASSERT(file);

    int failedFileTests = 0;
    int allTests = 0;
    while (fscanf (file, "%lf", &(quadratic->arguments.a)) == 1) {
        allTests++;
        fscanf (file, "%lf", &(quadratic->arguments.b));
        fscanf (file, "%lf", &(quadratic->arguments.c));
        fscanf (file, "%d",  (int*) &fileSolution->nAnswers);
        switch (fileSolution->nAnswers)
        {
            case oneRoot:
                fscanf (file, "%lf", &fileSolution->firstRoot);
                fileSolution->secondRoot = NAN;
                break;
            case twoRoots:
                fscanf (file, "%lf", &fileSolution->firstRoot);
                fscanf (file, "%lf", &fileSolution->secondRoot);
                break;
            case infinityRoots:
                fileSolution->firstRoot = NAN;
                fileSolution->secondRoot = NAN;
                break;
            case noRoots:
                fileSolution->firstRoot = NAN;
                fileSolution->secondRoot = NAN;
                break;
            case indefinityRoots:
                fileSolution->firstRoot = NAN;
                fileSolution->secondRoot = NAN;
                break;
            default:
                fileSolution->firstRoot = NAN;
                fileSolution->secondRoot = NAN;
                break;
        }
        failedFileTests += oneTest(quadratic, *fileSolution);
        initFileSolution (fileSolution);
        initQuadratic (quadratic);
    }
*passedFileTests = allTests - failedFileTests;
return failedFileTests;
}

void dynamicBufferFileTests (struct equation* quadratic, const char* pathToFile) {
    MYASSERT(quadratic);

    int failedFileTests = 0;
    int passedFileTests = 0;

    initQuadratic (quadratic);

    struct solution fileSolution;
    initFileSolution (&fileSolution);

    FILE* file = fopen(pathToFile, "r");
    if  (file == NULL) {
        printf(RED "Error: the file was not opened! Check the file tests.txt\n" RESET);
        return;
    }

    fseek(file, 0L, SEEK_END);
    long lengthOfFile = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char* fileBuffer = (char*)calloc(lengthOfFile, sizeof(char));
    fread(fileBuffer, sizeof(char), lengthOfFile, file);

    failedFileTests = readFromBufferAndTest(quadratic, &fileSolution, fileBuffer, &passedFileTests);
    free (fileBuffer);
    printf (GREEN "Number of passed file dynamic buffer tests = %d\n" RESET, passedFileTests);
    printf(BLUE "Number of failed file dynamic buffer tests = %d\n\n" RESET, failedFileTests);
    if (fclose(file) != 0)
        printf(RED "Error: the file was not closed! Check the file tests.txt\n" RESET);
}
int readFromBufferAndTest(struct equation* quadratic, struct solution* fileSolution, char* fileBuffer, int* passedFileTests) {
    MYASSERT(quadratic);
    MYASSERT(fileSolution);
    MYASSERT(fileBuffer);

    int failedFileTests = 0;
    int allTests = 0;

    int fileOffset = 0;
    int scannedSymbols = 0;
    int errorSscanf = 0;

    while (1) {
        if (sscanf (fileBuffer+fileOffset, "%lf %n", &(quadratic->arguments.a), &scannedSymbols) != 1)
            errorSscanf = 1;
        fileOffset += scannedSymbols;
        if (sscanf (fileBuffer+fileOffset, "%lf %n" , &(quadratic->arguments.b), &scannedSymbols) != 1)
            errorSscanf = 1;
        fileOffset += scannedSymbols;
        if (sscanf (fileBuffer+fileOffset, "%lf %n", &(quadratic->arguments.c), &scannedSymbols) != 1)
            errorSscanf = 1;
        fileOffset += scannedSymbols;
        if (sscanf (fileBuffer+fileOffset, "%d %n",  (int*) &fileSolution->nAnswers, &scannedSymbols) != 1)
            errorSscanf = 1;
        fileOffset += scannedSymbols;

        switch (fileSolution->nAnswers)
        {
            case oneRoot:
                if (sscanf (fileBuffer+fileOffset, "%lf %n", &fileSolution->firstRoot, &scannedSymbols) != 1)
                    errorSscanf = 1;
                fileOffset += scannedSymbols;
                fileSolution->secondRoot = NAN;
                break;
            case twoRoots:
                if (sscanf (fileBuffer+fileOffset, "%lf %n", &fileSolution->firstRoot, &scannedSymbols) != 1)
                    errorSscanf = 1;
                fileOffset += scannedSymbols;
                if (sscanf (fileBuffer+fileOffset, "%lf %n", &fileSolution->secondRoot, &scannedSymbols) != 1)
                    errorSscanf = 1;
                fileOffset += scannedSymbols;
                break;
            case infinityRoots:
            case noRoots:
            case indefinityRoots:
            default:
                fileSolution->firstRoot = NAN;
                fileSolution->secondRoot = NAN;
                break;
        }

        if (errorSscanf) {
            initQuadratic (quadratic);
            break;
        }
        failedFileTests += oneTest(quadratic, *fileSolution);
        initFileSolution (fileSolution);
        initQuadratic (quadratic);
        allTests++;
    }
    *passedFileTests = allTests - failedFileTests;
    return failedFileTests;
}

