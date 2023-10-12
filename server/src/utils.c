#include <arpa/inet.h> // For inet_ntoa
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

void get_in_addr(struct sockaddr *sa,char *addressBuffer)
{
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)sa;
    inet_ntop(AF_INET, &(ipv4->sin_addr), addressBuffer, INET_ADDRSTRLEN);
  
}
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}