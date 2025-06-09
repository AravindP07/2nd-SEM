#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char filename[100], content[1000];
    int choice;

    while (1) {
        printf("\nMenu:\n1. Write\n2. Append\n3. Display\n4. Exit\nChoose: ");
        scanf("%d", &choice);
        getchar(); // clear newline after number input

        if (choice == 4) break;

        printf("Filename: ");
        scanf("%s", filename);
        getchar(); // clear newline

        if (choice == 1 || choice == 2) {
            printf("Enter content:\n");
            fgets(content, sizeof(content), stdin);
            fp = fopen(filename, (choice == 1) ? "w" : "a");
            if (!fp) {
                printf("Cannot open file!\n");
                continue;
            }
            fputs(content, fp);
            fclose(fp);
            printf("Success!\n");
        } else if (choice == 3) {
            fp = fopen(filename, "r");
            if (!fp) {
                printf("Cannot open file!\n");
                continue;
            }
            printf("\nContents:\n");
            while (fgets(content, sizeof(content), fp)) {
                printf("%s", content);
            }
            fclose(fp);
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
