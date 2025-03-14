#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main() {
    int sockdes, newsock, c;
    struct sockaddr_in server, client;
    char msg[2000], reply[2000];

    // Create socket
    sockdes = socket(AF_INET, SOCK_STREAM, 0);
    if (sockdes == -1) {
        perror("Cannot create socket");
        return 1;
    }

    // Configure server structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind the socket
    if (bind(sockdes, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }
    printf("Bind done\n");

    // Listen for incoming connections
    listen(sockdes, 3);
    printf("Waiting for incoming connection...\n");

    c = sizeof(struct sockaddr_in);

    // Accept connection
    if ((newsock = accept(sockdes, (struct sockaddr*)&client, (socklen_t*)&c)) < 0) {
        perror("Accept failed");
        return 1;
    }
    printf("Connection accepted\n");

    // Communication loop
    while (1) {
        memset(reply, 0, sizeof(reply)); // Clear buffer
        int recv_size = recv(newsock, reply, sizeof(reply) - 1, 0);
        
        if (recv_size <= 0) {
            printf("Client disconnected\n");
            break;
        }

        printf("From client: %s\n", reply);

        printf("To client: ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0; // Remove newline

        send(newsock, msg, strlen(msg) + 1, 0);
    }

    close(newsock);
    close(sockdes);
    return 0;
}



