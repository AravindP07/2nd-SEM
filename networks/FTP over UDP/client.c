#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock, n;
    struct sockaddr_in server;
    socklen_t slen = sizeof(server);
    char buf[1024];
    FILE *f;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    printf("File name: ");
    scanf("%s", buf);
    sendto(sock, buf, strlen(buf), 0, (void*)&server, slen);

    f = fopen(buf, "rb");
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0)
        sendto(sock, buf, n, 0, (void*)&server, slen);

    buf[0] = '\0';
    sendto(sock, buf, 1, 0, (void*)&server, slen);

    fclose(f);
    close(sock);
}
