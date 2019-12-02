/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Socket header file
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
#include <string.h>
#include <fcntl.h>

#define SERVER_PORT 6000                // port of socket
#define SERVER_ADDR "192.168.28.96"     // Test ip
#define MAX_BUF_SIZE 512                // Max buffer size

// Open socket
int open_socket(int domain, int type, int protocol);
// Define socket properties
void get_address(struct sockaddr_in *server_addr);
// Connect socket to network
int connect_socket(int socket_fd, const struct sockaddr *addr, socklen_t addrlen);

// Connection

// Receive small message from server
int receive_msg(int socket_fd, char *buf);
// Send message to server
int send_msg(int socket_fd, char *msg);
// Receive file
int receive_file(int socket_fd, char* filename, int *filesize);
