/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Server header file
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <strings.h>

#define SERVER_PORT 6000
#define MAX_BUF_SIZE 256

int open_socket(int domain, int type, int protocol);
void get_address(struct sockaddr_in *server_addr);
int bind_socket(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int srv_comm(int client_socket);