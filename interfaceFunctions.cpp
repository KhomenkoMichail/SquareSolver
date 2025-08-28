#include <TXLib.h>
#include <stdio.h>
#include <assert.h>


#include "interfaceFunctions.h"
#include "helpingFunctions.h"
#include "structsAndEnum.h"

void introMessage (void) {
    printf ("This program is intended for solving quadratic equations such as:\n");
    printf ("ax^2 + bx + c = 0\n");
}
void announcementOfResults (struct equation quadratka) {

    printf ("Your equation:\n");
    printf ("%lgx^2%+lgx%+lg = 0\n", quadratka.arguments.a, quadratka.arguments.b, quadratka.arguments.c);

    switch (quadratka.roots.nRoots)
    {
        case infinityRoots:
            printf ("This equation has an infinite number of roots.\n");
            break;

        case noRoots:
            printf ("This equation does not have roots.\n");
            break;

        case oneRoot:
            printf ("This equation has one root x = %g\n", quadratka.roots.x1);
            break;

        case twoRoots:
            printf ("This equation has two roots:\n");
            printf ("x1 = %g\n", quadratka.roots.x1);
            printf ("x2 = %g\n", quadratka.roots.x2);
            break;

        case indefinityRoots:
            printf ("Error! Please, try again.\n");
            break;

        default:
            printf ("Error! Please, try again.\n");
            break;
    }
}
void requestToContinue (int *flag) {
    assert (*flag);
    int ch = 0;

    printf ("Enter any character to continue solving the equations ");
    printf ("or click [Enter] to end program.\n");

    if ((ch = getchar()) == '\n')
        *flag = 0;
    else bufferCleaner();
}
