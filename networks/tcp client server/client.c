#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in client;
    char msg[2000], reply[2000];

    // Create socket
    sockdes = socket(AF_INET, SOCK_STREAM, 0);
    if (sockdes == -1) {
        perror("Cannot create socket");
        return 1;
    }

    // Configure client structure
    client.sin_family = AF_INET;
    client.sin_port = htons(8888);
    
    // Convert IP address
    if (inet_pton(AF_INET, "127.0.0.1", &client.sin_addr) <= 0) {
        perror("Invalid address");
        return 1;
    }

    // Connect to server
    if (connect(sockdes, (struct sockaddr*)&client, sizeof(client)) < 0) {
        perror("Connection error");
        return 1;
    }
    printf("Connected to server\n");

    // Communication loop
    while (1) {
        printf("To server: ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0; // Remove newline

        // Send message
        send(sockdes, msg, strlen(msg) + 1, 0);

        // Receive reply
        memset(reply, 0, sizeof(reply)); // Clear buffer
        int recv_size = recv(sockdes, reply, sizeof(reply) - 1, 0);
        if (recv_size <= 0) {
            printf("Server disconnected\n");
            break;
        }

        printf("From server: %s\n", reply);
    }

    // Close socket
    close(sockdes);
    return 0;
}

