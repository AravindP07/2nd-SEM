#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 27     // Size of shared memory in bytes
#define SHM_KEY 2013    // Unique key for shared memory

int main() {
    int shmid;
    char *shm, *s;

    // Get the shared memory segment using the key
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid < 0) {
        printf("Server not started\n");
        exit(1);
    }

    printf("Accessing shared memory ID: %d\n", shmid);

    // Attach the shared memory to this process
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Read and print data from shared memory
    printf("Shared memory contents: ");
    for (s = shm; *s != '\0'; s++)
        putchar(*s);

    putchar('\n');

    // Write a signal character to indicate reading is done
    *shm = '*';

    return 0;
}
