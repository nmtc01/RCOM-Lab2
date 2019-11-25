/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Client file
 */

#include "client.h"

int open_socket(int domain, int type, int protocol){
  int ret = socket(domain, type, protocol);
  if(ret < 0){
    perror("Connect");
    exit(1);
  }
  return ret;
}

void get_address(struct sockaddr_in *server_addr){
  bzero((char*)server_addr, sizeof(*server_addr));
  server_addr->sin_family = AF_INET;
  server_addr->sin_port = htons(SERVER_PORT);             /*server TCP port must be network byte ordered */
  server_addr->sin_addr.s_addr = INADDR_ANY;              /*32 bit Internet address network byte ordered*/
}

int connect_socket(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  int ret = connect(sockfd, addr, addrlen);
  if(ret < 0){
    perror("Connect");
    exit(1);
  }
  return ret;
}

int clt_comm(int client_socket){
  // use send()/recv() to send/receive data

  char data[DATA_SIZE];
  recv(client_socket, &data, DATA_SIZE, 0);
  printf("<Server> %s\n", data);
}