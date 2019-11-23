#include <tcpFunctions.h>

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

int sock_fd = 0;

int connect_server(){
    int sock;
    struct sockaddr_in serv_addr;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        return -1; 
    }

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, SERVER_ADDR, &serv_addr.sin_addr)<=0){ 
        return -1; 
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        return -1; 
    }

    sock_fd = sock;
    return 1;    
}

void write_to_server(char *toWrite, int len){
    write(sock_fd, toWrite, len);
}

void disconnect_server(){
    shutdown(sock_fd, SHUT_RDWR);
    close(sock_fd);
}