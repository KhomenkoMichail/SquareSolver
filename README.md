# SolveSquare

## Table of contents
1. [About project](about-project)
2. [Possibilities](possibilities)
3. [How to use](how-to-use)
4. [Realization](realization)
   - [Formulas](formulas)
   - [Main function](main-function)
5. [Documentation](documentation)

# About project
DESCRIPTION: This project was created to solve quadratic equations\
AUTHOR: Khomenko Michail\
DATE_OF_CREATION: letka rt, august 2025\
This is my first project, please be more lenient.\
![rtLogo](https://start.mipt.ru/public/olympic/70/9b/2e/2e3f03_.jpg?t=121cf)

## Possibilities
- solution of quadratic equations of any kind.\
- handling user input and errors.\
- three tests of function "solveSquare" are included, also testing from file is included.\
- command line argument handling and various program modes are included\

## How to use
Use comand
```
make build
```
for building program\
Then use 
```
./SolveSquare.exe
or
./SolveSquare.exe --help
or
./SolveSquare.exe --version
or
./SolveSquare.exe --test <path/to/file>
or
./SolveSquare.exe --single
```
depending on your wishes\
--help - Prints available command line arguments and their description\
--version - Prints program description\
--single - Runs a single solution of a quadratic equation\
--test pathToFile - Runs tests of the function solveSquare,
needs pathToFile as third argument\
or use
```
make run
```
for building program and run it without comand line arguments\
Also use 
```
make clean
```
to remove object files.
## Realization 
### Formulas
Program uses standart formulas of calculation of discriminant and roots of quadratic equation:\
![formulas](https://images.genius.com/1d894d7dec53f02fe10f336c230bd83f.640x640x1.jpg)
### Main function
The main function of the program is solveSquare, the algorithm of which looks like:\
```
if (compareDouble(quadratic->arguments.a, 0)) {
        if (compareDouble(quadratic->arguments.b, 0)) {
            if (compareDouble(quadratic->arguments.c, 0))
                quadratic->roots.nRoots = infinityRoots;
            else quadratic->roots.nRoots = noRoots;
        }
        else {
            quadratic->roots.x1 = solveLinear(quadratic->arguments.b, quadratic->arguments.c);
            quadratic->roots.nRoots = oneRoot;
        }
    }
    else {
        if (compareDouble(quadratic->arguments.c, 0)) {      // if с == 0
            if (compareDouble(quadratic->arguments.b, 0)) {
                quadratic->roots.x1 = noRoots;
                quadratic->roots.nRoots = oneRoot;
            }
            else {
                quadratic->roots.x1 = noRoots;
                quadratic->roots.x2 = solveLinear(quadratic->arguments.a, quadratic->arguments.b);
                rootsInAscendingOrder (&(quadratic->roots.x1), &(quadratic->roots.x2));
                quadratic->roots.nRoots = twoRoots;
            }
        }

        else {                    // if а != 0 and с != 0
            d = quadratic->arguments.b * quadratic->arguments.b - 4 * quadratic->arguments.a * quadratic->arguments.c;      //вычисление дискриминанта

            if (d < 0)
                quadratic->roots.nRoots = noRoots;

            else if (compareDouble(d, 0)) {    //if  d == 0
                quadratic->roots.x1 = -quadratic->arguments.b/(2*quadratic->arguments.a);
                quadratic->roots.nRoots = oneRoot;
                }

            else {   //if d > 0
                sqrtD = sqrt(d);
                quadratic->roots.x1 = (-quadratic->arguments.b - sqrtD) / (2*quadratic->arguments.a);
                quadratic->roots.x2 = (-quadratic->arguments.b + sqrtD) / (2*quadratic->arguments.a);
                rootsInAscendingOrder (&(quadratic->roots.x1), &(quadratic->roots.x2));
                quadratic->roots.nRoots = twoRoots;
            }
        }
    }
```
## Documentation 
You can find documentation for project there:



