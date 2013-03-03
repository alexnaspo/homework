#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int socket_one, port_num, temp;
    struct sockaddr_in server_address;
    struct hostent *server;
    char msg_buffer[256];

    if (argc < 3) 
    {
       printf("%s\n", "Please provide the hostname and port number");
       exit(0);
    }
    port_num = atoi(argv[2]);

    socket_one = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_one < 0) {
      printf("%s\n", "Error creating the socket");
    }
      
    server = gethostbyname(argv[1]);
    if (server == NULL) {
      printf("%s\n", "Host doesn't exist");
      exit(0);
    }

    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr,
         server->h_length);
    server_address.sin_port = htons(port_num);

    if (connect(socket_one,(struct sockaddr *) &server_address,sizeof(server_address)) < 0) {
      printf("%s\n", "Connection error"); 
    }
        
    printf("Enter the message to send: ");
    bzero(msg_buffer,256);
    fgets(msg_buffer,255,stdin);
    temp = write(socket_one,msg_buffer,strlen(msg_buffer));
    
    //check is the write was successful
    if (temp < 0) {
      printf("%s\n", "Error occured writing to socket");
    }
    //set msg_buffer values to 0, then save message
    bzero(msg_buffer,256);
    temp = read(socket_one,msg_buffer,255);

    printf("%s\n",msg_buffer);
    close(socket_one);
    return 0;
}