#include <arpa/inet.h> // For inet_ntoa
#include <netinet/in.h>

void get_in_addr(struct sockaddr *sa,char *addressBuffer)
{
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)sa;
    inet_ntop(AF_INET, &(ipv4->sin_addr), addressBuffer, INET_ADDRSTRLEN);


    
}