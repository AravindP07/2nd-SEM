#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock, n;
    struct sockaddr_in server;
    char buf[1024];
    FILE *f;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    printf("File name: ");
    scanf("%s", buf);
    send(sock, buf, strlen(buf), 0);

    f = fopen(buf, "rb");
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0)
        send(sock, buf, n, 0);

    fclose(f);
    close(sock);
}
