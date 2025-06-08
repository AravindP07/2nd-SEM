#include <stdio.h>

struct process {
    int id, burst, arrival, wait, tottime, comp;
} p[20];

int main() {
    int n;
    float totalWait = 0, totalTurn = 0;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("\nProcess ID: ");
        scanf("%d", &p[i].id);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
    }

    // First process setup
    p[0].wait = 0;
    p[0].comp = p[0].arrival + p[0].burst;

    // Calculate for remaining processes
    for (int i = 1; i < n; i++) {
        if (p[i].arrival > p[i - 1].comp)
            p[i].wait = 0;
        else
            p[i].wait = p[i - 1].comp - p[i].arrival;

        p[i].comp = p[i].arrival + p[i].wait + p[i].burst;
    }

    // Turnaround time and totals
    for (int i = 0; i < n; i++) {
        p[i].tottime = p[i].comp - p[i].arrival;
        totalWait += p[i].wait;
        totalTurn += p[i].tottime;
    }

    // Output in lightly formatted table style
    printf("\nID  Arrival  Burst  Wait  Turnaround  Completion");
    for (int i = 0; i < n; i++) {
        printf("\n%-3d %-8d%-7d%-6d%-11d%-10d",
               p[i].id, p[i].arrival, p[i].burst,
               p[i].wait, p[i].tottime, p[i].comp);
    }

    // Print averages
    printf("\n\nAverage Waiting Time   = %.1f", totalWait / n);
    printf("\nAverage Turnaround Time= %.1f\n", totalTurn / n);

    return 0;
}
