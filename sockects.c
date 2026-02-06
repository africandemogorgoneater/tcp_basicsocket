#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define IP_ADDRESS "142.251.47.164"
#define PORT 80

int main() {
    int fs; //file descriptor representing the socket
    struct sockaddr_in socketaddr;//IP address + port number form a socket address
    char buf[1000]; //buffer to read data from the server in to
    char data[] = "HEAD / HTTP/1.0\r\n\r\n"; //data to write to server
    fs = socket(AF_INET,SOCK_STREAM,0); //Domain is the type of address in this case IP address, the socket type is the transmission protocol i.e TCP and the protocol is the application protocol IP?
    if(fs < 0)
    {
        printf("socket() error\n");
        return -1;
    }
    socketaddr.sin_addr.s_addr = inet_addr(IP_ADDRESS); //function converts the Internet host address from IPv4 numbers-and-dots notation into binary data in network byte order.
    socketaddr.sin_port = htons(PORT);
    socketaddr.sin_family = AF_INET;
    if(connect(fs,(struct sockaddr*)&socketaddr,sizeof(struct sockaddr_in)) != 0) //establish a connection with the server
    {
        printf("failed to create a socket connection\n");
        close(fs); 
        return -1;
    }
    if (write(fs, data, strlen(data)) < 0)
    {
        printf("Unable to write to server");
        close(fs);
        return -1;
    }
    if(read(fs, buf,1000) < 0)
    {
        printf("Unable to read from server");
        close(fs);
        return -1;
    }
    printf("\nDATA FROM SERVER:\n%s",buf);
    return 0;
}