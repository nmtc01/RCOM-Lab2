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
  char file[MAX_STRING_SIZE]; memset(file, 0, MAX_STRING_SIZE);
  char ip[MAX_STRING_SIZE];
  char buf[MAX_BUF_SIZE];

  if(get_args(argv[1], user, pass, host, path, file)){
    printf("Usage: %s ftp://[<user>:<password>@]<host>/<path>\n", argv[0]);
    return -1;
  }

  if(getip(host, ip)){
    printf("Error getting ip.\n");
    return -1;
  }

  system("clear");
  printf(" ******************************************************\n");
  printf(" * User: %*s *\n", (MAX_STRING_SIZE + 4), user);
  printf(" * Pass: %*s *\n", (MAX_STRING_SIZE + 4), pass);
  printf(" * Host: %*s *\n", (MAX_STRING_SIZE + 4), host);
  printf(" * Path: %*s *\n", (MAX_STRING_SIZE + 4), path);
  printf(" * File: %*s *\n", (MAX_STRING_SIZE + 4), file);
  printf(" * IP  : %*s *\n", (MAX_STRING_SIZE + 4), ip);
  printf(" ******************************************************\n\n\n");

  if(start_connection(&socket_fd, ip, SERVER_PORT)){
    printf("Error connecting.\n");
  }

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
  int pasv_sock_fd;
  if(passive_mode(socket_fd, &pasv_sock_fd)){
    printf("Error in pasv.\n");
    return -1;
  }

  /* Send filename */
  if(send_filename(socket_fd, file)){
    printf("Error in retr.\n");
    return -1;
  }

  /* Receive file */
  receive_file(pasv_sock_fd, file);

  /* End of communication */
  close(socket_fd);
  close(pasv_sock_fd);

  return 0;
}
