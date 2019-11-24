/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Server file
 */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SERVER_PORT 6000
#define SERVER_ADDR "192.168.28.96"

int open_socket(int domain, int type, int protocol);
void get_address(struct sockaddr_in *server_addr);
int bind_socket(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int main() {
	// open socket
  int network_socket = open_socket(AF_INET, SOCK_STREAM, 0);

	// create socket address
  struct sockaddr_in server_addr;
  get_address(&server_addr);

  // bind address to socket
  bind_socket(network_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));

  // listen and accept connections
  listen(network_socket, 5);
  int client_socket = accept(network_socket, NULL, NULL);

  // start of communication
  // use send()/recv() to send/receive data


  // end of communication
  close(network_socket);
  exit(0);
}

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
  server_addr->sin_port = htons(SERVER_PORT);            /*server TCP port must be network byte ordered */
  server_addr->sin_addr.s_addr = inet_addr(SERVER_ADDR); /*32 bit Internet address network byte ordered*/
}

int bind_socket(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  int ret = bind(sockfd, addr, addrlen);
  if(ret < 0){
    perror("Bind");
    exit(1);
  }
  return ret;
}
