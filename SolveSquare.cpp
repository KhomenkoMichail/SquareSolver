#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <assert.h>

void introMessage (void);
double getDouble (void);
void bufferCleaner (void);
void solveSquare (struct equation* quadratka);
void testSolveSquare (void);
double solveLinear (double k, double b);
void rootsInAscendingOrder (double* x1, double* x2);
void getArguments (struct equation* quadratka);
void announcementOfResults (struct equation quadratka);
void requestToContinue (int * flag);
int compareDouble (double first, double second);

enum amountOfRoots {
    infinityRoots = -1,
    noRoots = 0,
    oneRoot = 1,
    twoRoots = 2,
    indefinityRoots = 5
};

//InitQuadratka(){
struct structForArg {
            double a;
            double b;
            double c;
};

struct structForRoots {
    double x1;
    double x2;
    enum amountOfRoots nRoots;
};

struct equation {
    struct structForArg arguments;
    struct structForRoots roots;
};

int main (void) {

    struct equation quadratka = {
        .arguments = {
            .a = NAN,
            .b = NAN,
            .c = NAN
        },
        .roots = {
            .x1 = NAN,
            .x2 = NAN,
            .nRoots = indefinityRoots
        }
    };

    testSolveSquare ();

    int keepSolving = 1;
    while (keepSolving) {

        //InitQuadr()

        introMessage();

        getArguments (&quadratka);

        solveSquare (&quadratka);

        announcementOfResults (quadratka);

        requestToContinue (&keepSolving);
    }

    printf ("Программа завершена!\n");
    return 0;
}

//-----------------------------------------------------------------------------

void introMessage (void) {
    printf ("Эта программа предназначена для решения квадратных уравнений вида:\n");
    printf ("ax^2 + bx + c = 0\n");
}

//-----------------------------------------------------------------------------

void bufferCleaner (void) { //функция пропуска входных данных
    int ch = 0;
    while ((ch = getchar()) != '\n')
        continue;
}

//-----------------------------------------------------------------------------

double getDouble (void) { //функция получения значения типа double
    int ch = 0;
    double number = NAN;
    char ch1 = '\0';

        while ((scanf ("%lf%c", &number, &ch1) != 2) || (ch1 != '\n')) {

            putchar(ch1);
            while ((ch = getchar()) != '\n')
                putchar (ch);

            printf (" не является числом.\n"
                    "Введите число такое как 3, 52.52, -8\n");
        }

    return number;
}

//-----------------------------------------------------------------------------

void solveSquare (struct equation* quadratka) { //функция решения заданного квадратного уравнения
    assert (!(isnan(quadratka->arguments.a) || isnan(quadratka->arguments.b) || isnan (quadratka->arguments.c)));
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

//-----------------------------------------------------------------------------

void getArguments (struct equation* quadratka) {
    assert(quadratka);
    printf("Введите численное значение коэффициента a:");
    quadratka->arguments.a = getDouble();
    printf ("Введите численное значение коэффициента b:");
    quadratka->arguments.b = getDouble();
    printf ("Введите численное значение коэффициента c:");
    quadratka->arguments.c = getDouble();
}

//-----------------------------------------------------------------------------

void announcementOfResults (struct equation quadratka) {

    printf ("Полученное уравнение:\n");
    printf ("%lgx^2%+lgx%+lg = 0\n", quadratka.arguments.a, quadratka.arguments.b, quadratka.arguments.c);

    switch (quadratka.roots.nRoots)
    {
        case infinityRoots:
            printf ("Уравнение имеет бесконечное количество корней.\n");
            break;

        case noRoots:
            printf ("Уравнение не имеет корней.\n");
            break;

        case oneRoot:
            printf ("Уравнение имеет единственный корень x = %g\n", quadratka.roots.x1);
            break;

        case twoRoots:
            printf ("Уравнение имеет два корня:\n");
            printf ("x1 = %g\n", quadratka.roots.x1);
            printf ("x2 = %g\n", quadratka.roots.x2);
            break;

        case indefinityRoots:
            printf ("Ошибка! Попробуйте еще раз.\n");
            break;

        default:
            printf ("Ошибка! Попробуйте еще раз.\n");
            break;
    }
}

//-----------------------------------------------------------------------------

void requestToContinue (int *flag) {
    assert (*flag);
    int ch = 0;

    printf ("Введите любой символ, чтобы продолжить решать уравнения ");
    printf ("или нажмите [Enter], чтобы завершить программу.\n");

    if ((ch = getchar()) == '\n')
        *flag = 0;
    else bufferCleaner();
}

//-----------------------------------------------------------------------------

int compareDouble (double first, double second) {
    if (isnan(first) && isnan(second))      //оба nan
        return 1;

    else if (isnan(first) || isnan(second))  //только один nan
        return 0;

    else {
        double fabsOfDifference = NAN;
        fabsOfDifference = fabs(first - second);

        if (fabsOfDifference < 1e-10)
            return 1;
        return 0;
    }
}

//-----------------------------------------------------------------------------
double solveLinear (double k, double b) {
    assert(!(isnan(k) || isnan(b)));
    double x = NAN;
    //k == 0
    x = -b / k;
    return x;
}

//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------

void testSolveSquare (void) {
    const int testNum = 10;       //колличество различных примеров

    int failedTests = 0;

    struct equation testingArguments [testNum] = {      //заданные уравнения
      { {0, 0, 0}, {NAN, NAN, indefinityRoots} },
      { {0, 2, 2}, {NAN, NAN, indefinityRoots} },
      { {0, 0, 2}, {NAN, NAN, indefinityRoots} },
      { {2, 2, 0}, {NAN, NAN, indefinityRoots} },
      { {1, 0, -4},{NAN, NAN, indefinityRoots} },
      { {1, -5, 6},{NAN, NAN, indefinityRoots} },
      { {1, 2, 1}, {NAN, NAN, indefinityRoots} },
      { {0, 2, 0}, {NAN, NAN, indefinityRoots} },
      { {1, 1, 1}, {NAN, NAN, indefinityRoots} },
      { {1, -3, 2},{NAN, NAN, indefinityRoots} }
    };

    struct solution {
        amountOfRoots nAnswers;
        double firstRoot;
        double secondRoot;
    };

    struct solution testSolutions[testNum] = { {infinityRoots, NAN, NAN},   //ответы к заданным уравнениям
                                               {oneRoot, -1, NAN},
                                               {noRoots, NAN, NAN},
                                               {twoRoots, 0, -1},
                                               {twoRoots, -2, 2},
                                               {twoRoots, 2, 3},
                                               {oneRoot, NAN, -1},
                                               {oneRoot, 0, NAN},
                                               {noRoots, NAN, NAN},
                                               {twoRoots, 1, 2} };

    for (int test = 0; test < testNum; test++) {

        solveSquare(&testingArguments[test]);

        if (!(testingArguments[test].roots.nRoots == testSolutions[test].nAnswers &&
              (compareDouble(testingArguments[test].roots.x1, testSolutions[test].firstRoot) || compareDouble(testingArguments[test].roots.x1, testSolutions[test].secondRoot)) &&
              (compareDouble(testingArguments[test].roots.x2, testSolutions[test].secondRoot) || compareDouble(testingArguments[test].roots.x2, testSolutions[test].firstRoot)))) {

            printf ("FAILED: solveSquare(%lg, %lg, %lg) --> nRoots = %d, x1 = %lg, x2 = %lg\n",
                    testingArguments[test].arguments.a, testingArguments[test].arguments.b, testingArguments[test].arguments.c,
                    testingArguments[test].roots.nRoots, testingArguments[test].roots.x1, testingArguments[test].roots.x2);
            printf ("should be nRoots = %d, x1 = %lg, x2 = %lg\n\n",
                    testSolutions[test].nAnswers, testSolutions[test].firstRoot, testSolutions[test].secondRoot);

            failedTests++;
        }
    }
    printf ("Колличество непройденных тестов = %d\n", failedTests);
}
