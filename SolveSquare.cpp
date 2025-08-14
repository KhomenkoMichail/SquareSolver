#include<stdio.h>
#include<TXLib.h>
#include<math.h>
void intro (void);
double get_double (void);
void skip (void);
void solve_square (double a, double b, double c);
int main (void)
{
    double a, b, c;     //коэффициенты квадратного уравнения
    char ch;
    intro();
    while ((ch=getchar())!='\n')
    {
            skip();
            printf("Введите численное значение коэффициента a:");
            a=get_double();
            while (a==0.0)
            {
                printf("При a=0 уравнение не является квадратным!\n");
                printf("Введите другое численное значение a:");
                a=get_double();
            }
            printf ("Введите численное значение коэффициента b:");
            b=get_double();
            printf ("Введите численное значение коэффициента c:");
            c=get_double();
            printf ("Полученное уравнение:\n");
            printf ("%.2lfx^2+%.2lfx+%.2lf = 0\n", a, b, c);
            solve_square(a, b, c);
            intro();
    }
    printf ("Программа завершена!\n");
    return 0;
}
void intro (void)
{
    printf ("Эта программа предназначена для решения квадратных уравнений вида:\n");
    printf ("ax^2+bx+c=0\n");
    printf ("Введите любой символ для продолжения (или пустую строку для завершения программмы:\n");
}
void skip (void)  //функция пропуска входных данных
{
    char ch;
    while ((ch=getchar())!='\n')
        continue;
}
double get_double (void)   //функция получения значения типа double
{
    char ch;
    double d;
    while ((scanf ("%lf", &d))!=1)
    {
    while ((ch=getchar())!='\n')
        putchar(ch);
    printf (" не является числом.\nВведите число такое как 3, 52.52, -8\n");
    }
    skip();
    return d;
}
void solve_square (double a, double b, double c)  //функция решения заданного квадратного уравнения
{
    double d;
    double sq;
    d = b*b - 4*a*c;
    if (d<0)
        printf ("Данное уравнение не имеет решений!\n");
    else if (d==0.0)
        printf ("Уравнение имеет единственный корень x = %.2lf\n", -b/(2*a));
    else
        {
            printf ("Уравнение имеет два различных корня:\n");
            sq = sqrt(d);
            printf("x1=%.2lf\nx2=%.2lf\n", (-b-sq)/(2*a), (-b+sq)/(2*a));
        }
}

