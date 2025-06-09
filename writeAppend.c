#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[100];
    char content[1000];
    FILE *filePtr;
    int choice;

    while(1) {
        printf("\nFile Operations Menu:\n");
        printf("1. Write to a file\n");
        printf("2. Append to a file\n");
        printf("3. Display file contents\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: // Write to file
                printf("Enter filename: ");
                scanf("%s", filename);
                
                printf("Enter content to write (max 1000 chars):\n");
                getchar(); // Clear input buffer
                fgets(content, sizeof(content), stdin);
                
                filePtr = fopen(filename, "w");
                if(filePtr == NULL) {
                    printf("Error opening file!\n");
                    break;
                }
                
                fprintf(filePtr, "%s", content);
                fclose(filePtr);
                printf("Content written successfully!\n");
                break;

            case 2: // Append to file
                printf("Enter filename: ");
                scanf("%s", filename);
                
                printf("Enter content to append (max 1000 chars):\n");
                getchar(); // Clear input buffer
                fgets(content, sizeof(content), stdin);
                
                filePtr = fopen(filename, "a");
                if(filePtr == NULL) {
                    printf("Error opening file!\n");
                    break;
                }
                
                fprintf(filePtr, "%s", content);
                fclose(filePtr);
                printf("Content appended successfully!\n");
                break;

            case 3: // Display file contents
                printf("Enter filename: ");
                scanf("%s", filename);
                
                filePtr = fopen(filename, "r");
                if(filePtr == NULL) {
                    printf("Error opening file!\n");
                    break;
                }
                
                printf("\nFile contents:\n");
                while(fgets(content, sizeof(content), filePtr) != NULL) {
                    printf("%s", content);
                }
                fclose(filePtr);
                break;

            case 4: // Exit
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
