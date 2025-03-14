#include <stdio.h>
#include <string.h>
#include <unistd.h>	
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main() {
    int sockdes, fd, n;
    char fname[25] = "", fcontent[2000] = "";
    struct sockaddr_in server, client;
    socklen_t c = sizeof(client);

    sockdes = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockdes == -1) {
        printf("Cannot create socket\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(sockdes, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Bind failed\n");
        return 1;
    }

    printf("Bind done\n");

    n = recvfrom(sockdes, fname, sizeof(fname) - 1, 0, (struct sockaddr*)&client, &c);
    if (n < 0) {
        printf("Error receiving filename\n");
        return 1;
    }
    fname[n] = '\0';

    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        sendto(sockdes, "File not found", 15, 0, (struct sockaddr*)&client, c);
    } else {
        n = read(fd, fcontent, sizeof(fcontent) - 1);
        fcontent[n] = '\0';
        sendto(sockdes, fcontent, n, 0, (struct sockaddr*)&client, c);
        close(fd);
    }

    close(sockdes);
    return 0;
}

