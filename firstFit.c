#include <stdio.h> // Include standard input/output library

int main() {
    int np, nh;                      // np = number of processes, nh = number of holes
    int p[10], h[10];                // Arrays to hold process sizes and hole sizes
    int actual[10];                 // To store original size of holes (for reporting)
    int holeId[10];                 // To store the hole assigned to each process
    int alloc[10] = {0};            // Allocation flag: 1 = allocated, 0 = not allocated

    // Input: number of memory holes
    printf("Enter number of Holes: ");
    scanf("%d", &nh);

    // Input: sizes of each memory hole
    printf("Enter sizes of %d Holes:\n", nh);
    for (int i = 0; i < nh; i++) {
        scanf("%d", &h[i]);         // Read size
        actual[i] = h[i];           // Save original size for later display
    }

    // Input: number of processes
    printf("\nEnter number of Processes: ");
    scanf("%d", &np);

    // Input: sizes of each process
    printf("Enter sizes of %d Processes:\n", np);
    for (int i = 0; i < np; i++)
        scanf("%d", &p[i]);

    // Allocation Logic: First Fit
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nh; j++) {
            // If process fits and not yet allocated
            if (p[i] <= h[j]) {
                h[j] -= p[i];        // Reduce hole size by process size
                alloc[i] = 1;        // Mark as allocated
                holeId[i] = j;       // Save which hole it was assigned to
                break;               // Stop at the first fit (important!)
            }
        }
    }

    // Output: Allocation result
    printf("\n\tFirst Fit Allocation\n");
    printf("Process\tSize\tHole\n");
    for (int i = 0; i < np; i++) {
        if (alloc[i])
            printf("P%d\t%d\tH%d\n", i, p[i], holeId[i]);
        else
            printf("P%d\t%d\tNot allocated\n", i, p[i]);
    }

    // Output: Hole usage report
    printf("\nHole\tActual\tAvailable\n");
    for (int i = 0; i < nh; i++)
        printf("H%d\t%d\t%d\n", i, actual[i], h[i]);

    return 0; // End of program
}
