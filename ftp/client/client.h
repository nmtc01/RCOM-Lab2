/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Client header file
 */

#include "socket.h"

#define MAX_STRING_SIZE 128     // Max string size

int get_args(int argc, char *argv[], char *filepath, char *username, char *password);
int start_connection(int *socket_fd);
