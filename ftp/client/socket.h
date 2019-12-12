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
#include <libgen.h>

#define SERVER_PORT 21                  // port of socket
#define MAX_BUF_SIZE 512                // Max buffer size

/* Receive small message from server */
int receive_msg(int socket_fd);
int receive_msg_(int socket_fd, char* buf);

/* Send message to server */
int send_msg(int socket_fd, char *msg);

/* Receive file from server */
int receive_file(int socket_fd, char* filename);
