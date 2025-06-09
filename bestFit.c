#include <stdio.h>

// Structure to represent a process
struct Process {
    int size;     // Size of the process
    int flag;     // Allocation flag (0 = not allocated, 1 = allocated)
    int holeId;   // ID of the hole to which the process is allocated
} p[10];          // Array to hold up to 10 processes

// Structure to represent a hole
struct Hole {
    int id;       // Unique ID of the hole
    int size;     // Current available size of the hole (reduces after allocation)
    int actual;   // Original size of the hole (for display purposes)
} h[10];          // Array to hold up to 10 holes

// Function to sort holes in ascending order of available size
void sortHoles(struct Hole h[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (h[i].size > h[j].size) {
                struct Hole temp = h[i];
                h[i] = h[j];
                h[j] = temp;
            }
}

int main() {
    int np, nh;

    // Input number of memory holes
    printf("Enter number of Holes: ");
    scanf("%d", &nh);

    // Input size of each hole
    for (int i = 0; i < nh; i++) {
        printf("Size of hole H%d: ", i);
        scanf("%d", &h[i].size);
        h[i].actual = h[i].size;  // Store original size
        h[i].id = i;              // Assign hole ID (In order to track the hole, even after rearrangement)
    }

    // Input number of processes
    printf("\nEnter number of Processes: ");
    scanf("%d", &np);

    // Input size of each process
    for (int i = 0; i < np; i++) {
        printf("Size of process P%d: ", i);
        scanf("%d", &p[i].size);
        p[i].flag = 0;  // Mark as not allocated
    }

    // Best Fit Allocation Logic
    for (int i = 0; i < np; i++) {
        sortHoles(h, nh);  // Sort holes before each allocation attempt

        // Try to allocate the current process to the smallest suitable hole
        for (int j = 0; j < nh; j++) {
            if (!p[i].flag && p[i].size <= h[j].size) {
                p[i].flag = 1;             // Mark process as allocated
                p[i].holeId = h[j].id;     // Store the hole ID
                h[j].size -= p[i].size;    // Reduce available size of the hole
            }
        }
    }

    // Display Allocation Table
    printf("\n\tBest Fit Allocation\n");
    printf("---------------------------------\n");
    printf("Process\tSize\tAllocated Hole\n");
    printf("---------------------------------\n");
    for (int i = 0; i < np; i++) {
        if (p[i].flag)
            printf("P%d\t%d\tH%d\n", i, p[i].size, p[i].holeId);
        else
            printf("P%d\t%d\tNot allocated\n", i, p[i].size);
    }

    // Display Final Hole Status
    printf("\n---------------------------------\n");
    printf("Hole\tActual\tAvailable\n");
    printf("---------------------------------\n");
    for (int i = 0; i < nh; i++)
        printf("H%d\t%d\t%d\n", h[i].id, h[i].actual, h[i].size);

    return 0;
}
