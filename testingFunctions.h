/*!
    \file
    \brief Header file for `testingFunctions.h`
*/

#ifndef TESTING_FUNCTIONS
#define TESTING_FUNCTIONS

/*!
    \brief Tests function "solveSquare".
    \details Contains equation structures with arguments and correct solutions to these equations.
    Runs function "solveSquare" and compare answers.
    Outputs erroneous tests and their number.
    \param Does not accept parameters.
    \return Returns nothing.
*/
void testSolveSquare (void);

/*!
    \brief Makes one test of function "solveSquare".
    \param testingArguments - a pointer to equation structure with the specified arguments.
    \param testSolutions - a stricture which contains correct roots of the quadratic equation and their number.
    \return Returns 1 if test was failed, else returns 0.
*/
int oneTest (struct equation* testingArguments, struct solution testSolutions);

/*!
    \brief Tests function "solveSquare".
    \details Reads the arguments of a quadratic equation and its solutions from a .txt file.
    Calls the function "solveSquare" and compares its answers with answers from file.
    Outputs erroneous tests and their number.
    \param quadratic - a pointer to the equation structure which is filled with arguments from the file.
    \return Returns nothing.
*/
void testsFromFile (struct equation* quadratic);

/*!
    \brief Clears the solution structure.
    \details Initializes the solution structure as:
    \code
    .nAnswers = indefinityRoots,
    .firstRoot = NAN,
    .secondRoot = NAN
    \endcode
    \param fileSolution - a pointer to the solution structure, which needs to be initialized.
    \return Returns nothing.
*/
void initFileSolution (struct solution* fileSolution);

/*!
    \brief Reads arguments of the quadratic equation and answers for it from
    the opened txt. file and test function "solveSquare".
    \param quadratic - a pointer to the equation structure which is filled with
    arguments from the file and passed to the function "solveSquare".
    \param fileSolution - a pointer to the solution structure which is filled with
    answers from the file and compares with answers from the function "solveSquare".
    \return Returns a number of failed tests.
*/
int readFromFileAndTest(struct equation* quadratic, struct solution* fileSolution, FILE* file);

/*!
    \brief Reads arguments of a quadratic equation and answers to it from the string.
    Then compares these answers with answers from the function "solveSquare".
    \param quadratic - a pointer to the equation structure, which is filled with
    arguments from the string and passed to the function "solveSquare".
    \param fileSolution - a pointer to the solution structure which is filled with
    answers from the string and compares with answers from the function "solveSquare".
    \param fileBuffer - a pointer to the string, which contains equation arguments and answers.
    \return Returns a number of failed tests.
*/
int readFromBufferAndTest(struct equation* quadratic, struct solution* fileSolution, char* fileBuffer);

/*!
    \brief Tests function "solveSquare".
    \details Opens a file and reads its contents into a string. Then reads arguments
    of a quadratic equation and answers to it from this string.
    Then compares these answers with answers from the function "solveSquare".
    Outputs erroneous tests and their number.
    \param quadratic - a pointer to the equation structure which is filled with
    arguments from the file and passed to the function "solveSquare".
    \return Returns nothing.
*/
void testFromFileByBuffer (struct equation* quadratic);

#endif
