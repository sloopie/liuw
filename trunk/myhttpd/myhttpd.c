/* MyHttpd: a small httpd to serve static content
 *
 * Author: LIU Wei <liuw # liuw.name>
 * version: 0.5
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#define PAGE_LEN_LIMIT 10240000

enum { PLAIN, HTML, JPEG, PNG, GIF, CSS, BMP, CGI };
enum { GET, POST, PUT };

void print_usage();
ssize_t read_line(int, char *, size_t, int);
static void sighandler(int);

int sockfd;

int main(int argc, char **argv)
{
  int pid;
  int port;
  char *workdir, cwd[1000];
  int i, nread;
  char str_port[6];
  
  struct sockaddr_in cliaddr, servaddr;
  int newsockfd;

  if (signal(SIGINT, sighandler) == SIG_ERR)
    fprintf(stderr, "cannot catch SIGINT\n");

  if (argc != 3) {
    print_usage();
    exit(1);
  }

  port = atoi(argv[1]);
  workdir = argv[2];

  if (chdir(workdir)) {
    fprintf(stderr, "failed to change server root to %s\n", workdir);
    exit(1);
  }
  getcwd(cwd, 1000);

  setenv("SERVER_SOFTWARE", "MyHttpd/0.0.1", 1);
  setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
  setenv("SERVER_NAME", "localhost", 1);
  sprintf(str_port, "%d", port);
  str_port[5] = '\0';
  setenv("SERVER_PORT", str_port, 1);

  char header_plain[] =
    "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n";
  char header_html[] =
    "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n";
  char header_jpeg[] =
    "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nConnection: close\r\n\r\n";
  char header_png[] =
    "HTTP/1.1 200 OK\r\nContent-Type: image/png\r\nConnection: close\r\n\r\n";
  char header_gif[] =
    "HTTP/1.1 200 OK\r\nContent-Type: image/gif\r\nConnection: close\r\n\r\n";
  char header_css[] =
    "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\nConnection: close\r\n\r\n";
  char header_bmp[] =
    "HTTP/1.1 200 OK\r\nContent-Type: image/bmp\r\nConnection: close\r\n\r\n";
  char header_ok[] = "HTTP/1.1 200 OK\r\n";

  char *headers[] = {
    header_plain, header_html, header_jpeg, header_png,
    header_gif, header_css, header_bmp, header_ok
  };

  char header_404[] =
    "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
  int header_len_404 = strlen(header_404);
  int header_lens[8];
  for (i = 0; i < 8; i++)
    header_lens[i] = strlen(headers[i]);


  char *default_page = malloc(PAGE_LEN_LIMIT);
  char *page_404 = malloc(PAGE_LEN_LIMIT);
  char builtin_index[] = "<h1>MyHttpd is working!</h1>";
  char builtin_404[] = "<h1>404</h1>\nPage not found\n";
  size_t default_page_len, page_404_len, page_len;

  FILE *fp;

  if (!(fp = fopen("index.html", "r"))) {
    free(default_page);
    default_page = builtin_index;
    default_page_len = strlen(builtin_index);
  } else {
    memcpy(default_page, headers[1], header_lens[1]);
    default_page_len = fread(default_page + header_lens[1], 1,
			     PAGE_LEN_LIMIT, fp);
    if (default_page_len == 0 || default_page_len >= PAGE_LEN_LIMIT) {
      printf("index.html size error! sizeof(file) = %ld\n",
	     default_page_len);
      exit(1);
    }
    fclose(fp);
  }

  if (!(fp = fopen("404.html", "r"))) {
    free(page_404);
    page_404 = builtin_404;
    page_404_len = strlen(builtin_404);
  } else {
    memcpy(page_404, header_404, header_len_404);
    page_404_len =
      fread(page_404 + header_len_404, 1, PAGE_LEN_LIMIT, fp);
    if (page_404_len == 0 || page_404_len >= PAGE_LEN_LIMIT) {
      printf("404.html size error! sizeof(file) = %ld",
	     page_404_len);
      exit(1);
    }
    fclose(fp);
  }





  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  /* don't leave the socket in a TIME_WATI state if we close the connection */
  struct linger fix_ling;
  fix_ling.l_onoff = 1;
  fix_ling.l_linger = 0;
  if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &fix_ling, sizeof(fix_ling))
      < 0) {
    fprintf(stderr, "setsockopt error: %s\n", strerror(errno));
    exit(1);
  }
  if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
    fprintf(stderr, "Cannot bind port %d!\n", port);
    exit(1);
  }

  pid = getpid();
  printf("MyHttpd pid %d running at port %d\n", pid, port);
  listen(sockfd, 1000);

  socklen_t clilen;
  int method = 0;
  char page[PAGE_LEN_LIMIT];
  char *pos, *pageptr;
  char line[BUFSIZ], filename[BUFSIZ];
  int content_type = PLAIN;
  int use_default = 0, use_404 = 0;

  while (1) {
    clilen = sizeof(cliaddr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen);
    if (newsockfd < 0)
      continue;
    else
      printf("accept a client\n");

    while ((nread = read_line(newsockfd, line, BUFSIZ, 0)) > 0) {
      if (line[nread - 2] == '\r') {
	nread -= 2;
	line[nread] = '\0';
      }
      if (nread == 0)
	break;


      switch (line[0]) {
      case 'G':
	if (line[1] == 'E' && line[2] == 'T') {
	  //remove leading '/'
	  memcpy(filename, line + 5, strlen(line));
	  //remove trailing HTTP/1.1
	  filename[strlen(filename) - 9] = '\0';
	  if (filename[0] == '\0') {
	    use_default = 1;
	    filename[0]='/', filename[1]='\0';
	    //break;
	  }
	  puts(filename);
	  pos = line + 4;
	  for (; *pos != '.'; pos++);
	  pos++;
	  if (tolower(*pos) == 'h' && tolower(*(pos + 1)) == 't'
	      && tolower(*(pos + 2)) == 'm')
	    content_type = HTML;

	  else if (tolower(*pos) == 'j'
		   && tolower(*(pos + 1)) == 'p')
	    content_type = JPEG;

	  else if (tolower(*pos) == 'b' &&
		   tolower(*(pos + 1)) == 'm' &&
		   tolower(*(pos + 2)) == 'p')
	    content_type = BMP;

	  else if (tolower(*pos) == 'c' &&
		   tolower(*(pos + 1)) == 's' &&
		   tolower(*(pos + 2)) == 's')
	    content_type = CSS;

	  else if (tolower(*pos) == 'p' &&
		   tolower(*(pos + 1)) == 'n' &&
		   tolower(*(pos + 2)) == 'g')
	    content_type = PNG;

	  else if (tolower(*pos) == 'g' &&
		   tolower(*(pos + 1)) == 'i' &&
		   tolower(*(pos + 2)) == 'f')
	    content_type = GIF;
	}
	break;
      case 'P':
	if (line[1] == 'O') {

	}else if(line[1] == 'U') {

	}
	break;
      default:
	break;
      }

      //memset(filename, 0, BUFSIZ);
    }

    //parser filename
    if (!(fp = fopen(filename, "r"))) {
      fprintf(stderr, "working dir: %s\nopen file error: %s\n", cwd,
	      filename);
      use_404 = 1;
    } else {
      printf("open succeed\n");
      printf("content_type = %d\n", content_type);
      pos = page;
      bzero(page, PAGE_LEN_LIMIT);
      memcpy(page, headers[content_type], header_lens[content_type]);
      pos += header_lens[content_type];
      page_len = pos - page;
      //                      printf("%d\n", page_len);
      page_len += fread(pos, 1, PAGE_LEN_LIMIT, fp);
      //                      printf("%d\n", page_len);
      //                      puts(page);
      fclose(fp);
      puts("close succeed");
    }


    if (use_404) {
      printf("use 404 while opening %s\n", filename);
      send(newsockfd, page_404, page_404_len, 0);
    } else if (use_default) {
      printf("use default\n");
      send(newsockfd, builtin_index, default_page_len, 0);
    } else
      send(newsockfd, page, page_len, 0);
    close(newsockfd);
  }

  exit(0);
}

void print_usage(void)
{
  printf("usage: myhttpd port server_root\n");
  return;
}

ssize_t read_line(int fd, char *buf, size_t len, int flush)
{
  char *bufx = buf;
  static int cnt = 0;
  static char b[BUFSIZ];
  static char *bp;
  char c;
  int r_l;

  if (flush && cnt > 0) {
    r_l = cnt > len ? len : cnt;
    memcpy(buf, bp, r_l);
    cnt -= r_l;
    return r_l;
  }

  while (--len > 0) {
    if (--cnt <= 0) {
      cnt = recv(fd, b, sizeof(b), 0);
      if (cnt < 0)
	return -1;
      if (cnt == 0)
	return 0;
      bp = b;
    }
    c = *bp++;
    *buf++ = c;
    if (c == '\n') {
      *buf = '\0';
      return buf - bufx;
    }
  }
  return -1;
}

static void sighandler(int signo)
{
  printf("recieved SIGINT\n");
  shutdown(sockfd, SHUT_RDWR);
  exit(0);
}
