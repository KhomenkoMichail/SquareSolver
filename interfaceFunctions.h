/*!
    \file
    \brief Header for interface functions.
*/

#ifndef INTERFACE_FUNCTIONS
#define INTERFACE_FUNCTIONS

/*!
    \brief Prints an introductory message
    \param Does not accept parameters.
    \return Returns nothing.
*/
void introMessage (void);

/*!
    \brief Announces results of solving quadratic equation.
    \param quadratka - equation structure which results should be announced.
    \return Returns nothing.
*/
void announcementOfResults (struct equation quadratka);

/*!
    \brief Makes request to continue solving quadratic equations.
    \details Finishes solving quadratic equations if [Enter]
    is entered and continues solving equations if any other character is entered.
    \param flag -pointer to the variable responsible for the continuation of the cycle of solving equations.
*/
void requestToContinue (int *flag);
#endif
