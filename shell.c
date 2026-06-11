#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

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
        if (position >= buffer_size) {
            buffer_size += BUFFER_CMD_SIZE;
            buffer = realloc(buffer, buffer_size);

            if (!buffer) {
                fprintf(stderr, "%smy_shell: Command Allocation Error%s\n", RED, RESET);
                exit(EXIT_FAILURE);
            }
        }
        c = getchar();
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;
    }
}

char** get_arguments(char *cmd) {
    int buffer_size = BUFFER_ARGS_SIZE;
    int position = 0;
    char **args = malloc(buffer_size * sizeof(char *));
    if (!args) {
        fprintf(stderr, "%smy_shell: Argument Allocation Error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }
    char *token = strtok(cmd, SHELL_DELIM);

    while (token != NULL) {
        args[position++] = token;

        if (position >= buffer_size) {
            buffer_size += BUFFER_ARGS_SIZE;
            args = realloc(args, buffer_size * sizeof(char *));

            if (!args) {
                fprintf(stderr, "%smy_shell: Argument Allocation Error%s\n", RED, RESET);
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SHELL_DELIM);
    }  
    args[position] = NULL;
    return args;
}

int execute(char **args) {
    if (args[0] == NULL) return 1;
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }
    int status;
    pid_t cpid = fork();

    if (cpid == 0) {
        if (execvp(args[0], args) < 0) {
            fprintf(stderr, "%smy_shell: %s%s\n", RED, strerror(errno), RESET);
            exit(EXIT_FAILURE);
        }
    } else if (cpid < 0) {
        fprintf(stderr, "%smy_shell: Error Forking Process%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    } else {
        waitpid(cpid, &status, WUNTRACED);
    }
    return 1;
}

void run() {
    char  *cmd   = NULL;
    char  **args = NULL;
    int   status =    1;

    while (status)
    {
        printf("my_shell>>> ");
        fflush(stdout);
        cmd    = read_command();
        args   = get_arguments(cmd);
        status = execute(args);
        free(args);
        free(cmd);
    }
    

}

int main() {
    run();
    return 0;
}