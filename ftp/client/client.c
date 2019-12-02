/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Client file
 */

#include "client.h"

int get_args(int argc, char *argv[], char *filepath, char *username, char *password){
  memset(filepath, 0, MAX_STRING_SIZE);
  memset(username, 0, MAX_STRING_SIZE);
  memset(password, 0, MAX_STRING_SIZE);

  int user_defined = 0;
  int pass_defined = 0;

  for(int i = 1; i < argc; i++){
    if(argv[i] == "-u") {
      i++;
      username = argv[i];
      user_defined = 1;
      continue;
    } else if (argv[i] == "-p") {
      i++;
      password = argv[i];
      pass_defined = 1;
      continue;
    } else {
      filepath = argv[i];
    }
  }

  if(filepath == NULL){
    printf("No file path defined.\n");
    exit(1);
  }

  if(!user_defined){
    printf("Anonymous mode.\n");
    strcpy(username, "anonymous");
    strcpy(password, "");
    return 0;
  }

  if(!pass_defined){
    printf("No password.\n");
    strcpy(password, "");
  }

  return 0;
}

int start_connection(int *socket_fd){
  // open socket
  *socket_fd = open_socket(AF_INET, SOCK_STREAM, 0);

  // create socket address
  struct sockaddr_in server_addr;
  //get_address(&server_addr);
  bzero((char*)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);               /*32 bit Internet address network byte ordered*/
  server_addr.sin_port = htons(SERVER_PORT);                          /*server TCP port must be network byte ordered */

  // connect to socket
  connect_socket(*socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));

  return 0;
}
