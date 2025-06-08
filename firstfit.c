#include <stdio.h>

int main() {
    int np, nh, p[10], h[10], a[10] = {0}, holeId[10];

    printf("Enter number of Holes: ");
    scanf("%d", &nh);
    printf("Enter sizes of %d Holes:\n", nh);
    for (int i = 0; i < nh; i++) scanf("%d", &h[i]);

    printf("\nEnter number of Processes: ");
    scanf("%d", &np);
    printf("Enter sizes of %d Processes:\n", np);
    for (int i = 0; i < np; i++) scanf("%d", &p[i]);

    for (int i = 0; i < np; i++)
        for (int j = 0; j < nh; j++)
            if (!a[i] && p[i] <= h[j]) {
                h[j] -= p[i];
                a[i] = 1;
                holeId[i] = j;
                break;
            }

    printf("\n\tFirst Fit Allocation\nProcess\tSize\tHole\n");
    for (int i = 0; i < np; i++)
        printf("P%d\t%d\t%s%d\n", i, p[i], a[i] ? "H" : "Not allocated", a[i] ? holeId[i] : 0);

    printf("\nHole\tAvailable\n");
    for (int i = 0; i < nh; i++)
        printf("H%d\t%d\n", i, h[i]);

    return 0;
}
