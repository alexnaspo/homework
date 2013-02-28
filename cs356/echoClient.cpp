#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define   INADDR_NONE     0xffffffff
extern int  errno;
int error( char *msg);
#define LINELEN 128

// struct hostent {
//     char *h_name; /* official name of host */
//     char **h_aliases; /* host’s alias names */
//     int h_addrtype; /* address type */
//     char **h_addr_list; 
//       /*list of addresses from name server */
// };

// struct servent {
//   char *s_name;   /* service name */
//   char **s_aliases;  alias list 
//   int s_port;   /* port number */
//   char *s_proto;    /* protocol to use */
// };


int main(int argc, char *argv[]){ 
  char  *host ;
  char  *service = "daytime";
    /* default service port   */
  char  buf[LINELEN+1];   
    /* buffer for one line of text  */
  int n;  /* read count     */
  struct hostent  *hp;
  /* pointer to host information entry*/
  struct servent  *sp;
  /* pointer to service information entry*/
  struct protoent *pp;
  /* pointer to protocol information entry*/
  struct sockaddr_in sin; 
  /* an Internet endpoint address         */
  int     s;              
  /* socket descriptor and socket type    */

  if (argc != 2) {
    fprintf(stderr, "usage: %s host\n", 
          argv[0]);   
    exit(1);  
  } 
  host = argv[1];

  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;

  /* Map service name to port number */
  if ( sp = getservbyname(service, "tcp") )
    sin.sin_port = sp->s_port;        
  else                 
    error("can't get service entry\n");
  /* Map host name to IP address, 
  allowing for dotted decimal */
  if ( hp = gethostbyname(host) )
  memcpy(&sin.sin_addr, hp->h_addr, 
            hp->h_length);
  else if ( (sin.sin_addr.s_addr = 
      inet_addr(host)) == INADDR_NONE )
  error("can't get host entry\n");

  /* Map transport prot. name to prot. num. */
  if ( (pp = getprotobyname("tcp")) == 0)
  error("can't get protocol entry\n");

  /* Allocate a socket */
  s = socket(PF_INET, SOCK_STREAM, pp->p_proto);
  if (s < 0)
    error("can't create socket: \n");

  /* Connect the socket */
  if (connect(s, (struct sockaddr *)
          &sin, sizeof(sin)) < 0)
  error("can't connect to host\n");

  while( (n = read(s, buf, LINELEN)) > 0) {
    buf[n] = '\0';
    fputs(buf, stdout); 
  }

  exit(0);
  }

  int error(char *format){ 
    fprintf(stderr, format);
    exit(1);
  }




