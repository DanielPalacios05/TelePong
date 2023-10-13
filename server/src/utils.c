#include <arpa/inet.h> // For inet_ntoa
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <stdarg.h>

void get_in_addr(struct sockaddr *sa,char *addressBuffer)
{
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)sa;
    inet_ntop(AF_INET, &(ipv4->sin_addr), addressBuffer, INET_ADDRSTRLEN);
  
}

void concat(char * result, int num, ...) {
  va_list args;
  va_start(args, num);
  for (int i = 0; i < num; i++) {
    strcat(result, va_arg(args, char* ));
  }
  va_end(args);
}