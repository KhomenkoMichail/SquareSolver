/*!
    \file
    \brief Header for helping functions.
*/

#ifndef HELPING_FUNCTIONS_H
#define HELPING_FUNCTIONS_H

/*!
    \brief Clears input buffer.
    \param Does not accept parameters.
    \return Returns nothing.
*/
void bufferCleaner (void);

/*!
    \brief Compare two doubles.
    \details This function compares two doubles also for NAN and INF values.
    \param first - first comparable number.
    \param second - second comparable number.
    \return Returns 1, if the numbers are equal,
    else returns 0.
*/
int compareDouble (double first, double second);

/*!
    \brief Initializes equation structure.
    \details Initializes equation structure as :
    \code
        .arguments = {
            .a = NAN,
            .b = NAN,
            .c = NAN
        },
        .roots = {
            .x1 = NAN,
            .x2 = NAN,
            .nRoots = indefinityRoots
        }
    \endcode
    \param quadratic - a pointer to a structure for initialization
    \return Returns nothing.
*/
void initQuadratic (struct equation* quadratic);

/*!
    \brief Determines whether a number is double.
    \param x - the number that needs to be checked
    \return Returns 0 if the number is NAN or INF, else returns 1.
*/
int isDouble (double x);

#endif
