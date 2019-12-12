/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Socket file
 */

#include "socket.h"

int receive_msg(int socket_fd){
  FILE* sock_file = fdopen(socket_fd, "r");
  if(sock_file == NULL){
    perror("receive");
    return -1;
  }

  char buf[MAX_BUF_SIZE];
  int n;

  while (buf[3] != ' ') {
    memset(buf, 0, MAX_BUF_SIZE);
    if(fgets(buf, MAX_BUF_SIZE, sock_file) == NULL) break;
    printf("%s", buf);
  }

  if(buf[0] == '5'){
    printf("Unexpected error.\n");
    exit(1);
  }

  return 0;
}

int receive_msg_(int socket_fd, char* buf){
  FILE* sock_file = fdopen(socket_fd, "r");
  if(sock_file == NULL){
    perror("receive");
    return -1;
  }

  int n;

  while (buf[3] != ' ') {
    memset(buf, 0, MAX_BUF_SIZE);
    if(fgets(buf, MAX_BUF_SIZE, sock_file) == NULL) break;
    printf("%s", buf);
  }

  return 0;
}

int send_msg(int socket_fd, char *buf){
  int n = write(socket_fd, buf, strlen(buf));
  if(n < 0){
    printf("Error on send msg.\n");
    return -1;
  }

  return 0;
}

int receive_file(int socket_fd, char *filename){
  // Create file
  int file_fd = creat(filename, 0777);
  if(file_fd < 0){
    perror("creat()");
    return -1;
  }

  // Read file
  char data[MAX_BUF_SIZE];
  int read_bytes, write_bytes;
  while ((read_bytes = read(socket_fd, data, MAX_BUF_SIZE))) {
    if(read_bytes < 0){
      perror("read()");
      return -1;
    }
    write_bytes = write(file_fd, data, MAX_BUF_SIZE);
    if(write_bytes < 0){
      perror("write()");
      return -1;
    }
  }

  close(file_fd);
  return 0;
}
