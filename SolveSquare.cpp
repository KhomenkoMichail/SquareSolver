#include<stdio.h>
#include<TXLib.h>
#include<math.h>
void intro (void);
double get_double (void);
void skip (void);
void solve_square (double a, double b, double c);
int main (void)
{
    double a, b, c;     //������������ ����������� ���������
    char ch;
    intro();
    while ((ch=getchar())!='\n')
    {
            skip();
            printf("������� ��������� �������� ������������ a:");
            a=get_double();
            while (a==0.0)
            {
                printf("��� a=0 ��������� �� �������� ����������!\n");
                printf("������� ������ ��������� �������� a:");
                a=get_double();
            }
            printf ("������� ��������� �������� ������������ b:");
            b=get_double();
            printf ("������� ��������� �������� ������������ c:");
            c=get_double();
            printf ("���������� ���������:\n");
            printf ("%.2lfx^2+%.2lfx+%.2lf = 0\n", a, b, c);
            solve_square(a, b, c);
            intro();
    }
    printf ("��������� ���������!\n");
    return 0;
}
void intro (void)
{
    printf ("��� ��������� ������������� ��� ������� ���������� ��������� ����:\n");
    printf ("ax^2+bx+c=0\n");
    printf ("������� ����� ������ ��� ����������� (��� ������ ������ ��� ���������� ����������:\n");
}
void skip (void)  //������� �������� ������� ������
{
    char ch;
    while ((ch=getchar())!='\n')
        continue;
}
double get_double (void)   //������� ��������� �������� ���� double
{
    char ch;
    double d;
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
    double d;
    double sq;
    d = b*b - 4*a*c;
    if (d<0)
        printf ("������ ��������� �� ����� �������!\n");
    else if (d==0.0)
        printf ("��������� ����� ������������ ������ x = %.2lf\n", -b/(2*a));
    else
        {
            printf ("��������� ����� ��� ��������� �����:\n");
            sq = sqrt(d);
            printf("x1=%.2lf\nx2=%.2lf\n", (-b-sq)/(2*a), (-b+sq)/(2*a));
        }
}

