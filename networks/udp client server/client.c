#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes;
    struct sockaddr_in server;
    char msg[2000], reply[2000];
    socklen_t c;

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        printf("Cannot create socket\n");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);
    c = sizeof(server);

    printf("Enter a message: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0;

    sendto(sockdes, msg, strlen(msg), 0, (struct sockaddr*)&server, c);

    int n = recvfrom(sockdes, reply, sizeof(reply) - 1, 0, (struct sockaddr*)&server, &c);
    if (n < 0) {
        printf("Receive failed\n");
        return 1;
    }
    reply[n] = '\0';
    printf("From server: %s\n", reply);

    close(sockdes);
    return 0;
}


