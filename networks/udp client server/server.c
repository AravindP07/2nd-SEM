#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockdes, n;
    struct sockaddr_in server, client;
    char msg[2000], reply[2000];
    socklen_t c;

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        printf("Cannot create socket\n");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(sockdes, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Bind failed\n");
        return 1;
    }

    printf("Bind done\n");
    c = sizeof(client);

    n = recvfrom(sockdes, msg, sizeof(msg) - 1, 0, (struct sockaddr*)&client, &c);
    if (n < 0) {
        printf("Receive failed\n");
        return 1;
    }
    msg[n] = '\0';
    printf("From client: %s\n", msg);

    printf("Enter reply: ");
    fgets(reply, sizeof(reply), stdin);
    reply[strcspn(reply, "\n")] = 0;

    sendto(sockdes, reply, strlen(reply), 0, (struct sockaddr*)&client, c);

    close(sockdes);
    return 0;
}


