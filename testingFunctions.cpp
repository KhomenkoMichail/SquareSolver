#include <TXLib.h>
#include <stdio.h>
#include <assert.h>

#include "colors.h"
#include "testingFunctions.h"
#include "helpingFunctions.h"
#include "structsAndEnum.h"
#include "solvingFunctions.h"

void testSolveSquare (void) {
    int failedTests = 0;

    struct equation testingArguments [] = {      //заданные уравнения
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

    struct solution testSolutions[] = { { infinityRoots, NAN, NAN },   //ответы к заданным уравнениям
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

    printf ("%sNumber of failed program tests  = %d%s\n\n", BLUE, failedTests, RESET);
}

int oneTest (struct equation* testingArguments, struct solution testSolutions) {
        assert(testingArguments);

        solveSquare(testingArguments);

        if (!(testingArguments->roots.nRoots == testSolutions.nAnswers &&
              (compareDouble(testingArguments->roots.x1, testSolutions.firstRoot) || compareDouble(testingArguments->roots.x1, testSolutions.secondRoot)) &&
              (compareDouble(testingArguments->roots.x2, testSolutions.secondRoot) || compareDouble(testingArguments->roots.x2, testSolutions.firstRoot)))) {
            printf ("%sFAILED: solveSquare(%lg, %lg, %lg) --> nRoots = %d, x1 = %lg, x2 = %lg\n", RED,
                    testingArguments->arguments.a, testingArguments->arguments.b, testingArguments->arguments.c,
                    testingArguments->roots.nRoots, testingArguments->roots.x1, testingArguments->roots.x2);
            printf ("should be nRoots = %d, x1 = %lg, x2 = %lg\n\n%s",
                    testSolutions.nAnswers, testSolutions.firstRoot, testSolutions.secondRoot, RESET);
            return 1;
        }
        return 0;
}

void testsFromFile (struct equation* quadratic) {
    assert(quadratic);

    int failedFileTests = 0;

    initQuadratic (quadratic);

    struct solution fileSolution;
    initFileSolution (&fileSolution);

    FILE* file = fopen("tests.txt", "rb");
    if (file!= NULL) {
        failedFileTests = readFromFileAndTest(quadratic, &fileSolution, file);
        printf("%sNumber of failed file tests = %d\n%s", BLUE, failedFileTests, RESET);
        if (fclose(file) != 0)
            printf("%sError: the file was not closed! Check the file tests.txt\n%s", RED, RESET);
    }
    else printf("%sError: the file was not opened! Check the file tests.txt\n%s", RED, RESET);
}

void initFileSolution (struct solution* fileSolution) {
    assert(fileSolution);

    *fileSolution = { .nAnswers = indefinityRoots,
                      .firstRoot = NAN,
                      .secondRoot = NAN };
}

int readFromFileAndTest(struct equation* quadratic, struct solution* fileSolution, FILE* file) {
    assert(quadratic);
    assert(fileSolution);
    assert(file);

    int failedFileTests = 0;
    while (fscanf (file, "%lf", &(quadratic->arguments.a)) == 1) {
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
return failedFileTests;
}
void testFromFileByBuffer (struct equation* quadratic) {
    assert(quadratic);

    int failedFileTests = 0;
    initQuadratic (quadratic);

    struct solution fileSolution;
    initFileSolution (&fileSolution);

    FILE* file = fopen("tests.txt", "r");
    if  (file == NULL) {
        printf("%sError: the file was not opened! Check the file tests.txt\n%s", RED, RESET);
        return;
    }

    fseek(file, 0L, SEEK_END);
    long lengthOfFile = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char* fileBuffer = (char*)calloc(lengthOfFile, sizeof(char));
    fread(fileBuffer, sizeof(char), lengthOfFile, file);

    failedFileTests = readFromBufferAndTest(quadratic, &fileSolution, fileBuffer);
    free (fileBuffer);
    printf("%sNumber of failed fileBuffer tests = %d\n%s", BLUE, failedFileTests, RESET);
    if (fclose(file) != 0)
        printf("%sError: the file was not closed! Check the file tests.txt\n%s", RED, RESET);
}
int readFromBufferAndTest(struct equation* quadratic, struct solution* fileSolution, char* fileBuffer) {
    assert(quadratic);
    assert(fileSolution);
    assert(fileBuffer);

    int failedFileTests = 0;
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
    }
    return failedFileTests;
}

