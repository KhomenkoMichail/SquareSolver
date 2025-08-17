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
    c = 0.0;     //������������ ����������� ���������
    char ch = '0';
    int KeepSolving = 1;
    while (KeepSolving)
    {
            intro();
            printf("������� ��������� �������� ������������ a:");
            a=get_double();
            printf ("������� ��������� �������� ������������ b:");
            b=get_double();
            printf ("������� ��������� �������� ������������ c:");
            c=get_double();
            printf ("���������� ���������:\n");
            printf ("%gx^2+%gx+%g = 0\n", a, b, c);
            solve_square(a, b, c);
            printf ("������� ����� ������, ����� ���������� ������ ��������� ");
            printf("��� ������� [Enter], ����� ��������� ���������.\n");
            if ((ch=getchar())=='\n')
                KeepSolving = 0;
            else skip();
    }
    printf ("��������� ���������!\n");
    return 0;
}
void intro (void)
{
    printf ("��� ��������� ������������� ��� ������� ���������� ��������� ����:\n");
    printf ("ax^2+bx+c=0\n");
}
void skip (void)  //������� �������� ������� ������
{
    char ch = '0';
    while ((ch=getchar())!='\n')
        continue;
}
double get_double (void)   //������� ��������� �������� ���� double
{
    char ch = '0';
    double d = 0.0;
    while ((scanf ("%lf", &d))!=1)
    {
    while ((ch=getchar())!='\n')
        putchar(ch);
    printf (" �� �������� ������.\n������� ����� ����� ��� 3, 52.52, -8\n");
    }
    skip();
    return d;
}
void solve_square (double a, double b, double c)  //������� ������� ��������� ����������� ���������
{
    double d = 0.0; //������������ ����������� ���������
    double sq = 0.0;
    if ((a == 0.0)&&(b == 0.0)&&(c ==0.0))
        printf ("x - ����� �����\n");
    else if ((a == 0.0)&&(b==0.0))         //��� �!=0
        printf ("��������� �� ����� ������.\n");
    else if (a == 0.0)         //��� b!=0 � �!=0
        printf ("��������� ����� ������������ ������ x = %.2lf\n", -c/b);
    else   //��� a!=0
        {
        d = b*b - 4*a*c;      //���������� �������������
        if (d<0)
            printf ("��������� �� ����� ������.\n");
        else if (d==0.0)
            printf ("��������� ����� ������������ ������ x = %.2lf\n", -b/(2*a));
        else   //��� d>0
            {
                printf ("��������� ����� ��� ��������� �����:\n");
                sq = sqrt(d);
                printf("x1=%.2lf\nx2=%.2lf\n", (-b-sq)/(2*a), (-b+sq)/(2*a));
            }
        }
}

