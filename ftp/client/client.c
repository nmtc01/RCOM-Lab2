/* RCOM 2019/2020
 * Joao Campos and Nuno Cardoso
 * Client file
 */

#include "client.h"

int get_args(char *arg, char *user, char *pass, char *host, char *path){
  //    ftp://[<user>:<password>@]<host>/<url-path>

  char length = strlen(arg);
  char start[] = "ftp://";
  int state = 0, j = 0;


  for(int i = 0; i < length; i++){
    switch (state) {
      // Check ftp://
      case 0:
        if(i < strlen(start) - 1){
          if(start[i] == arg[i]) break;
        }
        if(i == strlen(start) - 1){
          if(start[i] == arg[i]){
            state = 1;
            break;
          }
        }

        printf("Error parsing ftp://\n");
        exit(1);
        break;
      // Get user
      case 1:
        if(arg[i] == ':'){
          state = 2;
          j = 0;
          break;
        }
        user[j] = arg[i];
        j++;

        break;
      // Get pass
      case 2:
        if(arg[i] == '@'){
          state = 3;
          j = 0;
          break;
        }
        pass[j] = arg[i];
        j++;

        break;
      // Get host
      case 3:
        if(arg[i] == '/'){
          state = 4;
          j = 0;
          break;
        }
        host[j] = arg[i];
        j++;

        break;
      // Get path
      case 4:
        path[j] = arg[i];
        j++;

        break;

      default:
        printf("Error parsing argument\nUsage: download ftp://[<user>:<password>@]<host>/<url-path>");
        exit(1);
        break;
    }
  }

  return 0;
}

int get_filename(char* path, char *filename){
  char* file_name = basename(path);
  strcpy(filename, file_name);
  return 0;
}

host_t *getip(char* host){
  host_t *h;
  if((h = gethostbyname(host)) == NULL){
    perror("gethostbyname");
    exit(1);
  }
  return h;
}

int start_connection(int *socket_fd, char* ip){
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
  server_addr.sin_port = htons(SERVER_PORT);

  // connect to socket
  if(connect(*socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
    perror("connect");
    exit(2);
  }

  return 0;
}

int login(int socket_fd, char* user, char* pass){
  char buf[MAX_BUF_SIZE];
  char res[MAX_BUF_SIZE];

  /* Send username */
  memset(buf, 0, MAX_BUF_SIZE);
  sprintf(buf, "USER %s\r\n", user);
  printf("USER %s\r\n", user);
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
  printf("PASS %s\r\n", pass);
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
  sprintf(buf, "CWD %s\r\n", dirname(path));
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
