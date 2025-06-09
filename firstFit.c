#include <stdio.h>

// Structure to represent a process
struct Process {
    int size;     // Size of the process
    int flag;     // Allocation flag (0 = not allocated, 1 = allocated)
    int holeId;   // Index of the hole to which the process is allocated
} p[10];          // Array of up to 10 processes

// Structure to represent a hole
struct Hole {
    int size;     // Available size in the hole (gets reduced as processes are allocated)
    int actual;   // Original size of the hole (for reporting)
} h[10];          // Array of up to 10 holes

int main() {
    int np, nh;   // np = number of processes, nh = number of holes

    // Step 1: Input number and sizes of memory holes
    printf("Enter number of Holes: ");
    scanf("%d", &nh);
    for (int i = 0; i < nh; i++) {
        printf("Size of hole H%d: ", i);
        scanf("%d", &h[i].size);
        h[i].actual = h[i].size;  // Save the original size
    }

    // Step 2: Input number and sizes of processes
    printf("\nEnter number of Processes: ");
    scanf("%d", &np);
    for (int i = 0; i < np; i++) {
        printf("Size of process P%d: ", i);
        scanf("%d", &p[i].size);
        p[i].flag = 0;  // Initialize allocation flag as not allocated
    }

    // Step 3: First Fit Allocation
    for (int i = 0; i < np; i++) {          // Loop through all processes
        for (int j = 0; j < nh; j++) {      // Loop through all holes
            if (!p[i].flag && p[i].size <= h[j].size) {  // If not yet allocated and hole is large enough
                p[i].flag = 1;              // Mark process as allocated
                p[i].holeId = j;            // Save the hole ID
                h[j].size -= p[i].size;     // Reduce the hole size
                break;                      // Move to the next process
            }
        }
    }

    // Step 4: Display allocation result
    printf("\n\tFirst Fit Allocation\nProcess\tSize\tHole");
    for (int i = 0; i < np; i++) {
        printf("\nP%d\t%d\t", i, p[i].size);
        if (p[i].flag)
            printf("H%d", p[i].holeId);
        else
            printf("Not allocated");
    }

    // Step 5: Display final hole availability
    printf("\n\nHole\tActual\tAvailable");
    for (int i = 0; i < nh; i++)
        printf("\nH%d\t%d\t%d", i, h[i].actual, h[i].size);

    return 0;
}
