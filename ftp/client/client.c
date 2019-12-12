/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Client file
 */

#include "client.h"

int get_args(char *arg, char *user, char *pass, char *host, char *path, char* file){
  // ftp://[<user>:<password>@]<host>/<path>

  char* start = "ftp://";
  char* url = malloc(strlen(arg));

  strcpy(url, arg);
  // Check start ftp://
  if(strncmp(url, start, strlen(start))){
    printf("Invalid url.");
    return -1;
  }
  url += strlen(start);

  if(strchr(url, ':') != NULL){
    // Read username
    while (*url != ':') {
      strncat(user, url, 1);
      url++;
    }
    url++;

    // Read password
    while (*url != '@') {
      strncat(pass, url, 1);
      url++;
    }
    url++;
  } else {
    strcpy(user, "anonymous");
    strcpy(pass, "");
  }

  // Read host
  while (*url != '/') {
    strncat(host, url, 1);
    url++;
  }
  url++;

  // Read path
  strncpy(path, url, strrchr(url, '/')-url);

  // Read filename
  strcpy(file, strrchr(url, '/')+1);

  return 0;
}

int get_filename(char* path, char *filename){
  char* file_name = basename(path);
  strcpy(filename, file_name);
  return 0;
}

int getip(char* host, char* ip){
  host_t *h;
  if((h = gethostbyname(host)) == NULL){
    perror("gethostbyname");
    return -1;
  }

  strcpy(ip, inet_ntoa(*((struct in_addr *)h->h_addr)));

  return 0;
}

int start_connection(int *socket_fd, char* ip, int port){
  // open socket
  if((*socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(2);
  }

  // create socket address
  struct sockaddr_in server_addr;
  bzero((char*)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(ip);
  server_addr.sin_port = htons(port);

  // connect to socket
  if(connect(*socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
    perror("connect");
    exit(2);
  }

  printf("Connected %s:%d\r\n", ip, port);

  return 0;
}

int login(int socket_fd, char* user, char* pass){
  char buf[MAX_BUF_SIZE];
  char res[MAX_BUF_SIZE];

  /* Send username */
  memset(buf, 0, MAX_BUF_SIZE);
  sprintf(buf, "USER %s\r\n", user);
  printf("%s", buf);
  if(send_msg(socket_fd, buf)){
    printf("Error sending username.\n");
    return -1;
  }

  /* Receive response */
  if(receive_msg(socket_fd)){
    printf("Error reading username response.\n");
    return -1;
  }

  /* Send password */
  memset(buf, 0, MAX_BUF_SIZE);
  sprintf(buf, "PASS %s\r\n", pass);
  printf("%s", buf);
  if(send_msg(socket_fd, buf)){
    printf("Error sending password.\n");
    return -1;
  }

  /* Receive response */
  if(receive_msg(socket_fd)){
    printf("Error reading password response.\n");
    return -1;
  }

  return 0;
}

int change_directory(int socket_fd, char* path){
  char buf[MAX_BUF_SIZE];
  char res[MAX_BUF_SIZE];

  /* Send cwd */
  memset(buf, 0, MAX_BUF_SIZE);
  sprintf(buf, "CWD %s\r\n", path);
  printf("%s", buf);
  if(send_msg(socket_fd, buf)){
    printf("Error sending cwd.\n");
    return -1;
  }

  /* Receive response */
  if(receive_msg(socket_fd)){
    printf("Error reading cwd response.\n");
    return -1;
  }

  return 0;
}

int passive_mode(int socket_fd, int* pasv_sock_fd){
  char buf[MAX_BUF_SIZE];
  char res[MAX_BUF_SIZE];

  /* Send pasv */
  memset(buf, 0, MAX_BUF_SIZE);
  sprintf(buf, "PASV\r\n");
  printf("%s", buf);
  if(send_msg(socket_fd, buf)){
    printf("Error sending pasv.\n");
    return -1;
  }

  /* Receive response */
  if(receive_msg_(socket_fd, res)){
    printf("Error reading pasv response.\n");
    return -1;
  }

  char pasv[1024];
  memset(pasv, 0, MAX_BUF_SIZE);
  int ip1,ip2,ip3,ip4,port1,port2,port;
  sscanf(res, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)",&ip1,&ip2,&ip3,&ip4,&port1,&port2);

  sprintf(pasv, "%d.%d.%d.%d",ip1,ip2,ip3,ip4);
  port = port1 * 256 + port2;

  start_connection(pasv_sock_fd, pasv, port);

  return 0;
}

int send_filename(int socket_fd, char* filename){
  char buf[MAX_BUF_SIZE];
  char res[MAX_BUF_SIZE];

  /* Send cwd */
  memset(buf, 0, MAX_BUF_SIZE);
  sprintf(buf, "RETR %s\r\n", filename);
  printf("%s", buf);
  if(send_msg(socket_fd, buf)){
    printf("Error sending retr.\n");
    return -1;
  }

  /* Receive response */
  if(receive_msg(socket_fd)){
    printf("Error reading retr response.\n");
    return -1;
  }

  return 0;
}
