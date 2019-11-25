/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Client main file
 */

#include "client.h"

int main() {
	// open socket
  int network_socket = open_socket(AF_INET, SOCK_STREAM, 0);

	// create socket address
  struct sockaddr_in server_addr;
  get_address(&server_addr);

  // connect to socket
  connect_socket(network_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));

  // start of communication
  clt_comm(network_socket);

  // end of communication
  close(network_socket);
  exit(0);
}
