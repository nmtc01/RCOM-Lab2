/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Client main file
 */

#include "client.h"

int main(int argc , char *argv[]) {
  int socket_fd;
  host_t *h;
	struct sockaddr_in server_addr;
  char user[MAX_STRING_SIZE]; memset(user, 0, MAX_STRING_SIZE);
  char pass[MAX_STRING_SIZE]; memset(pass, 0, MAX_STRING_SIZE);
  char host[MAX_STRING_SIZE]; memset(host, 0, MAX_STRING_SIZE);
  char path[MAX_STRING_SIZE]; memset(path, 0, MAX_STRING_SIZE);
  char filename[MAX_STRING_SIZE]; memset(filename, 0, MAX_STRING_SIZE);
  char buf[MAX_BUF_SIZE];

  get_args(argv[1], user, pass, host, path);
  get_filename(path, filename);
  h = getip(host);

  if(!strlen(user)){
    strcpy(user, "anonymous");
    strcpy(pass, "");
  }

  system("clear");
  printf(" ******************************************************\n");
  printf(" * User: %*s *\n", (MAX_STRING_SIZE + 4), user);
  printf(" * Pass: %*s *\n", (MAX_STRING_SIZE + 4), pass);
  printf(" * Host: %*s *\n", (MAX_STRING_SIZE + 4), host);
  printf(" * Path: %*s *\n", (MAX_STRING_SIZE + 4), path);
  printf(" * File: %*s *\n", (MAX_STRING_SIZE + 4), filename);
  printf(" * IP  : %*s *\n", (MAX_STRING_SIZE + 4), inet_ntoa(*((struct in_addr *)h->h_addr)));
  printf(" ******************************************************\n\n\n");

  start_connection(&socket_fd, inet_ntoa(*((struct in_addr *)h->h_addr)));

  /* Receive opening message */
  if(receive_msg(socket_fd)){
    printf("Error reading opening message.\n");
    return -1;
  }

  /* Login */
  if(login(socket_fd, user, pass)){
    printf("Error in login.\n");
    return -1;
  }

  /* Change directory */
  if(change_directory(socket_fd, path)){
    printf("Error in cwd.\n");
    return -1;
  }

  /* Passive mode */

  /* Send filename */

  /* Receive file */


  /* End of communication */
  close(socket_fd);

  return 0;
}
