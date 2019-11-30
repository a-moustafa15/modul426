#include <tcpFunctions.h>
#include <moveSensorFunctions.h>
#include <ledFunctions.h>
#include <ctrlcHandler.h>

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
        close(sock);
        return -1; 
    }

    sock_fd = sock;
    return 1;    
}

void disconnect_server(){
    shutdown(sock_fd, SHUT_RDWR);
    close(sock_fd);
}

void reconnect(){
    disconnect_server();
    stop_detect_movements();
    led_wait_for_server();
    while(connect_server() != 1 && is_running());
    led_server_connected();
    start_detect_movements();
}

int check_server_connection(){
    char c = (char)0x01;
    if(write(sock_fd, &c, 1) < 0){
        reconnect();
        return 0;
    }
        
    return 1;
}

void write_to_server(char *toWrite, int len){
    if(write(sock_fd, toWrite, len) < 0)
        reconnect();
}