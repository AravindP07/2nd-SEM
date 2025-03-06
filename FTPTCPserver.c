#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0), c;
    struct sockaddr_in server = {AF_INET, htons(8080), INADDR_ANY};
    
    bind(s, (struct sockaddr*)&server, sizeof(server));
    listen(s, 1);
    
    printf("Waiting for client...\n");
    c = accept(s, NULL, NULL);
    printf("Client connected. Receiving file...\n");

    // Receive the file name from the client
    char file_name[1024];
    int len = read(c, file_name, sizeof(file_name));
    file_name[len] = '\0';  // Null-terminate the file name string
    printf("Receiving file: %s\n", file_name);

    // Open the file for writing
    FILE *file = fopen(file_name, "w");
    if (!file) {
        perror("Failed to open file");
        close(c);
        close(s);
        return 1;
    }

    // Receive the file data from the client
    char buf[1024];
    int bytes_received;
    while ((bytes_received = read(c, buf, sizeof(buf))) > 0) {
        fwrite(buf, 1, bytes_received, file);
    }

    fclose(file);
    close(c);
    close(s);
    printf("File received and saved as '%s'.\n", file_name);
    return 0;
}
