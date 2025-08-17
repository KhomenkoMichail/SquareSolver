#include<stdio.h>
#include<TXLib.h>
#include<math.h>
void intro (void);
double get_double (void);
void skip (void);
void solve_square (double a, double b, double c);
int main (void)
{
    double a = 0.0,
    b = 0.0,
    c = 0.0;     //коэффициенты квадратного уравнения
    char ch = '0';
    int KeepSolving = 1;
    while (KeepSolving)
    {
            intro();
            printf("Введите численное значение коэффициента a:");
            a=get_double();
            printf ("Введите численное значение коэффициента b:");
            b=get_double();
            printf ("Введите численное значение коэффициента c:");
            c=get_double();
            printf ("Полученное уравнение:\n");
            printf ("%gx^2+%gx+%g = 0\n", a, b, c);
            solve_square(a, b, c);
            printf ("Введите любой символ, чтобы продолжить решать уравнения ");
            printf("или нажмите [Enter], чтобы завершить программу.\n");
            if ((ch=getchar())=='\n')
                KeepSolving = 0;
            else skip();
    }
    printf ("Программа завершена!\n");
    return 0;
}
void intro (void)
{
    printf ("Эта программа предназначена для решения квадратных уравнений вида:\n");
    printf ("ax^2+bx+c=0\n");
}
void skip (void)  //функция пропуска входных данных
{
    char ch = '0';
    while ((ch=getchar())!='\n')
        continue;
}
double get_double (void)   //функция получения значения типа double
{
    char ch = '0';
    double d = 0.0;
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
    double d = 0.0; //дискриминант квадратного уравнения
    double sq = 0.0;
    if ((a == 0.0)&&(b == 0.0)&&(c ==0.0))
        printf ("x - любое число\n");
    else if ((a == 0.0)&&(b==0.0))         //при с!=0
        printf ("Уравнение не имеет корней.\n");
    else if (a == 0.0)         //при b!=0 и с!=0
        printf ("Уравнение имеет единственный корень x = %.2lf\n", -c/b);
    else   //при a!=0
        {
        d = b*b - 4*a*c;      //вычисление дискриминанта
        if (d<0)
            printf ("Уравнение не имеет корней.\n");
        else if (d==0.0)
            printf ("Уравнение имеет единственный корень x = %.2lf\n", -b/(2*a));
        else   //при d>0
            {
                printf ("Уравнение имеет два различных корня:\n");
                sq = sqrt(d);
                printf("x1=%.2lf\nx2=%.2lf\n", (-b-sq)/(2*a), (-b+sq)/(2*a));
            }
        }
}

