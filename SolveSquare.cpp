#include<stdio.h>
#include<TXLib.h>
#include<math.h>
#include<assert.h>
void introMessage (void);
double getDouble (void);
void skip (void);
int solveSquare (double a, double b, double c,
                 double *x1, double *x2);
void getArguments (double *A, double *B, double *C);
void announcementOfResults (int answers, double x1, double x2);
void requestToContinue (int * flag);
int compareDouble (double first, double second);
int main (void) {
    double a = NAN, b = NAN, c = NAN;     //������������ ����������� ���������
    double x1 = NAN, x2 = NAN;
    int answers = NAN; // ����������� ������ ����������� ���������
    int keepSolving = 1;
    while (keepSolving) {
        introMessage();
        getArguments (&a, &b, &c);
        answers  = solveSquare (a, b, c, &x1, &x2);
        announcementOfResults (answers, x1, x2);
        requestToContinue (&keepSolving);
    }
    printf ("��������� ���������!\n");
    return 0;
}
void introMessage (void) {
    printf ("��� ��������� ������������� ��� ������� ���������� ��������� ����:\n");
    printf ("ax^2 + bx + c = 0\n");
}
void skip (void) { //������� �������� ������� ������
    char ch = 0;
    while ((ch = getchar()) != '\n')
        continue;
}
double getDouble (void) {   //������� ��������� �������� ���� double
    char ch = 0;
    double d = NAN;
    while ((scanf ("%lf", &d)) != 1) {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf (" �� �������� ������.\n������� ����� ����� ��� 3, 52.52, -8\n");
    }
    skip();
    return d;
}
int solveSquare (double a, double b, double c, double *x1, double *x2) { //������� ������� ��������� ����������� ���������
    assert(!((isnan(a)) || (isnan(b)) || (isnan(c))));
    assert((*x1 != NULL) && (*x2 != NULL));
    printf ("���������� ���������:\n");
    printf ("%gx^2+%gx+%g = 0\n", a, b, c);
    double d = NAN; //������������ ����������� ���������
    double sqrtD = NAN;
    if ((compareDouble(a, 0))&&(compareDouble(b, 0))&&(compareDouble(c, 0)))
        return -1; //����������� ���������� ������ ���������
    else if ((compareDouble(a, 0))&&(compareDouble(b, 0)))         //��� � != 0
        return 0; //��������� �� ����� ������
    else if (compareDouble(a, 0)){         //��� b != 0 � � != 0
        *x1 = -c/b;
        return 1; // ��������� ����� ������������ ������
        }
    else {   //��� a != 0
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
            return 2;
        }
    }

}
void getArguments (double *A, double *B, double *C) {
    assert((*A != NULL) && (*B != NULL) && (*C != NULL));
    printf("������� ��������� �������� ������������ a:");
    *A = getDouble();
    printf ("������� ��������� �������� ������������ b:");
    *B = getDouble();
    printf ("������� ��������� �������� ������������ c:");
    *C = getDouble();
}
void announcementOfResults (int answers, double x1, double x2) {
    if (compareDouble(x1, 0))
        x1 = fabs(x1);         //���������� x1 = -0
    if (compareDouble(x2, 0))
        x2 = fabs(x2);         //���������� x2 = -0
    switch (answers)
    {
    case -1:
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
void requestToContinue (int *flag) {
    assert (*flag != NULL);
    char ch = 0;
    printf ("������� ����� ������, ����� ���������� ������ ��������� ");
    printf ("��� ������� [Enter], ����� ��������� ���������.\n");
    if ((ch = getchar()) == '\n')
        *flag = 0;
    else skip();
}
int compareDouble (double first, double second) {
    double fabsOfDifference = NAN;
    fabsOfDifference = fabs(first - second);
    if (fabsOfDifference < 1e-10)
        return 1;
    return 0;
}

