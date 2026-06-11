#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_CMD_SIZE 1024
#define BUFFER_ARGS_SIZE 10
#define RED "\033[0;31m"
#define RESET "\e[0m"
#define SHELL_DELIM " \t\r\n"


char*   read_command();
char**  get_arguments(char *);
int     execute(char **);

char* read_command() {
    
    int position = 0;
    int c;
    int buffer_size = BUFFER_CMD_SIZE;
    char *buffer = malloc(buffer_size);

    if (!buffer) {
        fprintf(stderr, "%smy_shell: Command Allocation Error%s\n", RED, RESET);
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
                fprintf(stderr, "%smy_shell: Command Allocation Error%s\n", RED, RESET);
                exit(EXIT_FAILURE);
            }
        }
    }
}

char** get_arguments(char *cmd) {
    int buffer_size = BUFFER_ARGS_SIZE;
    int position = 0;
    char **args = malloc(buffer_size * sizeof(char *));
    if (!args) {
        fprintf(stderr, "%smy_shell: Argument Allocation Error%s", RED, RESET);
        exit(EXIT_FAILURE);
    }
    char *token = strtok(cmd, SHELL_DELIM);

    while (token != NULL) {
        args[position++] = token;
        printf("%s\n", token);

        if (position >= buffer_size) {
            buffer_size += BUFFER_ARGS_SIZE;
            args = realloc(args, buffer_size * sizeof(char *));

            if (!args) {
                fprintf(stderr, "%smy_shell: Argument Allocation Error%s", RED, RESET);
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SHELL_DELIM);
    }  
    return args;
}

void run() {
    char  *cmd   = NULL;
    char  **args = NULL;
    int   status =    1;

    while (status)
    {
        printf("my_shell>>> ");
        cmd    = read_command();
        args   = get_arguments(cmd);
        // status = execute(args);
        free(cmd);
        free(args);
    }
    

}

int main() {
    run();
    return 0;
}