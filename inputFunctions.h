/*!
    \file
    \brief Header for input functions.
*/

#ifndef INPUT_FUNCTIONS_H
#define INPUT_FUNCTIONS_H

/*!
    \brief Gets arguments for quadratic equation.
    \details Makes request for getting arguments a, b and c and gets them.
    \param quadrarka - a pointer to a structure for initialization.
    \return Return nothing.
*/
void getArguments (struct equation* quadratka);

/*!
    \brief Gets double data.
    \details Gets one double number from string. Makes a request to try again if it encounters extra characters.
    \param Does not accept parameters.
    \return Returns one double number.
*/
double getDouble (void);

#endif
