#include <stdio.h>
#include <stdbool.h>

// Define a process structure
struct process {
    int id, wait, burst, tottime, comp, arrival, priority;
    bool completed;  // True if process is already executed
} p[20];

int main() {
    int n, time = 0, completed = 0;
    float totwait = 0, totturn = 0;

    // Input: Number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input: Process details
    for (int i = 0; i < n; i++) {
        printf("\nProcess ID: ");
        scanf("%d", &p[i].id);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst);
        printf("Priority (higher = better): ");
        scanf("%d", &p[i].priority);

        // Initialize process state
        p[i].completed = false;
    }

    // Scheduling logic (Non-Preemptive Priority)
    while (completed < n) {
        int highest = -1, highPriority = -1;

        // Find the highest-priority process that has arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= time && p[i].priority > highPriority) {
                highPriority = p[i].priority;
                highest = i;
            }
        }

        if (highest != -1) {
            // Execute selected process
            time += p[highest].burst;
            p[highest].comp = time;
            p[highest].tottime = time - p[highest].arrival;         // Turnaround Time
            p[highest].wait = p[highest].tottime - p[highest].burst; // Waiting Time
            p[highest].completed = true;

            totwait += p[highest].wait;
            totturn += p[highest].tottime;
            completed++;
        } else {
            time++; // No process is ready yet, increment time
        }
    }

    // Output: Process table
    printf("\nID\tBurst\tArrival\tPriority\tWait\tTurnaround\tCompletion");
    for (int i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d", p[i].id, p[i].burst, p[i].arrival,
               p[i].priority, p[i].wait, p[i].tottime, p[i].comp);
    }

    // Output: Averages
    printf("\n\nAverage Waiting Time: %.1f", totwait / n);
    printf("\nAverage Turnaround Time: %.1f\n", totturn / n);

    return 0;
}
