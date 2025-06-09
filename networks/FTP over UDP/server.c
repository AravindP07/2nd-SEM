#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock, n;
    struct sockaddr_in server, client;
    socklen_t clen = sizeof(client);
    char buf[1024];
    FILE *f;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (void*)&server, sizeof(server));

    n = recvfrom(sock, buf, sizeof(buf), 0, (void*)&client, &clen);
    buf[n] = '\0';
    f = fopen(buf, "wb");

    while (1) {
        n = recvfrom(sock, buf, sizeof(buf), 0, (void*)&client, &clen);
        if (n == 1 && buf[0] == '\0') break;
        fwrite(buf, 1, n, f);
    }

    fclose(f);
    close(sock);
}

