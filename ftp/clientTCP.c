/*      (C)2000 FEUP  */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 6000
#define SERVER_ADDR "192.168.28.96"

int main() {
	// open socket
  int network_socket = open_socket(AF_INET, SOCK_STREAM, 0);

	// create socket address

  // connect to socket
  connect_socket(network_socket, (struct sockaddr*) &server_addr, sizeof(server_addr);

  close(network_socket);
  exit(0);
}

int open_socket(int domain, int type, int protocol){
  int ret = socket(domain, type, protocol);
  if(ret < 0){
    perror("Connect");
    exit(1);
  }
  return ret;
}

struct sockaddr_in get_address(){
  struct sockaddr_in server_addr;
  bzero((char*)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);            /*server TCP port must be network byte ordered */
  server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR); /*32 bit Internet address network byte ordered*/

  return server_addr;
}

int connect_socket(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  int ret = connect(sockfd, addr, addrlen);
  if(ret < 0){
    perror("Connect");
    exit(1);
  }
  return ret;
}
