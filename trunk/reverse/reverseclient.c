/*
  reverseclient.c
  by liuw
  liuw@liuw.name
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netdb.h>

#include "reverse.h"

int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in server;
  struct hostent *host;
  int port, nbytes;
  char msg[BUFSIZ];
  char recvbuf[BUFSIZ];

  if (argc != 3) {
    fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((host = gethostbyname(argv[1])) == NULL) {
    fprintf(stderr, "gethostbyname() error\n");
    exit(EXIT_FAILURE);
  }

  port = atoi(argv[2]);
  if (port < 0 || port > 65535) {
    fprintf(stderr, "Invalid port number %d\n", port);
    exit(EXIT_FAILURE);
  }

  // create a socket
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "socket() error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  memset((void *)&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr = *((struct in_addr*)host->h_addr);

  // connect to server
  if (connect(sockfd, (struct sockaddr*)&server, 
	      sizeof(struct sockaddr)) == -1) {
    fprintf(stderr, "connect() error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  printf("Connected to server %s...\n", argv[1]);
  printf("Enter `%s' if you want to quit.\n", EXIT);
  memset((void *)msg, 0, BUFSIZ);
  memset((void *)recvbuf, 0, BUFSIZ);


  for (;;) {
    printf("%s", PROMPT);
    scanf("%s", msg);
    send(sockfd, msg, strlen(msg), 0);
    if (!strcmp(msg, EXIT)) 
      break;
    recv(sockfd, recvbuf, BUFSIZ, 0);
    printf("Server send: %s\n", recvbuf);
    memset((void *)msg, 0, BUFSIZ);
    memset((void *)recvbuf, 0, BUFSIZ);

  }

  close(sockfd);

  exit(EXIT_SUCCESS);
}
