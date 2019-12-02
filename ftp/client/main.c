/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Client main file
 */

#include "client.h"

int main(int argc , char *argv[]) {
  int socket_fd;
  char *filepath = (char*)malloc(MAX_STRING_SIZE);
  char *username = (char*)malloc(MAX_STRING_SIZE);
  char *password = (char*)malloc(MAX_STRING_SIZE);

  // separate arguments
  get_args(argc, argv, filepath, username, password);

  // start of communication
  start_connection(&socket_fd);

  char buf[MAX_BUF_SIZE];
  receive_msg(socket_fd, buf);

  // end of communication
  close(socket_fd);
  exit(0);
}
