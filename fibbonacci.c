#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// Check if a number is prime
int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main() {
    int pipefd[2];          // pipefd[0] = read end, pipefd[1] = write end
    if (pipe(pipefd) == -1) { perror("pipe"); exit(1); }

    pid_t pid = fork();     // Create a child process
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        // Child process: generate Fibonacci numbers and write to pipe
        close(pipefd[0]);                   // Close unused read end
        int a = 0, b = 1, c;
        for (int i = 0; i < 25; i++) {
            c = a + b;
            write(pipefd[1], &c, sizeof(c)); // Write Fibonacci number
            a = b; b = c;                    // Update for next term
        }
        close(pipefd[1]);                   // Close write end after done
    } else {
        // Parent process: read numbers from pipe and print primes
        close(pipefd[1]);                   // Close unused write end
        int num;
        printf("Prime Fibonacci numbers:\n");
        while (read(pipefd[0], &num, sizeof(num)) > 0)
            if (is_prime(num)) printf("%d\t", num);
        close(pipefd[0]);                   // Close read end
        printf("\n");
    }

    return 0;
}
