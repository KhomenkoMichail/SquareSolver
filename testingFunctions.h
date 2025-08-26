void testSolveSquare (void);
int oneTest (struct equation* testingArguments, struct solution testSolutions);
void testsFromFile (struct equation* quadratka);
void initFileSolution (struct solution* fileSolution);
int readFromFileAndTest(struct equation* quadratka, struct solution* fileSolution, FILE* file);
int readFromBufferAndTest(struct equation* quadratka, struct solution* fileSolution, char* fileBuffer);
void testFromFileByBuffer (struct equation* quadratka);
