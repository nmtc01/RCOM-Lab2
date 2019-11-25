/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Server main file
 */

#include "server.h"

int main() {
	// open socket
  int network_socket = open_socket(AF_INET, SOCK_STREAM, 0);

	// create socket address
  struct sockaddr_in server_addr;
  get_address(&server_addr);

  // bind address to socket
  bind_socket(network_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));

  // listen and accept connection
  listen(network_socket, 1);
  int client_socket = accept(network_socket, NULL, NULL);

  // start of communication
  srv_comm(client_socket);

  // end of communication
  close(network_socket);
  exit(0);
}