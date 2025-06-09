#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

int main() {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct ifreq ifr;
    char *iface = "eno1";  // Change if needed
    unsigned char *mac;

    strncpy(ifr.ifr_name, iface, IFNAMSIZ);

    // Get IP
    ioctl(fd, SIOCGIFADDR, &ifr);
    printf("IP Address: %s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

    // Get MAC
    ioctl(fd, SIOCGIFHWADDR, &ifr);
    mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
    printf("MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    close(fd);
    return 0;
}

