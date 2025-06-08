#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Check if a program to execute is given
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program_to_execute> [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process waits for child
        wait(NULL);
        printf("\nProcess creation completed\n");
        exit(EXIT_SUCCESS);
    } else if (pid == 0) {
        // Child process executes the given program
        execvp(argv[1], &argv[1]);

        // If execvp fails
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}
