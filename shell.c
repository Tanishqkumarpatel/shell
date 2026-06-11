#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_CMD_SIZE 1024
#define RED "\033[0;31m"
#define RESET "\e[0m"

char*   read_command();
char**  get_arguments(char *);
int     execute(char **);

char* read_command() {
    
    int position = 0;
    int c;
    int buffer_size = BUFFER_CMD_SIZE;
    char *buffer = malloc(buffer_size);

    if (!buffer) {
        fprintf(stderr, "%smy_shell: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    while(1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= buffer_size) {
            buffer_size += BUFFER_CMD_SIZE;
            buffer = realloc(buffer, buffer_size);

            if (!buffer) {
                fprintf(stderr, "%smy_shell: Allocation error%s\n", RED, RESET);
                exit(EXIT_FAILURE);
            }
        }
    }
}

void run() {
    char  *cmd   = NULL;
    char  **args = NULL;
    int   status =    1;

    while (status)
    {
        printf("my_shell>>> ");
        cmd    = read_command();
        printf("%s\n", cmd);
        // args   = get_arguments(cmd);
        // status = execute(args);
        free(cmd);
        free(args);
    }
    

}

int main() {
    run();
    return 0;
}