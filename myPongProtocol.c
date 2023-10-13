#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "constants.h"

int createClientSocket()
{
    int client_socket;
    struct sockaddr_in server_address;

    // Crear un socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }
    return client_socket;
}

int createServerSocket()
{
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if (server_socket == -1)
    {
        perror("Error al crear el socket");
    }

    // Configurar la dirección y el puerto en los que se escucharán los datagramas
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);       // Puerto deseado
    server_address.sin_addr.s_addr = INADDR_ANY; // Escuchar en todas las interfaces

    // Vincular el socket a la dirección y puerto
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Error al vincular el socket");
        close(server_socket);
    }
    return server_socket;
}

struct Player receivePlayer(int server_socket)
{
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    char read_data[BUFFER_SIZE];

    int bytes_read = recvfrom(server_socket, read_data, sizeof(read_data), 0, (struct sockaddr *)&client_address, &client_len);
    struct Player player;
    // Copiar los valores de client_address y client_len en player.address y player.address_len
    memcpy(&player.address, &client_address, sizeof(client_address));
    player.address_len = client_len;

    // Copiar el nickname desde read_data a player.nickname
    strncpy(player.nickname, read_data, sizeof(player.nickname) - 1);
    player.nickname[sizeof(player.nickname) - 1] = '\0'; // Asegurarse de que la cadena esté terminada con '\0'

    // Asignar valores adecuados a player.playerNum y player.playerPos según tu lógica
    player.playerNum = 0; // Por ejemplo, aquí se inicializa en 0
    player.playerPos = 0; // Por ejemplo, aquí se inicializa en 0
    player.gameId = 0;

    memset(read_data, 0, sizeof(read_data));

    return player;
}

void sendGameInfo(int server_socket, int playerNum, int gameId, struct sockaddr_storage address, socklen_t address_len)
{
    sendto(server_socket, &playerNum, sizeof(playerNum), 0, (struct sockaddr *)&address, address_len);
    sendto(server_socket, &gameId, sizeof(gameId), 0, (struct sockaddr *)&address, address_len);
}

void sendOpponent(int server_socket, char *nickname, struct Player player)
{
    sendto(server_socket, nickname, strlen(nickname) + 1, 0, (struct sockaddr *)&player.address, player.address_len);
}



void sockaddrStorageToString(const struct sockaddr_storage *addr, char* buffer) {

    if (addr->ss_family == AF_INET) {
        struct sockaddr_in *addr_in = (struct sockaddr_in *)addr;
        const char *ip_str = inet_ntoa(addr_in->sin_addr);

        if (ip_str != NULL) {
            snprintf(buffer, MAX_ADDR_LEN, "%s:%d", ip_str, ntohs(addr_in->sin_port));
        }
    } else {
        snprintf(buffer, MAX_ADDR_LEN, "Dirección desconocida");
    }
}




char *socklen_tToCString(socklen_t *client_len) {
    char *len_str  = malloc(sizeof(char*)*20); // Declaración de una cadena para almacenar el valor convertido
    // Utiliza sprintf para convertir el valor de len a una cadena
    sprintf(len_str, "%lu", (unsigned long)client_len);
    // Maneja otros tipos de direcciones según sea necesario
    return len_str;
}

struct sockaddr_storage resolveAddress(char *token){

    char* colon_position = strchr(token, ':');
    if (colon_position == NULL) {
        fprintf(stderr, "Error: Cadena no válida\n");
    }

    *colon_position = '\0'; // Reemplazar ':' por un carácter nulo

    char* ip_str = token;
    char* port_str = colon_position + 1;
    printf("IP: %s - PORT: %s", ip_str, port_str);

    struct addrinfo *converted_address;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // Puede ser AF_INET para IPv4 o AF_INET6 para IPv6
    hints.ai_socktype = SOCK_DGRAM;
    printf("Antes del getaddr.... \n");
    int err = getaddrinfo(ip_str, port_str, &hints, &converted_address);

    if (err != 0)
    {
        fprintf(stderr, "Error en getaddrinfo: %s\n", gai_strerror(err));
    }

    struct sockaddr_storage address;

    if (converted_address != NULL)
    {
        memcpy(&address, converted_address->ai_addr, converted_address->ai_addrlen);
        freeaddrinfo(converted_address); // Libera la memoria asignada por getaddrinfo
    }
    else
    {
        fprintf(stderr, "La resolución de dirección falló.\n");
        // Aquí puedes manejar el error de resolución según sea necesario
    }
    return address;
}




struct Response handleCommunication(char *message)
{
    char *message2 = message;
    char input[1000];
    strcpy(input, message2);
    char *token;

    // Uso de strtok para dividir la cadena en subcadenas
    token = strtok(input, " ");
    if (strcmp(token, "PLAYER") == 0)
    {
        printf("Hemos recibido PLAYER\n");
        token = strtok(NULL, " ");
        if (strcmp(token, "CREATE") == 0)
        {
            printf("Hemos recibido el CREATE\n");
            token = strtok(NULL, " ");
            printf("Hemos recibido al jugador: %s\n", token);
        }
        else if (strcmp(token, "RECEIVE") == 0)
        {
            printf("Hemos recibido el RECEIVE\n");
            token = strtok(NULL, " ");
            int socket = atoi(token);
            struct Response response;
            response.player = receivePlayer(socket);
            printf("Hemos recibido al jugador: %s\n", response.player.nickname);
            sockaddrStorageToString(&response.player.address,response.address);
            strncpy(response.player.addressText, response.address, sizeof(response.player.addressText));
            printf("Sin error !!\n");
            
            strncpy(response.client_len, socklen_tToCString(&response.player.address_len), sizeof(response.client_len));
            strncpy(response.player.addressLenText, response.client_len, sizeof(response.player.addressLenText));

            return response;
        }
        else if (strcmp(token, "DELETE") == 0)
        {
            printf("Hemos recibido el DELETE\n");
            token = strtok(NULL, " ");
            char *juego = token;
            printf("Hemos recibido al juego: %s\n", token);
            token = strtok(NULL, " ");
            char *jugador = token;
            printf("Hemos recibido al jugador: %s\n", token);
            printf("Hemos recibido al juego: %s, con el jugador: %s\n", juego, jugador);
        }
    }
    else if (strcmp(token, "SERVER") == 0)
    {

        printf("Hemos recibido SERVER\n");
        token = strtok(NULL, " ");
        if (strcmp(token, "CREATE_SOCKET") == 0)
        {
            printf("Hemos recibido el CREATE_SOCKET\n");
            int socket = createServerSocket();
            struct Response response;
            response.server_socket = socket;
            return response;
        }
        else if (strcmp(token, "GAME_INFO") == 0)
        {
            printf("Hemos recibido el GAME_INFO\n");
            token = strtok(NULL, " ");
            int socket = atoi(token);

            token = strtok(NULL, " ");
            int playerNum = atoi(token);
            printf(" Este es el número sacado %d    |||\n", playerNum);

            token = strtok(NULL, " ");
            int gameId = atoi(token);

            token = strtok(NULL, " ");
            printf("Ha llegado hasta aca.... \n");
            
            struct sockaddr_storage address = resolveAddress(token);
            printf("Ha llegado hasta aca 22.... \n");
            socklen_t address_len = sizeof(address);

            sendGameInfo(socket, playerNum, gameId, address, address_len);
        }
    }
}
