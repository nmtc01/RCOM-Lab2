/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Socket file
 */

#include "socket.h"

int open_socket(int domain, int type, int protocol){
  int ret = socket(domain, type, protocol);
  if(ret < 0){
    perror("Open");
    exit(1);
  }
  return ret;
}

void get_address(struct sockaddr_in *server_addr){
  bzero((char*)server_addr, sizeof(*server_addr));
  server_addr->sin_family = AF_INET;
  server_addr->sin_port = htons(SERVER_PORT);                         /*server TCP port must be network byte ordered */
  server_addr->sin_addr.s_addr = inet_addr(SERVER_ADDR);               /*32 bit Internet address network byte ordered*/
}

int connect_socket(int socket_fd, const struct sockaddr *addr, socklen_t addrlen){
  int ret = connect(socket_fd, addr, addrlen);
  if(ret < 0){
    perror("Connect");
    exit(1);
  }
  return ret;
}

int receive_msg(int socket_fd, char *buf){
  memset(buf, 0, MAX_BUF_SIZE);
  int n = read(socket_fd, buf, MAX_BUF_SIZE);
  if(n < 0){
    printf("Error on receive msg.\n");
    return -1;
  }
  return n;
}

int send_msg(int socket_fd, char *buf){
  memset(buf, 0, MAX_BUF_SIZE);
  int n = write(socket_fd, buf, MAX_BUF_SIZE);
  if(n < 0){
    printf("Error on send msg.\n");
    return -1;
  }
  return n;
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
