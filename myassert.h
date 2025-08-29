#define MYASSERT(e) \
    if (!(e)) { \
        printf(RED "------------------------------------------------------\n");\
        printf ("ERROR!\nfile: %s\n", __FILE__);\
        printf ("function: %s\n", __func__);\
        printf ("line: %d\n", __LINE__);\
        printf("------------------------------------------------------\n" RESET);\
        exit(EXIT_FAILURE);\
    }
