#include <stdio.h>

int main() {
    int np, nh, p[10], h[10], actual[10], holeId[10], alloc[10] = {0};

    printf("Enter number of Holes: ");
    scanf("%d", &nh);
    printf("Enter sizes of %d Holes:\n", nh);
    for (int i = 0; i < nh; i++) {
        scanf("%d", &h[i]);
        actual[i] = h[i];
    }

    printf("\nEnter number of Processes: ");
    scanf("%d", &np);
    printf("Enter sizes of %d Processes:\n", np);
    for (int i = 0; i < np; i++) scanf("%d", &p[i]);

    for (int i = 0; i < np; i++) {
        int bestIdx = -1;
        for (int j = 0; j < nh; j++)
            if (p[i] <= h[j] && (bestIdx == -1 || h[j] < h[bestIdx]))
                bestIdx = j;
        if (bestIdx != -1) {
            h[bestIdx] -= p[i];
            alloc[i] = 1;
            holeId[i] = bestIdx;
        }
    }

    printf("\n\tBest Fit Allocation\nProcess\tSize\tHole\n");
    for (int i = 0; i < np; i++)
        printf("P%d\t%d\t%s%d\n", i, p[i], alloc[i] ? "H" : "Not allocated", alloc[i] ? holeId[i] : 0);

    printf("\nHole\tActual\tAvailable\n");
    for (int i = 0; i < nh; i++)
        printf("H%d\t%d\t%d\n", i, actual[i], h[i]);

    return 0;
}
