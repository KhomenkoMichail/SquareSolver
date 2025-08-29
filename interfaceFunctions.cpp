#include <TXLib.h>
#include <stdio.h>

#include "colors.h"
#include "myassert.h"
#include "interfaceFunctions.h"
#include "helpingFunctions.h"
#include "structsAndEnum.h"

void introMessage (void) {
    printf (MAGENTA "This program is intended for solving quadratic equations such as:\n" RESET);
    printf (CYAN "ax^2 + bx + c = 0\n" RESET);
}

void announcementOfResults (struct equation quadratic) {
    MYASSERT(isDouble(quadratic.arguments.a));
    MYASSERT(isDouble(quadratic.arguments.b));
    MYASSERT(isDouble(quadratic.arguments.c));

    printf ("Your equation:\n");
    printf ("%lgx^2%+lgx%+lg = 0\n", quadratic.arguments.a, quadratic.arguments.b, quadratic.arguments.c);

    switch (quadratic.roots.nRoots)
    {
        case infinityRoots:
            printf ("This equation has an infinite number of roots.\n");
            break;

        case noRoots:
            printf ("This equation does not have roots.\n");
            break;

        case oneRoot:
            printf ("This equation has one root x = %g\n", quadratic.roots.x1);
            break;

        case twoRoots:
            printf ("This equation has two roots:\n");
            printf ("x1 = %g\n", quadratic.roots.x1);
            printf ("x2 = %g\n", quadratic.roots.x2);
            break;

        case indefinityRoots:
        default:
            printf (RED "Error! Please, try again.\n" RESET);
            break;
    }
}

void requestToContinue (int* flag) {
    MYASSERT (flag);
    int ch = 0;

    printf (GREEN "Enter any character to continue solving the equations " RESET);
    printf (RED "or click [Enter] to end program.\n" RESET);

    if ((ch = getchar()) == '\n')
        *flag = 0;
    else bufferCleaner();
}
