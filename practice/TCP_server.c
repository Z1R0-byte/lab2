#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(){
    // 1) create a socket 
    /*
        socket(domain, type, protocol)
        domain = in this case --> internet
        type = type of socket we are using, in this case --> TCP
        protocol = in this case 0, as we have already used a TCP socket
    */
    int net_sock;
    net_sock = socket(AF_INET, SOCK_STREAM, 0);
    // this creates one of the end point of the network communication 


    // 2) specify where we wanna connect to

    struct sockaddr_in server_addr; 
    server_addr.sin_family = AF_INET; 

    // htons converts the port number into the required format
    server_addr.sin_port = htons(9002); 

    // INADDR_ANY is equivalent to setting it to 0.0.0.0
    server_addr.sin_addr.s_addr = INADDR_ANY; 

    int connection_status = connect(net_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)); 

    //check for errors
    // connection_status == 0 => no errors, connection_status == -1 => error
    if(connection_status == -1){ 
        printf("There is some error with the connection.\n"); 
        return 0; 
    }

    // receive data from the server
    char response[256]; 

    recv(net_sock, &response, sizeof(response), 0); 

    // print data 
    printf("Received Data: %s\n", response); 

    return 0; 
}