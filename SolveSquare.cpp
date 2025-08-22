#include<stdio.h>
#include<TXLib.h>
#include<math.h>
void introMessage (void);
double getDouble (void);
void skip (void);
int solveSquare (double a, double b, double c,
                 double *x1, double *x2);
void getArguments (double *A, double *B, double *C);
void announcementOfResults (int answers, double x1, double x2);
void requestToContinue (int * flag);
int main (void) {
    double a = 0, b = 0, c = 0;     //коэффициенты квадратного уравнения
    char ch = 0;
    double x1 = 0, x2 = 0;
    int answers = 0; // колличество корней квадратного уравнения
    int keepSolving = 1;
    while (keepSolving) {
        introMessage();
        getArguments (&a, &b, &c);
        answers  = solveSquare (a, b, c, &x1, &x2);
        announcementOfResults (answers, x1, x2);
        requestToContinue (&keepSolving);
    }
    printf ("Программа завершена!\n");
    return 0;
}

// ((0.100000000003 - 0.1) - 0.0 ) = 0.00000000003 < 0.0001
//     E        E        0.000001
// ( ... ,0.0, ...)
// 1e-5 1e-10
// == -> 001000100101
// 000000000000
// ^
// *-1 0*-1  0000000 1000000
// -0
// fabs() <
// 100-105стр прату NAN

void introMessage (void) {
    printf ("Эта программа предназначена для решения квадратных уравнений вида:\n");
    printf ("ax^2 + bx + c = 0\n");
}
void skip (void) { //функция пропуска входных данных
    char ch = '0';
    while ((ch = getchar()) != '\n')
        continue;
}
double getDouble (void) {   //функция получения значения типа double
    char ch = '0';
    double d = 0.0;
    while ((scanf ("%lf", &d)) != 1) {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf (" не является числом.\nВведите число такое как 3, 52.52, -8\n");
    }
    skip();
    return d;
}
int solveSquare (double a, double b, double c, double *x1, double *x2) { //функция решения заданного квадратного уравнения
    printf ("Полученное уравнение:\n");
    printf ("%gx^2+%gx+%g = 0\n", a, b, c);
    double d = 0.0; //дискриминант квадратного уравнения
    double sqrt_d = 0.0;
    if ((a == 0.0)&&(b == 0.0)&&(c ==0.0))
        return -1; //бесконечное количество корней уравнения
    else if ((a == 0.0)&&(b == 0.0))         //при с != 0
        return 0; //уравнение не имеет корней
    else if (a == 0.0){         //при b != 0 и с != 0
        *x1 = -c/b;
        return 1; // уравнение имеет единственный корень
        }
    else {   //при a != 0
        d = b * b - 4 * a * c;      //вычисление дискриминанта
        if (d < 0)
            return 0;
        else if (d == 0) {
            *x1 = -b/(2*a);
            return 1;
            }
        else {   //при d > 0
            sqrt_d = sqrt(d);
            *x1 = (-b - sqrt_d) / (2*a);
            *x2 = (-b + sqrt_d) / (2*a);
            return 2;
        }
    }

}

// Check assert NAN
void getArguments (double *A, double *B, double *C) {
    printf("Введите численное значение коэффициента a:");
    *A = getDouble();
    printf ("Введите численное значение коэффициента b:");
    *B = getDouble();
    printf ("Введите численное значение коэффициента c:");
    *C = getDouble();
}
void announcementOfResults (int answers, double x1, double x2){
    switch (answers)
    {
    case -1:
    printf ("Уравнение имеет бесконечное количество корней.\n");
    break;
    case 0:
    printf ("Уравнение не имеет корней.\n");
    break;
    case 1:
    printf ("Уравнение имеет единственный корень x = %g\n", x1);
    break;
    case 2:
    printf ("Уравнение имеет два корня:\n");
    printf ("x1 = %g\n", x1);
    printf ("x2 = %g\n", x2);
    break;
    default:
    printf ("Ошибка! Попробуйте еще раз.\n");
    break;
    }
}
void requestToContinue (int *flag) {
    char ch = 0;
    printf ("Введите любой символ, чтобы продолжить решать уравнения ");
    printf ("или нажмите [Enter], чтобы завершить программу.\n");
    if ((ch = getchar()) == '\n')
        *flag = 0;
    else skip();
}
