#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server = {AF_INET, htons(8080)};
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    
    connect(s, (struct sockaddr*)&server, sizeof(server));
    printf("Connected. Sending file...\n");

    // Ask the user for the file name to send
    char file_name[1024];
    printf("Enter the file name to send: ");
    fgets(file_name, sizeof(file_name), stdin);
    file_name[strcspn(file_name, "\n")] = 0;  // Remove the newline character

    // Send the file name to the server
    write(s, file_name, strlen(file_name));

    // Open the file for reading
    FILE *file = fopen(file_name, "r");
    if (!file) {
        perror("Failed to open file");
        close(s);
        return 1;
    }

    // Send the file content to the server
    char buf[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buf, 1, sizeof(buf), file)) > 0) {
        write(s, buf, bytes_read);
    }

    fclose(file);
    close(s);
    printf("File sent successfully.\n");
    return 0;
}
