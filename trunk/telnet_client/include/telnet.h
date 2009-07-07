/*
  telnet.h
  by liuw
  liuw@liuw.name
*/

#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXHOSTNAMELEN 256
#define MAXINETADDRS 6
#define ADDRSTRLEN 16

#define STDIN_FILENO 0
#define STDOUT_FILENO 1

#define TRUE 1
#define FALSE 0

#define bool unsigned char

typedef struct {
  unsigned char *head;
  unsigned char *pos;
  int len;
} buffer_t;



typedef struct {
  int fd;
  struct sockaddr_in  rhost;
  short port;
  buffer_t sendq, recvq;
} sock_t;
