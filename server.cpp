#include <iostream> 
#include <cstring> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <netinet/in.h> 
using namespace std; 

int main(){ 
    int serve = socket(AF_INET, SOCK_STREAM,0); 

    sockaddr_in serveraddr{}; 
    serveraddr.sin_port = htons(9001); 
    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_addr.s_addr = INADDR_ANY; 
    bind(serve, (sockaddr*)&serveraddr, sizeof(serveraddr));

    listen(serve, 5);
    while(true){ 
        std::cout << "Waiting for the message..." << std::endl; 
        int client = accept(serve, nullptr, nullptr); 
        
        char buffer{0}; 
        recv(client, &buffer, 1024, 0); 
        std::cout << "received" << buffer << std::endl; 
        close(client); 
    } 
    close(serve); 
}