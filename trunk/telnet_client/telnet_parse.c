/*
  telnet_parse.c
  by liuw
  liuw@liuw.name
*/
#include <string.h>
#include "rfc0854.h"
#include "telnet.h"

/* this routine acts as a parser. it response to the IAC control sequences and
   strip those control sequence off the buffer. this is just a simple
   implemetation, we simply response WONT to all negotiation request. if a
   control sequence is split between two calls of this routine, the static
   buffer can handle it correctly */
/* FIXME: why not try to negotiate with the server? because I have no idea about
   what to response and I am just too lazy to check those out. and if I am
   to handle all those request, I have to modify this routine since it only
   has a 4 byte static buffer for request without argument, that adds to my
   workload. Orz :( */
void telnet_parse(sock_t *sock)
{
  static unsigned char getrq[4];
  static int l = 0;
  unsigned char putrq[4], *buf = sock->recvq.pos;
  int i, *size = &sock->recvq.len, ref_size = *size, eat_chars = 0;

  /* if the socket object is NULL, assume a reset */
  if (sock == NULL) {
    l = 0;
    return;
  }

  /* loop all chars of the string */
  for (i = 0; i < ref_size; ++i) {
    /* if we found IAC char OR we are fetching a IAC code string, process it */
    if ((buf[i] != TELNET_IAC) && (l == 0))
      continue;

    /* copy the chars in the IAC-code-building buffer */
    getrq[l++] = buf[i];

    /* eat a char */
    eat_chars++;

    /* if this is the first char (IAC!) go straight to the next one */
    if (l == 1)
      continue;

    /* identify the IAC code. The effect is resolved here. If the char needs
       further data the subsection just needs to leave the index 'l' set */
    switch (getrq[1]) {
    case TELNET_SE:
    case TELNET_NOP:
      goto do_eat_chars;
    case TELNET_DM:
    case TELNET_BRK:
    case TELNET_IP:
    case TELNET_AO:
    case TELNET_AYT:
    case TELNET_EC:
    case TELNET_EL:
    case TELNET_GA:
    case TELNET_SB:
      goto do_eat_chars;
    case TELNET_WILL:
    case TELNET_WONT:
      if (l < 3) /* need more data */
        continue;

      /* refuse this option */
      putrq[0] = TELNET_IAC;
      putrq[1] = TELNET_DONT;
      putrq[2] = getrq[2];
      write(sock->fd, putrq, 3);
      goto do_eat_chars;
    case TELNET_DO:
    case TELNET_DONT:
      if (l < 3)
	continue;

      /* refuse this option */
      putrq[0] = 0xFF;
      putrq[1] = TELNET_WONT;
      putrq[2] = getrq[2];
      write(sock->fd, putrq, 3);
      goto do_eat_chars;
    case TELNET_IAC:
      /* insert a byte 255 (IAC) in the buffer. Note that we don't know in which
	 position we are, but there must be at least 1 eaten char where we
	 can park our data byte. */
      buf[i - --eat_chars] = 0xFF;
      goto do_eat_chars;
    default:
      /* FIXME: don't know how to handle unknown code, just leave it to screen */
      break;
    }
    continue;
    
  do_eat_chars:
    /* ... */
    l = 0;

    if (eat_chars > 0) {
      unsigned char *from, *to;

      /* move the index to the overlapper character */
      i++;

      /* if this is the end of the string, memmove() dose not care of a null
	 size, it simply does nothing. */
      from = &buf[i];
      to = &buf[i - eat_chars];
      memmove(to, from, ref_size - i);

      /* fix the index. since the loop will auto-increment the index we need
	 to put it one char before. this means that it can become negative
	 but it is not a big problem since it is singed. */
      i -= eat_chars + 1;
      ref_size -= eat_chars;
      eat_chars = 0;
    }
  }
  *size = ref_size - eat_chars;
}
  
