#include<stdio.h>
#include<TXLib.h>
#include<math.h>
void introMessage (void);
double getDouble (void);
void skip (void);
void solveSquare (double a, double b, double c);
void getArguments (double * A, double * B, double * C);
void requestToContinue (int * flag);
int main (void) {
    double a = 0.0, b = 0.0, c = 0.0;     //������������ ����������� ���������
    char ch = 0;
    int keepSolving = 1;
    while (keepSolving) {
        introMessage();
        getArguments (&a, &b, &c);
        solveSquare (a, b, c);
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
    char ch = '0';
    while ((ch = getchar()) != '\n')
        continue;
}
double getDouble (void) {   //������� ��������� �������� ���� double
    char ch = '0';
    double d = 0.0;
    while ((scanf ("%lf", &d)) != 1) {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf (" �� �������� ������.\n������� ����� ����� ��� 3, 52.52, -8\n");
    }
    skip();
    return d;
}
void solveSquare (double a, double b, double c) { //������� ������� ��������� ����������� ���������
    printf ("���������� ���������:\n");
    printf ("%gx^2+%gx+%g = 0\n", a, b, c);
    double d = 0.0; //������������ ����������� ���������
    double sq = 0.0;
    if ((a == 0.0)&&(b == 0.0)&&(c ==0.0))
        printf ("x - ����� �����\n");
    else if ((a == 0.0)&&(b == 0.0))         //��� � != 0
        printf ("��������� �� ����� ������.\n");
    else if (a == 0.0)         //��� b != 0 � � != 0
        printf ("��������� ����� ������������ ������ x = %g\n", -c/b);
    else {   //��� a != 0
        d = b * b - 4 * a * c;      //���������� �������������
        if (d < 0)
            printf ("��������� �� ����� ������.\n");
        else if (d == 0.0)
            printf ("��������� ����� ������������ ������ x = %g\n", -b / (2 * a));
        else {   //��� d > 0

                printf ("��������� ����� ��� ��������� �����:\n");
                sq = sqrt(d);
                printf("x1 = %g\nx2 = %g\n", (-b - sq)/(2 * a), (-b + sq)/(2 * a));
        }
    }
}
void getArguments (double * A, double * B, double * C) {
    printf("������� ��������� �������� ������������ a:");
    *A = getDouble();
    printf ("������� ��������� �������� ������������ b:");
    *B = getDouble();
    printf ("������� ��������� �������� ������������ c:");
    *C = getDouble();
}
void requestToContinue (int * flag) {
    char ch = 0;
    printf ("������� ����� ������, ����� ���������� ������ ��������� ");
    printf ("��� ������� [Enter], ����� ��������� ���������.\n");
    if ((ch = getchar()) == '\n')
        *flag = 0;
    else skip();
}
