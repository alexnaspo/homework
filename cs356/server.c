#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
  struct sockaddr_in server_address, client_address;
  int socket_one, new_socket, port_num, temp;
  socklen_t clilen;
  char msg_buffer[256];

  if (argc < 2)
  {
    printf("%s\n", "Please provide the port number");
  }
  socket_one = socket(AF_INET, SOCK_STREAM, 0);
  if( socket_one < 0) {
    printf("%s\n", "Error creating the socket");
  }

  //fill struct sockaddr_in with fields
  bzero((char *) &server_address, sizeof(server_address));
  port_num = atoi(argv[1]);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port_num);

  if (bind(socket_one, (struct sockaddr *) &server_address, sizeof(server_address)) < 0){
    //bind fails
    printf("%s\n", "Connection error"); 
  }
  
  listen(socket_one, 5);
  printf("%s\n", "Waiting for Message...");
  clilen = sizeof(client_address);
  new_socket = accept(socket_one, (struct sockaddr *) &client_address, &clilen);

  //set msg_buffer values to 0, then save message
  bzero(msg_buffer, 256);
  temp = read(new_socket, msg_buffer, 255);

  printf("Response message: %s\n",msg_buffer);
  temp = write(new_socket, "I got your message",18);

  if (temp < 0) {
    printf("%s\n", "Error occured writing to socket");
  }

  printf("%s\n", "Closing Sockets");
  close(new_socket);
  close(socket_one);    

  return 0;
}