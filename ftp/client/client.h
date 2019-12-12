/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Client header file
 */

#include "socket.h"

#define MAX_STRING_SIZE 40     // Max string size

typedef struct hostent host_t;

/* Get info from url argument */
int get_args(char *arg, char *user, char *pass, char *host, char *path, char* file);

/* Get filename from path */
int get_filename(char* path, char *filename);

/* Get ip of given host */
int getip(char* host, char* ip);

/* Open socket and connect with IP */
int start_connection(int *socket_fd, char* ip, int port);

/* Login into server */
int login(int socket_fd, char* user, char* pass);

/* Change directory in server */
int change_directory(int socket_fd, char* path);

/* Enter passive mode */
int passive_mode(int socket_fd, int* pasv_sock_fd);

/* Send filename */
int send_filename(int socket_fd, char* filename);
