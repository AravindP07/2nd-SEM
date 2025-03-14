#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main() {
    int sockdes;
    FILE *fd;
    char filename[25], new_filename[25], filecontent[2000];
    struct sockaddr_in server;
    socklen_t c = sizeof(server);

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        printf("Cannot create socket\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);

    printf("Enter the file name: ");
    scanf("%s", filename);
    printf("Enter new file name: ");
    scanf("%s", new_filename);

    sendto(sockdes, filename, strlen(filename), 0, (struct sockaddr*)&server, c);

    int n = recvfrom(sockdes, filecontent, sizeof(filecontent) - 1, 0, (struct sockaddr*)&server, &c);
    if (n < 0) {
        printf("Error receiving file content\n");
        return 1;
    }
    filecontent[n] = '\0';

    if (strcmp(filecontent, "File not found") == 0) {
        printf("Server: File not found\n");
    } else {
        fd = fopen(new_filename, "w");
        if (fd == NULL) {
            printf("Error creating file\n");
            return 1;
        }
        fprintf(fd, "%s", filecontent);
        fclose(fd);
        printf("File received and saved as %s\n", new_filename);
    }

    close(sockdes);
    return 0;
}

