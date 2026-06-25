#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64

void execute_command(const char *cmd_str) {
    char *copy = strdup(cmd_str);
    if (!copy) {
        perror("strdup");
        exit(1);
    }

    char *args[MAX_ARGS];
    int argc = 0;
    char *token = strtok(copy, " ");
    while (token && argc < MAX_ARGS - 1) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;

    if (argc == 0) {
        free(copy);
        return;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        free(copy);
        return;
    }

    pid_t child1 = fork();
    if (child1 == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        free(copy);
        return;
    }

    if (child1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    }

    pid_t child2 = fork();
    if (child2 == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        free(copy);
        return;
    }

    if (child2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execlp("wc", "wc", "-c", (char *)NULL);
        perror("execlp");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    free(copy);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s \"command1 args...\" \"command2 args...\" ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        execute_command(argv[i]);
    }

    return 0;
}