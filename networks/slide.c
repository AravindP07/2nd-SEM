#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to send a batch of frames
void sendFrames(int start, int windowSize, int totalFrames);

// Function to simulate random frame loss
int isFrameLost();

int main() {
    int windowSize, totalFrames;

    // Get user input for total frames and window size
    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);
    
    printf("Enter window size: ");
    scanf("%d", &windowSize);
    
    srand(time(NULL)); // Seed random number generator

    int base = 0; // Starting frame index

    // Loop until all frames are sent
    while (base < totalFrames) {
        sendFrames(base, windowSize, totalFrames); // Send frames in window
        int ack = base; // Track acknowledgment
        
        // Check acknowledgment for each frame in the window
        for (int i = base; i < base + windowSize && i < totalFrames; i++) {
            if (isFrameLost()) { // Simulate lost acknowledgment
                printf("Acknowledgment for Frame %d lost. Retransmitting window...\n", i);
                break;
            }
            ack++; // Move to next acknowledged frame
        }
        base = ack; // Slide the window forward
    }

    printf("All frames successfully transmitted!\n");
    return 0;
}

// Function to send frames within the window
void sendFrames(int start, int windowSize, int totalFrames) {
    printf("Sending frames: ");
    for (int i = start; i < start + windowSize && i < totalFrames; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

// Function to randomly simulate frame loss (20% probability)
int isFrameLost() {
    return rand() % 5 == 0;
}

