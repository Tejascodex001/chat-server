#include <iostream> 
#include <cstring> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <netinet/in.h> 
using namespace std; 

int main(){
    int client = socket(AF_INET, SOCK_STREAM, 0); 

    sockaddr_in serveraddr{}; 
    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_port = htons(9001); 
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr); 

    connect(client, (sockaddr*)&serveraddr, sizeof(serveraddr)); 
    std::cout << "connected to server" << std::endl; 
    
    close(client); 
}