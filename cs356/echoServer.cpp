#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

using namespace std;

/* This is port number that the server will listen to.
   This port number must be used in the client */
#define SERVER_PORT htons(63513)

int main() {
  
  char receivedStr[1000];

  /* create socket */
  int serverSock=socket(AF_INET, SOCK_STREAM, 0);

  /* Create sockaddr_in structure for the server socket.  
           INADDR_ANY means accept a connection on any of this host's IP addresses*/
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = SERVER_PORT;
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  /* bind (this socket, local address, address length)
           bind server socket (serverSock) to server address (serverAddr).  
           Necessary so that server can use a specific port */ 
  bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));

  // wait for a client
  /* listen (this socket, request queue length) */
  listen(serverSock,4);

  // Do forever 
  while (1 == 1) {
    // accept a connection request from client
    /* First, create a sockaddr_in struct to hold the address of the client.  
                   Then, create a NEW socket (called clientSock) to talk to the client and connect it to the client socket.   
                   accept (old socket, client socket address, length of client socket address)*/  
    sockaddr_in clientAddr;
    socklen_t sin_size=sizeof(struct sockaddr_in);
    int clientSock=accept(serverSock,(struct sockaddr*)&clientAddr, &sin_size);

    //receive a message from a client
    recv(clientSock, receivedStr, 500, 0);
    cout << "Server received:  " << receivedStr << endl;
    
    close(clientSock);
    }
  return 0;
  }

