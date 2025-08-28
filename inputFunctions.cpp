#include <TXLib.h>
#include <stdio.h>
#include <assert.h>

#include "structsAndEnum.h"
#include "inputFunctions.h"

void getArguments (struct equation* quadratka) {
    assert(quadratka);
    printf("Enter the coefficient  a:");
    quadratka->arguments.a = getDouble();
    printf ("Enter the coefficient  b:");
    quadratka->arguments.b = getDouble();
    printf ("Enter the coefficient  c:");
    quadratka->arguments.c = getDouble();
}
double getDouble (void) { //функция получения значения типа double
    int ch = 0;
    double number = NAN;
    char ch1 = '\0';

        while ((scanf ("%lf%c", &number, &ch1) != 2) || (ch1 != '\n')) {

            putchar(ch1);
            while ((ch = getchar()) != '\n')
                putchar (ch);

            printf (" is not a number.\n"
                    "Enter a number like 3, 52.52, -8\n");
        }

    return number;
}
