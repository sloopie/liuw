/*
  main.c: telnet client main functions
  by liuw
  liuw@liuw.name
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <assert.h>
#include <getopt.h>
#include "telnet.h"

/* global definitions here, use to control process */
bool got_sigterm = FALSE;	/* when this is TRUE the application MUST exit */
bool got_sigint = FALSE;	/* when this is TRUE the application SHOULD exit */

/* got_int: signal handler for SIGINT */
static void got_int(int sig)
{
  got_sigint = TRUE;
}

/* got_term: signal handler for SIGTERM */
static void got_term(int sig)
{
  got_sigterm = TRUE;
}



/* main: entry point of program. set up some variable, get host information,
   then pass control to readwrite() */
int main(int argc, char **argv)
{
  int c;
  char *hostname;
  sock_t sock;
  struct hostent *host;
  struct sigaction sv;
  
  memset(&sock, 0, sizeof(sock_t));
  
  /* parse command line options */
  while (TRUE) {
    int optidx = 0;
    static const struct option long_options[] = {
      {"port", 		required_argument, NULL, 'p'},
      {"hostname", 	required_argument, NULL, 'h'},
      {0, 0, 0, 0 }
    };

    c = getopt_long(argc, argv, "p:h:", long_options, &optidx);

    if (c == -1)
      break;

    switch (c) {
    case 'p':
      sock.port = atoi(optarg);
      break;
    case 'h':
      hostname = optarg;
      break;
    }
  }

  /* set up the signal handling system, use new style routine sigaction()
     instead of signal() */
  sigemptyset(&sv.sa_mask);
  sv.sa_flags = 0;
  sv.sa_handler = got_int;
  sigaction(SIGINT, &sv, NULL);
  sv.sa_handler = got_term;
  sigaction(SIGTERM, &sv, NULL);

   
  /* misc process, no need to explain */
  if ((host = gethostbyname(hostname)) == NULL) {
    fprintf(stderr, "gethostbyname() error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  /* create a socket */
  sock.fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock.fd == -1) {
    fprintf(stderr, "socket() error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  memset((void *)&sock.rhost, 0, sizeof(struct sockaddr_in));
  sock.rhost.sin_family = AF_INET;
  sock.rhost.sin_port = htons(sock.port);
  sock.rhost.sin_addr = *((struct in_addr *) host->h_addr);

  /* don't leave the socket in a TIME_WAIT state if we close the connection */
  struct linger fix_ling;
  fix_ling.l_onoff = 1;
  fix_ling.l_linger = 0;
  if (setsockopt(sock.fd, SOL_SOCKET, SO_LINGER, &fix_ling, sizeof(fix_ling))
      < 0) {
    fprintf(stderr, "setsockopt error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  /* connect to remote server */
  if (connect(sock.fd, (struct sockaddr *)&sock.rhost, sizeof(struct sockaddr))
      == -1) {
    fprintf(stderr, "connect() error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  /* pass control to interactive read write function */
  readwrite(&sock);

  return 0;
}

/* readwrite: handle read and write, in this program, we are reading from
   stdin and write to remote host via a socket */
int readwrite(sock_t *sock)
{
  sock_t *dummy = (sock_t *) malloc(sizeof(sock_t));
  int read_ret, write_ret;
  int fd_sock, fd_stdin, fd_stdout, fd_max;
  unsigned char buf[BUFSIZ];
  bool inloop = TRUE;
  fd_set ins, outs;	/* we need select() here... */
  struct timeval delayer;

  fd_stdin = STDIN_FILENO;
  fd_stdout = STDOUT_FILENO;
  /* dummy sock_t, we need it to manage a queue */
  memset(dummy, 0, sizeof(sock_t));
  /* find out max fd + 1 */
  fd_max = (fd_stdin > fd_sock ? fd_stdin : fd_sock) + 1;
  /* don't block select(), make it fast :) */
  delayer.tv_sec = 0;
  delayer.tv_usec = 0;

  /* sock MUST NOT be null */
  assert(sock);

  /* for convenience */
  fd_sock = sock->fd;
  assert(fd_sock > 0);

  while (inloop) {
    bool call_select = TRUE;

    /* if we recevied an interrupt signal break this function */
    if (got_sigint) {
      got_sigint = FALSE;
      break;
    }

    /* if we received a terminating signal we must terminate */
    if (got_sigterm)
      break;

    /* reset ins and outs */
    FD_ZERO(&ins);
    FD_ZERO(&outs);

    /* if the receiving queue is not empty it means that something bad is
       happening (for example the target sending queue is delaying the output
       and so requires some more time to free up. */
    if (sock->recvq.len == 0) {
      FD_SET(fd_sock, &ins);	/* good, add it to ins */
    }else
      call_select = FALSE;	/* oh no, don't select() it for now */

    /* also set the dummy sock_t */
    if (dummy->recvq.len == 0) {
      FD_SET(fd_stdin, &ins);
    }else
      call_select = FALSE;

    /* now the send queue. when the socket buffer is full, it is not writable */
    if (sock->sendq.len > 0) {
      if ((delayer.tv_sec == 0) && (delayer.tv_usec == 0)) {
	FD_SET(fd_sock, &outs);
	call_select = TRUE;
      }
    }



    if (call_select || delayer.tv_sec || delayer.tv_usec) {
      int ret;
      ret = select(fd_max, &ins, &outs, NULL,
		   (delayer.tv_sec || delayer.tv_usec ? &delayer : NULL));

      if (ret < 0) {
	if (errno == EINTR)      	/* something wrong (maybe a legal
					   signal) */
	  goto handle_signal;
	perror("select(readwrite)");
	exit(EXIT_FAILURE);
      }else if (ret == 0) {		/* time expired */
	delayer.tv_sec = 0;
	delayer.tv_usec = 0;
      }

      call_select = TRUE;
    }

    /* reading from stdin the incoming data. the data is currently in the
       kernel's receiving queue, and in this session we move that data to our
       own receiving queue, located in the socket object. we can be sure that
       this queue is empty now because otherwise this fd would'nt have been
       watched. */
    if (call_select && FD_ISSET(fd_stdin, &ins)) {
      read_ret = read(fd_stdin, buf, sizeof(buf));

      if (read_ret < 0) {
	perror("read(stdin)");
	exit(EXIT_FAILURE);
      }else if (read_ret != 0) {
	dummy->recvq.len = read_ret;
	dummy->recvq.head = NULL;
	dummy->recvq.pos = buf;
      }
    }

    /* for optimazation reasons we have a common buffer for both receiving
       queues, because of this, handle the data now so the buffer is available
       for the other socket events. */
    if (dummy->recvq.len > 0) {
      buffer_t *my_recvq = &dummy->recvq;
      buffer_t *rem_sendq = &sock->sendq;

      /* if the remote send queue is empty, move there the entire data block */
      if (rem_sendq->len == 0) {
	memcpy(rem_sendq, my_recvq, sizeof(*rem_sendq));
	memset(my_recvq, 0, sizeof(*my_recvq));
      } else if (!my_recvq->head) {
	/* move the data block in a dedicated allocated space */
	my_recvq->head = malloc(my_recvq->len);
	memcpy(my_recvq->head, my_recvq->pos, my_recvq->len);
	my_recvq->pos = my_recvq->head;
      }
    }

    /* now handle the dummy sendq because of the same reason as above. there
       could be a common buffer that moves around the queues, so if this is the
       case handle it so that it can be reused. if we must delay it some more,
       copy it in a dynamically allocated space. */
    if (sock->sendq.len > 0) {
      unsigned char *data = sock->sendq.pos;
      int data_len = sock->sendq.len;
      buffer_t *my_sendq = &sock->sendq;

      write_ret = write(fd_sock, data, data_len);
      if (write_ret < 0) {
	if (errno == EAGAIN)
	  write_ret = 0;	/* write would block, append it to select() */
	else {
	  perror("write(net)");
	  exit(EXIT_FAILURE);
	}
      }

      /* update the queue */
      my_sendq->len -= data_len;
      my_sendq->pos += data_len;


      if (my_sendq->len == 0) {
	free(my_sendq->head);
	memset(my_sendq, 0, sizeof(*my_sendq));
      }else if (!my_sendq->head) {
	my_sendq->head = malloc(my_sendq->len);
	memcpy(my_sendq->head, my_sendq->pos, my_sendq->len);
	my_sendq->pos = my_sendq->head;
      }
    }				/* end of reading from stdin section */

    /* reading from the socket (net). */
    if (call_select && FD_ISSET(fd_sock, &ins)) {
      read_ret = read(fd_sock, buf, sizeof(buf));

      if (read_ret < 0) {
	perror("read(net)");
	exit(EXIT_FAILURE);
      }else if (read_ret == 0) {
	inloop = FALSE; /* EOF received from the net */
      } else {
	sock->recvq.len = read_ret;
	sock->recvq.head = NULL;
	sock->recvq.pos = buf;
      }
    }

    /* handle net receiving queue */
    if (sock->recvq.len > 0) {
      buffer_t *my_recvq = &sock->recvq;
      buffer_t *rem_sendq = &dummy->sendq;

      /* parse telnet code */
      telnet_parse(sock);

      /* the telnet parsing could have returned 0 chars! */
      if (my_recvq->len > 0) {
	/* if the remote send queue is empty, move there the entire data block */
	if (rem_sendq->len == 0) {
	  memcpy(rem_sendq, my_recvq, sizeof(*rem_sendq));
	  memset(my_recvq, 0, sizeof(*my_recvq));
	} else if (!my_recvq->head) {
	  /* move the data block in a dedicated allocated space */
	  my_recvq->head = malloc(my_recvq->len);
	  memcpy(my_recvq->head, my_recvq->pos, my_recvq->len);
	  my_recvq->pos = my_recvq->head;
	}
      }
    }

    if (dummy->sendq.len > 0) {
      unsigned char *data = dummy->sendq.pos;
      int data_len = dummy->sendq.len;
      buffer_t *my_sendq = &dummy->sendq;

      write_ret = write(fd_stdout, data, data_len);

      if (write_ret < 0) {
	perror("write(stdout)");
	exit(EXIT_FAILURE);
      }

      /* FIXME: unhandled exception */
      assert((write_ret > 0) && (write_ret <= data_len));

      if (write_ret < data_len) {
	data_len = write_ret;
      }

      /* update the queue */
      my_sendq->len -= data_len;
      my_sendq->pos += data_len;

      if (my_sendq->len == 0) {
	free(my_sendq->head);
	memset(my_sendq, 0, sizeof(*my_sendq));
      } else if (!my_sendq->head) {
	my_sendq->head = malloc(my_sendq->len);
	memcpy(my_sendq->head, my_sendq->pos, my_sendq->len);
	my_sendq->pos = my_sendq->head;
      }
    }			        /* end of reading from socket section */

  handle_signal:		/* just ignore user signals */
    continue;
  }				/* end of while (inloop) */

  /* we've got and EOF from the net, close the sockets */
  shutdown(fd_sock, SHUT_RDWR);
  close(fd_sock);
  sock->fd = -1;

  /* just leave dummy sock_t */
  free(dummy);
  return 0;
}
