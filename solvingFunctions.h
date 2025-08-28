/*!
    \file
    \brief Header for solving functions.
*/

#ifndef SOLVING_FUNCTIONS
#define SOLVING_FUNCTIONS

/*!
    \brief Solves the quadratic equation.
    \details Accepts an equation structure with the specified arguments and adds answers to it.
    \param quadratka - a pointer to equation structure with specified argument.
    \return Returns nothing.
*/
void solveSquare (struct equation* quadratka);

/*!
    \brief Solves the linear equation.
    \details Solves the linear equation of the form: k*x + b = 0
    \param k - argument k of the linear equation.
    \param b - argument b of the linear equation.
    \return Returns answer of the linear equation.
*/
double solveLinear (double k, double b);

/*!
    \brief Sets the roots in ascending order.
    \details Makes x1 a smaller root and x2 a bigger one.
    \param x1 - the pointer to the first quadratic equation root.
    \param x2 - the pointer to the second quadratic equation root.
    \return Returns nothing.
*/
void rootsInAscendingOrder (double* x1, double* x2);
#endif
