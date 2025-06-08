#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // Buffer size

int mutex = 1;           // Controls mutual exclusion
int empty = SIZE;        // Count of empty slots
int full = 0;            // Count of full slots
int buffer[SIZE];        // Shared buffer
int in = 0, out = 0;     // Indexes for producer and consumer

// Simulates wait (P operation)
void wait(int *s) {
    while (*s <= 0);  // Wait until semaphore is available
    (*s)--;           // Acquire semaphore
}

// Simulates signal (V operation)
void signal(int *s) {
    (*s)++;           // Release semaphore
}

// Producer logic
void produce() {
    if (empty == 0) {
        printf("Buffer full! Cannot produce.\n");
        return;
    }

    int item;
    printf("Enter item to produce: ");
    scanf("%d", &item);

    wait(&empty);               // Wait if no empty slots
    wait(&mutex);               // Enter critical section

    buffer[in] = item;          // Add item to buffer
    in = (in + 1) % SIZE;       // Move to next index

    signal(&mutex);             // Exit critical section
    signal(&full);              // One more full slot

    printf("Produced: %d\n", item);
}

// Consumer logic
void consume() {
    if (full == 0) {
        printf("Buffer empty! Cannot consume.\n");
        return;
    }

    wait(&full);               // Wait if buffer is empty
    wait(&mutex);              // Enter critical section

    int item = buffer[out];    // Remove item from buffer
    out = (out + 1) % SIZE;    // Move to next index

    signal(&mutex);            // Exit critical section
    signal(&empty);            // One more empty slot

    printf("Consumed: %d\n", item);
}

// Menu to simulate user interaction
int main() {
    int choice;
    printf("1. Produce\n2. Consume\n3. Exit\n");

    while (1) {
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: produce(); break;
            case 2: consume(); break;
            case 3: exit(0);   // Terminate program
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
