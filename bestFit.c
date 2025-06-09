#include <stdio.h>

// Process structure
struct Process {
    int size;
    int flag;      // 0 = not allocated, 1 = allocated
    int holeIndex; // Index of the hole it was allocated to
} processes[10];

// Hole structure
struct Hole {
    int size;
    int originalSize;
    int id;
} holes[10];

// Sort holes by available size (ascending)
void sortHoles(int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (holes[i].size > holes[j].size) {
                struct Hole temp = holes[i];
                holes[i] = holes[j];
                holes[j] = temp;
            }
        }
    }
}

int main() {
    int numHoles, numProcesses;

    printf("Enter number of memory holes: ");
    scanf("%d", &numHoles);

    for (int i = 0; i < numHoles; i++) {
        printf("Size of Hole H%d: ", i);
        scanf("%d", &holes[i].size);
        holes[i].originalSize = holes[i].size;
        holes[i].id = i;
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        printf("Size of Process P%d: ", i);
        scanf("%d", &processes[i].size);
        processes[i].flag = 0;  // Mark as not allocated
    }

    // Best Fit Allocation
    for (int i = 0; i < numProcesses; i++) {
        sortHoles(numHoles);
        for (int j = 0; j < numHoles; j++) {
            if (!processes[i].flag && processes[i].size <= holes[j].size) {
                processes[i].flag = 1;            // Mark as allocated
                processes[i].holeIndex = holes[j].id;
                holes[j].size -= processes[i].size;
                break; // Allocate once
            }
        }
    }

    // Allocation result
    printf("\nBest Fit Allocation:\n");
    printf("-----------------------------\n");
    printf("Process\tSize\tHole\n");
    printf("-----------------------------\n");
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].flag)
            printf("P%d\t%d\tH%d\n", i, processes[i].size, processes[i].holeIndex);
        else
            printf("P%d\t%d\tNot Allocated\n", i, processes[i].size);
    }

    // Final hole status
    printf("\nFinal Hole Status:\n");
    printf("-----------------------------\n");
    printf("Hole\tOriginal\tAvailable\n");
    printf("-----------------------------\n");
    for (int i = 0; i < numHoles; i++) {
        printf("H%d\t%d\t\t%d\n", holes[i].id, holes[i].originalSize, holes[i].size);
    }

    return 0;
}

