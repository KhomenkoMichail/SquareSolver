/*!
    \file
    \brief Header for command line functions.
*/

#ifndef COMMAND_LINE_FUNCTIONS_H
#define COMMAND_LINE_FUNCTIONS_H

int processingCommandLineArguments (int numberOfArguments, char* arguments[]);

int modeHelp (void);

int modeVersion (void);

int modeSingle (void);

int modeTest (char* pathToFile);

int errorInput (void);

#endif
