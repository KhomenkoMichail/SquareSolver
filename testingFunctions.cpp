#include <TXLib.h>
#include <stdio.h>

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

    printf ("Number of failed program tests  = %d\n", failedTests);
}
int oneTest (struct equation* testingArguments, struct solution testSolutions) {

        solveSquare(testingArguments);

        if (!(testingArguments->roots.nRoots == testSolutions.nAnswers &&
              (compareDouble(testingArguments->roots.x1, testSolutions.firstRoot) || compareDouble(testingArguments->roots.x1, testSolutions.secondRoot)) &&
              (compareDouble(testingArguments->roots.x2, testSolutions.secondRoot) || compareDouble(testingArguments->roots.x2, testSolutions.firstRoot)))) {

            printf ("FAILED: solveSquare(%lg, %lg, %lg) --> nRoots = %d, x1 = %lg, x2 = %lg\n",
                    testingArguments->arguments.a, testingArguments->arguments.b, testingArguments->arguments.c,
                    testingArguments->roots.nRoots, testingArguments->roots.x1, testingArguments->roots.x2);
            printf ("should be nRoots = %d, x1 = %lg, x2 = %lg\n\n",
                    testSolutions.nAnswers, testSolutions.firstRoot, testSolutions.secondRoot);
            return 1;
        }
        return 0;
}

void testsFromFile (struct equation* quadratka) {
    int failedFileTests = 0;
    initQuadratka (quadratka);

    struct solution fileSolution;
    initFileSolution (&fileSolution);

    FILE* file = fopen("tests.txt", "r");

    if (file!= NULL) {
            failedFileTests = readFromFileAndTest(quadratka, &fileSolution, file);
    printf("Number of failed file tests = %d\n", failedFileTests);
    }
    else printf("Error: the file was not opened!\n");
}
void initFileSolution (struct solution* fileSolution) {
    *fileSolution = { .nAnswers = indefinityRoots,
                      .firstRoot = NAN,
                      .secondRoot = NAN };
}
int readFromFileAndTest(struct equation* quadratka, struct solution* fileSolution, FILE* file) {
    int failedFileTests = 0;
    while (fscanf (file, "%lf", &(quadratka->arguments.a)) == 1) {
        fscanf (file, "%lf", &(quadratka->arguments.b));
        fscanf (file, "%lf", &(quadratka->arguments.c));
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
        failedFileTests += oneTest(quadratka, *fileSolution);
        initFileSolution (fileSolution);
        initQuadratka (quadratka);
    }
return failedFileTests;
}
void testFromFileByBuffer (struct equation* quadratka) {
    int failedFileTests = 0;
    initQuadratka (quadratka);

    struct solution fileSolution;
    initFileSolution (&fileSolution);

    FILE* file = fopen("tests.txt", "r");
    if  (file == NULL)
        return;

    fseek(file, 0L, SEEK_END);
    long lengthOfFile = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char* fileBuffer = (char*)calloc(lengthOfFile, sizeof(char)); //calloc
    fread(fileBuffer, sizeof(char), lengthOfFile, file);//read

    failedFileTests = readFromBufferAndTest(quadratka, &fileSolution, fileBuffer);
    printf("Number of failed fileBuffer tests = %d\n", failedFileTests);

}
int readFromBufferAndTest(struct equation* quadratka, struct solution* fileSolution, char* fileBuffer) {
    int failedFileTests = 0;
    int fileOffset = 0;
    int scannedSymbols = 0;
    int errorSscanf = 0;

    while (1) {

        if (sscanf (fileBuffer+fileOffset, "%lf %n", &(quadratka->arguments.a), &scannedSymbols) != 1)
            errorSscanf = 1;
        fileOffset += scannedSymbols;
        if (sscanf (fileBuffer+fileOffset, "%lf %n" , &(quadratka->arguments.b), &scannedSymbols) != 1)
            errorSscanf = 1;
        fileOffset += scannedSymbols;
        if (sscanf (fileBuffer+fileOffset, "%lf %n", &(quadratka->arguments.c), &scannedSymbols) != 1)
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
            initQuadratka (quadratka);
            break;
        }
        failedFileTests += oneTest(quadratka, *fileSolution);
        initFileSolution (fileSolution);
        initQuadratka (quadratka);
    }
    return failedFileTests;
}

