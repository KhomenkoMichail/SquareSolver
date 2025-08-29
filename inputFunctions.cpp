#include <TXLib.h>
#include <stdio.h>


#include "colors.h"
#include "myassert.h"
#include "structsAndEnum.h"
#include "inputFunctions.h"

void getArguments (struct equation* quadratic) {
    MYASSERT(quadratic);

    printf("Enter the coefficient  a:");
    quadratic->arguments.a = getDouble();

    printf ("Enter the coefficient  b:");
    quadratic->arguments.b = getDouble();

    printf ("Enter the coefficient  c:");
    quadratic->arguments.c = getDouble();
}

double getDouble (void) {
    int ch = 0;
    double number = NAN;
    char ch1 = '\0';
    while ((scanf ("%lf%c", &number, &ch1) != 2) || (ch1 != '\n')) {

        putchar(ch1);
        while ((ch = getchar()) != '\n')
            putchar (ch);

        printf (RED " is not a number.\n" RESET
                "Enter a number like 3, 52.52, -8\n");
    }
    return number;
}
