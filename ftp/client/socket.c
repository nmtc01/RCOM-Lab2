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

  return 0;
}

int send_msg(int socket_fd, char *buf){
  int n = write(socket_fd, buf, MAX_BUF_SIZE);
  if(n < 0){
    printf("Error on send msg.\n");
    return -1;
  }

  return 0;
}

int receive_file(int socket_fd, char *filename, int *filesize){
  // Create file
  int file_fd = creat(filename, 0777);
  if(file_fd < 0){
    perror("Receive File");
    return -1;
  }

  // get file size
  read(socket_fd, filesize, sizeof(int));

  // get file
  char data[MAX_BUF_SIZE];
  int read_bytes;
  while ((read_bytes = read(socket_fd, data, MAX_BUF_SIZE)) != 0) {
    if(read_bytes < 0){
      perror("Read file");
      exit(1);
    }
    write(file_fd, data, MAX_BUF_SIZE);
  }

  close(file_fd);
  return 0;
}
