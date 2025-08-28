#include <TXLib.h>
#include <stdio.h>
#include <assert.h>

#include "colors.h"
#include "interfaceFunctions.h"
#include "helpingFunctions.h"
#include "structsAndEnum.h"

void introMessage (void) {
    printf ("%sThis program is intended for solving quadratic equations such as:%s\n", MAGENTA, RESET);
    printf (CYAN "ax^2 + bx + c = 0\n");
}

void announcementOfResults (struct equation quadratic) {
    assert(isDouble(quadratic.arguments.a));
    assert(isDouble(quadratic.arguments.b));
    assert(isDouble(quadratic.arguments.c));

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
            printf ("%sError! Please, try again.\n%s", RED, RESET);
            break;
    }
}

void requestToContinue (int* flag) {
    assert (flag);
    int ch = 0;

    printf ("Enter %sany character%s to continue solving the equations ", GREEN, RESET);
    printf ("or click %s[Enter]%s to end program.\n", RED, RESET);

    if ((ch = getchar()) == '\n')
        *flag = 0;
    else bufferCleaner();
}
