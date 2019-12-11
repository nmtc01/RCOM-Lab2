/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Client header file
 */

#include "socket.h"

#define MAX_STRING_SIZE 40     // Max string size

typedef struct hostent host_t;

/* Get info from url argument */
int get_args(char *arg, char *user, char *pass, char *host, char *path);

/* Get filename from path */
int get_filename(char* path, char *filename);

/* Get ip of given host */
host_t *getip(char* host);

/* Open socket and connect with IP */
int start_connection(int *socket_fd, char* ip);

/* Login into server */
int login(int socket_fd, char* user, char* pass);

/* Change directory in server */
int change_directory(int socket_fd, char* path);
