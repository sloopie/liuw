/*
  reverseserver.c
  by liuw
  liuw@liuw.name
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/wait.h>

#include "reverse.h"

#define DEBUG 0

void sighandler(int signo)
{
  int status;
#ifdef DEBUG
  printf("Caught SIGCHLD\n");
#endif
  wait(&status);
}


void revstr(char *s)
{
  int len = strlen(s);
  char *tmp = malloc(len+1);
  int i;
  for (i = 0; i < len; i++)
    tmp[i] = s[len-i-1];
  tmp[i] = '\0';
  strcpy(s, tmp);
  free(tmp);
}

int main(int argc, char **argv)
{
  int sockfd, acc_fd;
  struct sockaddr_in server;
  struct sockaddr_in client;
  int sin_size, port;
  size_t nbytes;
  char buffer[BUFSIZ];

  signal(SIGCHLD, sighandler);

  if (argc != 2) {
    fprintf(stderr, "Usage: %s port\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  port = atoi(argv[1]);
  if (port < 0 || port > 65535) {
    fprintf(stderr, "Invalid port %d\n", port);
    exit(EXIT_FAILURE);
  }

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "socket() error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  memset((void *)&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(port);

  if (bind(sockfd, (struct sockaddr*)&server, 
	   sizeof(struct sockaddr)) == -1) {
    fprintf(stderr, "bind() error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  if (listen(sockfd, 5) == -1) {
    fprintf(stderr, "listen() error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  for (;;) {
    sin_size = sizeof(struct sockaddr_in);
    if ((acc_fd = accept(sockfd, (struct sockaddr*)&client, 
			 &sin_size)) == -1) {
      fprintf(stderr, "accept() error: %s\n",
	      strerror(errno));
      exit(EXIT_FAILURE);
    }
    int new_fd = acc_fd;
    if (fork() == 0) {
      for (;;) {
	printf("Connection from %s:%d\n", inet_ntoa(client.sin_addr),
	       ntohs(client.sin_port));
	if ((nbytes = recv(new_fd, buffer, BUFSIZ, 0)) == -1) {
	  fprintf(stderr, "recv() error: %s\n", strerror(errno));
	  exit(EXIT_FAILURE);
	}
	buffer[nbytes] = '\0';
	if (!strcmp(buffer, EXIT)) {
	  printf("Client %s:%d exited, goodbye\n", 
		 inet_ntoa(client.sin_addr), 
		 ntohs(client.sin_port));
	  exit(EXIT_SUCCESS);
	}
	printf("Client send: %s\n", buffer);
	revstr(buffer);
	send(new_fd, buffer, strlen(buffer), 0);

      }
    }
  }

  close(sockfd);

  exit(EXIT_SUCCESS);
}
