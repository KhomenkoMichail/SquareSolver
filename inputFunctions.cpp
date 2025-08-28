#include <TXLib.h>
#include <stdio.h>
#include <assert.h>

#include "colors.h"
#include "structsAndEnum.h"
#include "inputFunctions.h"

void getArguments (struct equation* quadratic) {
    assert(quadratic);

    printf("Enter the coefficient  a:");
    quadratic->arguments.a = getDouble();

    printf ("Enter the coefficient  b:");
    quadratic->arguments.b = getDouble();

    printf ("Enter the coefficient  c:");
    quadratic->arguments.c = getDouble();
}

double getDouble (void) { //функция получения значения типа double
    int ch = 0;
    double number = NAN;
    char ch1 = '\0';
    while ((scanf ("%lf%c", &number, &ch1) != 2) || (ch1 != '\n')) {

        putchar(ch1);
        while ((ch = getchar()) != '\n')
            putchar (ch);

        printf (" %sis not a number.%s\n"
                "Enter a number like 3, 52.52, -8\n", RED, RESET);
    }
    return number;
}
