#define _BLOCK_ 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int     argc;
    char** argv;
}   stringArray;

int just_like_main(int, char**);

int main(void)
{
    const int   n_parm = 16;
    const char* test_strings[16] =
    {
        "Creating", "a", "block", "of",
        "strings", ",", "just", "like",
        "the", "system", "does", "for" ,
        "main()", "for", "every", "program"
    };
  
    stringArray ex; // example
    int N = _BLOCK_; // 1st block
    ex.argc = 0;
    ex.argv = (char**)malloc(sizeof(char*) * _BLOCK_);
    const char* program_name = "full path of program";
    ex.argv[ex.argc] = (char*)malloc(1 + strlen(program_name));
    strcpy(ex.argv[ex.argc], program_name);
    ex.argc += 1; // 1st arg. That was easy

    // loads all other strings into **argv
    for (int i = 0; i < n_parm; i += 1)
    {   // each one
        if (ex.argc >= N)
        {   // block is full
            N = N + _BLOCK_;
            char* new_block = realloc(ex.argv, (N * sizeof(char*)));
            printf("Block extended for a total of %d pointers\n", N);
            ex.argv = (char**)new_block;
        };
        ex.argv[ex.argc] = (char*)malloc(1 + strlen(test_strings[i]));
        strcpy(ex.argv[ex.argc], test_strings[i]);
        ex.argc += 1;
    };  // for()
    printf("\t%d strings in the block:\n", ex.argc);
    for (int i = 0; i < ex.argc; i += 1)
    {
        printf("\t\t%d of %d: '%s'\n", 1 + i, ex.argc, ex.argv[i]);
    };

    // now trims the end of the block
    // allocated: N.
    // used: argc
    printf("\t%d pointers allocated\n", N);
    printf("\t%d arguments read\n", ex.argc);
    if (N == ex.argc)
        printf("\tNothing to free()\n");
    else
    {
        printf("\t%d pointers to free\n", N - ex.argc);
        char* new_size = realloc(ex.argv, (ex.argc * sizeof(char*)));
        printf("\tBlock size trimmed for a total of %d pointers\n", ex.argc);
        ex.argv = (char**)new_size;
    };
    printf("\tCalling just_like_main() with these args\n");
    int res = just_like_main(ex.argc, ex.argv);
    printf("\n\n\t\"main()\" returned %d\n", res);
    printf("\tNow fres the block and exit\n");
    for (int i = 0; i < ex.argc; i += 1)
        free(ex.argv[i]);
    free(ex.argv);
    printf("\n\nGame over\n");
    return 0;
};

int just_like_main(int argc, char** argv)
{
    printf("\n\tAt \"main()\": %d arguments\n\n", argc);
    for (int i = 0; i < argc; i += 1)
        printf("%8d\t'%s'\n", i, argv[i]);
    return 0;
};  // nova_main()

