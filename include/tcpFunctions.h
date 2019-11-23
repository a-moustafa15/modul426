#define SERVER_ADDR "192.168.0.200"
#define PORT 5567

int connect_server();

void write_to_server(char *toWrite, int len);

void disconnect_server();