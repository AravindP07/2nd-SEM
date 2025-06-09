#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock, client, n;
    struct sockaddr_in server, client_addr;
    socklen_t len = sizeof(client_addr);
    char buf[1024];
    FILE *f;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&server, sizeof(server));
    listen(sock, 1);
    client = accept(sock, (struct sockaddr*)&client_addr, &len);

    n = recv(client, buf, sizeof(buf), 0);
    buf[n] = '\0';
    f = fopen(buf, "wb");

    while ((n = recv(client, buf, sizeof(buf), 0)) > 0)
        fwrite(buf, 1, n, f);

    fclose(f);
    close(client);
    close(sock);
}



