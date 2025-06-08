#include <stdio.h>
#include <string.h>

int num = 0;                    // Number of files allocated
int len[10], str[10];          // Length and starting block for each file
char fid[10][4];               // File names (max 3 chars)
char disk[20][4];              // Disk blocks (20 total), stores file names

// Print file directory table
void directory() {
    printf("\nFile\tStart\tLength\n");
    for (int i = 0; i < num; i++)
        printf("%-4s\t%3d\t%6d\n", fid[i], str[i], len[i]);
}

// Display disk blocks visually
void display() {
    printf("\nDisk Blocks:\n");
    for (int i = 0; i < 20; i++) printf("%4d", i);        // Block numbers
    printf("\n");
    for (int i = 0; i < 20; i++) 
        printf("%4s", (disk[i][0] == '\0') ? "." : disk[i]); // Show file ID or '.'
    printf("\n");
}

int main() {
    char id[4];          // Temporary file name
    int start, blocks, choice;

    // Initialize disk to empty
    for (int i = 0; i < 20; i++)
        strcpy(disk[i], "");

    printf("Disk before allocation:\n");
    display();

    do {
        // Take input for file allocation
        printf("\nEnter file name (max 3 chars): ");
        scanf("%3s", id);
        printf("Enter start block: ");
        scanf("%d", &start);
        printf("Enter number of blocks: ");
        scanf("%d", &blocks);

        // Check if request exceeds disk range
        if (start < 0 || start + blocks > 20) {
            printf("Error: Request exceeds disk range.\n");
            continue;
        }

        // Check if blocks are free
        int free = 1;
        for (int i = start; i < start + blocks; i++) {
            if (disk[i][0] != '\0') {
                free = 0;
                break;
            }
        }

        if (!free) {
            printf("Error: Contiguous allocation not possible.\n");
            continue;
        }

        // Allocate blocks
        strcpy(fid[num], id);
        str[num] = start;
        len[num] = blocks;

        for (int i = start; i < start + blocks; i++)
            strcpy(disk[i], id);

        num++;
        printf("Allocation successful.\n");

        // Ask if user wants to allocate more
        printf("More allocation? (1. Yes, 2. No): ");
        scanf("%d", &choice);

    } while (choice == 1);

    // Final output
    printf("\nContiguous Allocation Result:\n");
    directory();
    printf("\nDisk after allocation:\n");
    display();

    return 0;
}
