#include <stdio.h>
#include <stdbool.h>

// Define a process structure
struct process {
    int id, arrival, burst, wait, comp, tottime;
    bool completed;
} p[20];

int main() {
    int n, time = 0, completed = 0;

    float totwait = 0, totturn = 0;

    // Input: number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input: process details
    for (int i = 0; i < n; i++) {
        printf("\nProcess ID: ");
        scanf("%d", &p[i].id);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
        p[i].completed = false; // Initially not completed
    }

    // Scheduling: Shortest Job First (non-preemptive)
    while (completed < n) {
        int shortest = -1, minBurst = 9999;

        // Find shortest job among arrived and uncompleted processes
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= time && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                shortest = i;
            }
        }

        if (shortest != -1) {
            // Execute selected process
            time += p[shortest].burst;
            p[shortest].comp = time;
            p[shortest].tottime = time - p[shortest].arrival;          // Turnaround time
            p[shortest].wait = p[shortest].tottime - p[shortest].burst; // Waiting time
            p[shortest].completed = true;

            totwait += p[shortest].wait;
            totturn += p[shortest].tottime;
            completed++;
        } else {
            time++; // No process is ready; advance time
        }
    }

    // Output: Process table
    printf("\nID\tBurst\tArrival\tWait\tTurnaround\tCompletion");
    for (int i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%d\t%d\t\t%d", p[i].id, p[i].burst, p[i].arrival,
               p[i].wait, p[i].tottime, p[i].comp);
    }

    // Output: Averages
    printf("\n\nAverage Waiting Time: %.1f", totwait / n);
    printf("\nAverage Turnaround Time: %.1f\n", totturn / n);

    return 0;
}
