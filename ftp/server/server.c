/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Server file
 */

#include "server.h"

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
  server_addr->sin_port = htons(SERVER_PORT);             /*server TCP port must be network byte ordered */
  server_addr->sin_addr.s_addr = INADDR_ANY;              /*32 bit Internet address network byte ordered*/
}

int bind_socket(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  int ret = bind(sockfd, addr, addrlen);
  if(ret < 0){
    perror("Bind");
    exit(1);
  }
  return ret;
}

int srv_comm(int client_socket){
  // use send()/recv() to send/receive data

  char msg[MAX_BUF_SIZE] = "Start of connection.";
  send(client_socket, msg, sizeof(msg), 0);

  /*  Plan:
      1. receive request with username, password and file
      2. send green light, start packet followed by file, followed by end packet
         or send red light
      3. close
  */
}