#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char*   read_command();
char**  get_arguments(char *);
int     execute(char **);



void run() {
    char  *cmd   = NULL;
    char  **args = NULL;
    int   status =    1;

    while (status)
    {
        printf("my_shell>>> ");
        cmd    = read_command();
        args   = get_arguments(cmd);
        status = execute(args);
        free(cmd);
        free(args);
    }
    

}

int main() {
    run();
    return 0;
}