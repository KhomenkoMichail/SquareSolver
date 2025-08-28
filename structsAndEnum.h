/*!
    \file
    \brief Header for structs and enum.
*/

#ifndef STRUCTS_AND_ENUM
#define STRUCTS_AND_ENUM

/*!
    \enum amountOfRoots
    \brief all possible numbers of roots of a quadratic equation.
    \code
    infinityRoots = -1,
    noRoots = 0,
    oneRoot = 1,
    twoRoots = 2,
    indefinityRoots = 5
    \endcode
*/
enum amountOfRoots {
    infinityRoots = -1,
    noRoots = 0,
    oneRoot = 1,
    twoRoots = 2,
    indefinityRoots = 5
};

/*!
    \struct structForArg
    \brief Contains argumenta a, b and c of a quadratic equation.
    \code
    double a;
    double b;
    double c;
    \endcode
*/
struct structForArg {
            double a;
            double b;
            double c;
};

/*!
    \struct structForRoots
    \brief Contains answers of quadratic equation and their number.
    \code
    double x1;
    double x2;
    enum amountOfRoots nRoots;
    \endcode
*/
struct structForRoots {
    double x1;
    double x2;
    enum amountOfRoots nRoots;
};

/*!
    \struct equation
    \brief Contains structure with arguments of quadratic equation and structure with answers for it.
    \code
    struct structForArg arguments;
    struct structForRoots roots;
    \endcode
*/
struct equation {
    struct structForArg arguments;
    struct structForRoots roots;
};

/*!
    \struct solution
    \brief Contains correct answers of quadratic equation and their number. .
    \code
    struct structForArg arguments;
    struct structForRoots roots;
    \endcode
*/
struct solution {
        amountOfRoots nAnswers;
        double firstRoot;
        double secondRoot;
    };
#endif
