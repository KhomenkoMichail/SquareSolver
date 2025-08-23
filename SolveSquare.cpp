#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <assert.h>

void introMessage (void);
double getDouble (void);
void bufferCleaner (void);
int solveSquare (struct structForArg arguments, struct structForRoots rootsPointers);
int testSolveSquare (int* flagToContinue);
double solveLinear (double k, double b);
void rootsInAscendingOrder (double* x1, double* x2);
void getArguments (struct structForArg* pStructArg);
void announcementOfResults (int answers, double x1, double x2);
void requestToContinue (int * flag);
int compareDouble (double first, double second);

// Struct Quadratka {
//   struct structForArg ; //24�
//    structForRoots ; //24�
//}

//InitQuadratka(){



struct structForArg{
            double a;
            double b;
            double c;
        };

struct structForRoots {
    double px1;
    double px2;
    int nRoots;//TODO:
};

enum amountOfRoots {
    infinityRoots = -1,
    noRoots = 0,
    oneRoot = 1,
    twoRoots = 2,
    indefinityRoots = 5

    //TODO:
}

const int infinityRoots = -1;
const int indefinityRoots = 5;


int main (void) {
    double x1 = NAN, x2 = NAN;

    struct structForArg arguments = {
        .a = NAN,
        .b = NAN,
        .c = NAN
    };

    struct structForRoots rootsPointers = {
        &x1,
        &x2,
        nRoots =
    };
    //

    int keepSolving = 1;
    //testSolveSquare (&keepSolving);
    while (keepSolving) {

        int nRoots = indefinityRoots; // ����������� ������ ����������� ���������

        introMessage();
        getArguments (&arguments);

        nRoots = solveSquare (arguments, rootsPointers);

        announcementOfResults (nRoots, x1, x2);
        requestToContinue (&keepSolving);
    }

    printf ("��������� ���������!\n");
    return 0;
}

//-----------------------------------------------------------------------------

void introMessage (void) {
    printf ("��� ��������� ������������� ��� ������� ���������� ��������� ����:\n");
    printf ("ax^2 + bx + c = 0\n");
}

//-----------------------------------------------------------------------------

void bufferCleaner (void) { //������� �������� ������� ������
    int ch = 0;
    while ((ch = getchar()) != '\n')
        continue;
}

//-----------------------------------------------------------------------------

double getDouble (void) { //������� ��������� �������� ���� double
    int ch = 0;
    double number = NAN;
    char ch1 = '\0';

        while ((scanf ("%lf%c", &number, &ch1) != 2) || (ch1 != '\n')) {

            putchar(ch1);
            while ((ch = getchar()) != '\n')
                putchar (ch);

            printf (" �� �������� ������.\n"
                    "������� ����� ����� ��� 3, 52.52, -8\n");
        }

    return number;
}

//-----------------------------------------------------------------------------

int solveSquare (struct structForArg arguments, struct structForRoots rootsPointers) { //������� ������� ��������� ����������� ���������
    assert (!(isnan(arguments.a) || isnan(arguments.b) || isnan (arguments.c)));
    assert ((rootsPointers.px1) && (rootsPointers.px2));



    *rootsPointers.px1 = NAN;
    *rootsPointers.px2 = NAN;

    printf ("���������� ���������:\n");
    printf ("%gx^2+%gx+%g = 0\n", arguments.a, arguments.b, arguments.c);

    double d = NAN; //������������ ����������� ���������
    double sqrtD = NAN;

    if (compareDouble(arguments.a, 0)) {
        if (compareDouble(arguments.b, 0)) {
            if (compareDouble(arguments.c, 0))
                return infinityRoots;
            else return 0;
        }
        else {
            *rootsPointers.px1 = solveLinear(arguments.b, arguments.c);
            return 1;
        }
    }
    else {
        if (compareDouble(arguments.c, 0)) {      // ��� � == 0
            if (compareDouble(arguments.b, 0)) {
                *rootsPointers.px1 = 0;
                return 1;
            }
            else {
                *rootsPointers.px1 = 0;
                *rootsPointers.px2 = solveLinear(arguments.a, arguments.b);
                rootsInAscendingOrder (rootsPointers.px1, rootsPointers.px2);
                return 2;
            }
        }

        else {                    // ��� � != 0 � � != 0
            d = arguments.b * arguments.b - 4 * arguments.a * arguments.c;      //���������� �������������

            if (d < 0)
                return 0;

            else if (compareDouble(d, 0)) {    //���  d == 0
                *rootsPointers.px1 = -arguments.b/(2*arguments.a);
                return 1;
                }

            else {   //��� d > 0
                sqrtD = sqrt(d);
                *rootsPointers.px1 = (-arguments.b - sqrtD) / (2*arguments.a);
                *rootsPointers.px2 = (-arguments.b + sqrtD) / (2*arguments.a);
                rootsInAscendingOrder (rootsPointers.px1, rootsPointers.px2);
                return 2;
            }
        }
    }
    if (compareDouble(*rootsPointers.px1, 0))
        *rootsPointers.px1 = fabs(*rootsPointers.px1);

    if (compareDouble(*rootsPointers.px2, 0))
        *rootsPointers.px2 = fabs(*rootsPointers.px2);
}

//-----------------------------------------------------------------------------

void getArguments (struct structForArg* pStructArg) {
    assert(pStructArg);
    printf("������� ��������� �������� ������������ a:");
    pStructArg->a = getDouble();
    printf ("������� ��������� �������� ������������ b:");
    pStructArg->b = getDouble();
    printf ("������� ��������� �������� ������������ c:");
    pStructArg->c = getDouble();
}

//-----------------------------------------------------------------------------

void announcementOfResults (int nRoots, double x1, double x2) {
    switch (nRoots)
    {
        case infinityRoots:
            printf ("��������� ����� ����������� ���������� ������.\n");
            break;

        case 0:
            printf ("��������� �� ����� ������.\n");
            break;

        case 1:
            printf ("��������� ����� ������������ ������ x = %g\n", x1);
            break;

        case 2:
            printf ("��������� ����� ��� �����:\n");
            printf ("x1 = %g\n", x1);
            printf ("x2 = %g\n", x2);
            break;

        default:
            printf ("������! ���������� ��� ���.\n");
            break;
    }
}

//-----------------------------------------------------------------------------

void requestToContinue (int *flag) {
    assert (*flag);
    int ch = 0;

    printf ("������� ����� ������, ����� ���������� ������ ��������� ");
    printf ("��� ������� [Enter], ����� ��������� ���������.\n");

    if ((ch = getchar()) == '\n')
        *flag = 0;
    else bufferCleaner();
}

//-----------------------------------------------------------------------------

int compareDouble (double first, double second) {
    if (isnan(first) && isnan(second))      //��� nan
        return 1;

    else if (isnan(first) || isnan(second))  //������ ���� nan
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

int testSolveSquare (int* flag) {
    assert (flag);
    const int argumentsNum = 3;   //����������� ���������� ����������� ��-�
    const int testNum = 10;       //����������� ��������� ��������

    double x1 = NAN, x2 = NAN;
    int nRoots = 0;

    double arg[testNum][argumentsNum] = { {0, 0, 0},
                                          {0, 2, 2},
                                          {0, 0, 2},
                                          {2, 2, 0},
                                          {1, 0, -4},
                                          {1, -5, 6},
                                          {1, 2, 1},
                                          {0, 2, 0},
                                          {1, 1, 1},
                                          {1, -3, 2} };
    struct solution {
        int nAnswers;
        double firstRoot;
        double secondRoot;
    };

    struct solution testSolutions[testNum] = { {-1, NAN, NAN},   //������ � �������� ����������
                                               {1, -1, NAN},
                                               {0, NAN, NAN},
                                               {2, -1, 0},
                                               {2, -2, 2},
                                               {2, 2, 3},
                                               {1, -1, NAN},
                                               {1, 0, NAN},
                                               {0, NAN, NAN},
                                               {2, 1, 2} };

    for (int test = 0; test < testNum; test++) {

//        nRoots = solveSquare(arg[test][0], arg[test][1], arg[test][2], &x1, &x2);

        if (!(nRoots == testSolutions[test].nAnswers &&
              compareDouble(x1, testSolutions[test].firstRoot) &&
              compareDouble(x2, testSolutions[test].secondRoot))) {

            printf ("FAILED: solveSquare(%lg, %lg, %lg) --> nRoots = %d, x1 = %lg, x2 = %lg\n",
                    arg[test][0], arg[test][1], arg[test][2],
                    nRoots, x1, x2);
            printf ("should be nRoots = %d, x1 = %lg, x2 = %lg\n\n",
                    testSolutions[test].nAnswers, testSolutions[test].firstRoot, testSolutions[test].secondRoot);

            *flag = 0;
        }

        else printf ("������ �����!\n\n");
    }
return 0;
}
