#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <assert.h>

void introMessage (void);
double getDouble (void);
void bufferCleaner (void);
int solveSquare (double a, double b, double c,
                 double *x1, double *x2);
int testSolveSquare (int* flagToContinue);
int solveLinear (double k, double b);
void rootsInAscendingOrder (double* x1, double* x2);
void getArguments (double *A, double *B, double *C);
void announcementOfResults (int answers, double x1, double x2);
void requestToContinue (int * flag);
int compareDouble (double first, double second);

const int infinityRoots = -1;

int main (void) {
    double a = NAN, b = NAN, c = NAN;     //������������ ����������� ���������
    double x1 = NAN, x2 = NAN;
    int nRoots = NAN; // ����������� ������ ����������� ���������
    int keepSolving = 1;
    testSolveSquare (&keepSolving);
    while (keepSolving) {
        introMessage();
        getArguments (&a, &b, &c);

        nRoots = solveSquare (a, b, c, &x1, &x2);

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
    char ch = 0;
    while ((ch = getchar()) != '\n')
        continue;
}

//-----------------------------------------------------------------------------

double getDouble (void) { //������� ��������� �������� ���� double
    char ch = 0;
    double number = NAN;
    int ch1 = 0;

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

int solveSquare (double a, double b, double c, double *x1, double *x2) { //������� ������� ��������� ����������� ���������
    *x1 = NAN;
    *x2 = NAN;

    printf ("���������� ���������:\n");
    printf ("%gx^2+%gx+%g = 0\n", a, b, c);

    double d = NAN; //������������ ����������� ���������
    double sqrtD = NAN;

    if ((compareDouble (a, 0)) && (compareDouble (b, 0)) && (compareDouble (c, 0)))
        return infinityRoots; //����������� ���������� ������ ���������

    else if ((compareDouble(a, 0))&&(compareDouble(b, 0)))         //��� � != 0
        return 0; //��������� �� ����� ������

    else if (compareDouble(a, 0)){         //��� b != 0 � � != 0
        *x1 = solveLinear(b, c);
        return 1; // ��������� ����� ������������ ������
        }


    else {   //��� a != 0

        if (compareDouble(c, 0)) {      // ��� � == 0
            *x1 = 0;
            *x2 = solveLinear(a, b);
            rootsInAscendingOrder (x1, x2);
            return 2;
            }

        else {                    // ��� � != 0 � � != 0
            d = b * b - 4 * a * c;      //���������� �������������

            if (d < 0)
                return 0;

            else if (compareDouble(d, 0)) {    //���  d == 0
                *x1 = -b/(2*a);
                return 1;
                }

            else {   //��� d > 0
                sqrtD = sqrt(d);
                *x1 = (-b - sqrtD) / (2*a);
                *x2 = (-b + sqrtD) / (2*a);
                rootsInAscendingOrder (x1, x2);
                return 2;
            }

        }

    }

}

//-----------------------------------------------------------------------------

void getArguments (double *A, double *B, double *C) {
    assert((*A != NULL) && (*B != NULL) && (*C != NULL));
    printf("������� ��������� �������� ������������ a:");
    *A = getDouble();
    printf ("������� ��������� �������� ������������ b:");
    *B = getDouble();
    printf ("������� ��������� �������� ������������ c:");
    *C = getDouble();
}

//-----------------------------------------------------------------------------

void announcementOfResults (int nRoots, double x1, double x2) {
    if (compareDouble(x1, 0))
        x1 = fabs(x1);         //���������� x1 = -0

    if (compareDouble(x2, 0))
        x2 = fabs(x2);         //���������� x2 = -0

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
    assert (*flag != NULL);
    char ch = 0;

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
int solveLinear (double k, double b) {
    double x = NAN;

    x = -b / k;
    return x;
}

//-----------------------------------------------------------------------------
void rootsInAscendingOrder (double* x1, double* x2) {
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
    const int argumentsNum = 3;
    const int testNum = 3;

    double x1 = NAN, x2 = NAN;
    int nRoots = 0;

    double arg[testNum][argumentsNum] = { {0, 0, 0},
                                          {0, 2, 2},
                                          {0, 0, 2} };
    struct solution {
        int nAnswers;
        double firstRoot;
        double secondRoot;
    };

    struct solution testSolutions[testNum] = { {-1, NAN, NAN},
                                               {1, -1, NAN},
                                               {0, NAN, NAN}};

    for (int test = 0; test < testNum; test++) {

        nRoots = solveSquare(arg[test][0], arg[test][1], arg[test][2], &x1, &x2);

        if (!(nRoots == testSolutions[test].nAnswers &&
              compareDouble(x1, testSolutions[test].firstRoot) &&
              compareDouble(x2, testSolutions[test].secondRoot))) {
            printf ("FAILED: solveSquare(%lg, %lg, %lg) --> nRoots = %d, x1 = %lg, x2 = %lg\n",
                    arg[test][0], arg[test][1], arg[test][2],
                    nRoots, x1, x2);
            printf ("should be nRoots = %d, x1 = %lg, x2 = %lg\n",
                    testSolutions[test].nAnswers, testSolutions[test].firstRoot, testSolutions[test].secondRoot);
            *flag = 0;
        }

        else printf ("������ �����!\n");
    }
return 0;
}
