/*!
    \file
    \brief Header for command line functions.
*/

#ifndef COMMAND_LINE_FUNCTIONS_H
#define COMMAND_LINE_FUNCTIONS_H

/*!
    \brief Processes command line arguments and runs the selected program mode
    \param numberOfArguments - number of command line arguments
    \param arguments - array of pointers to command line arguments
    \return Returns continueTheProgram - variable that is responsible for the continuation of the program.
    1 for continue and 0 for end program.
*/
int processingCommandLineArguments (int numberOfArguments, char* arguments[]);

/*!
    \brief Prints the description of the program operating modes.
    \param Does not accept parameters.
    \return Returns 0.
*/
int modeHelp (void);

/*!
    \brief Prints the description of the project.
    \param Does not accept parameters.
    \return Returns 0.
*/
int modeVersion (void);

/*!
    \brief Starts the mode with a one-time solution of the quadratic equation.
    \param Does not accept parameters.
    \return Returns 0.
*/
int modeSingle (void);

/*!
    \brief Starts the mode with testing the function "solveSquare".
    \details Includes dynamicBufferFileTests, scanningFileTestsSolveSquare,
    integratedTestSolveSquare (read testingFunctions documentation).
    \param Does not accept parameters.
    \return Returns 0.
*/
int modeTest (char* pathToFile);

/*!
    \brief Prints a message about an error input in the command line.
    \param Does not accept parameters.
    \return Returns 0.
*/
int errorCommandLineInput (void);

#endif
