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
    std::cout << "Waiting for the message..." << std::endl;
    int client = accept(serve, nullptr, nullptr); 
    while(true){         
        char buffer[1024] = {0};
        int byte = recv(client, buffer, sizeof(buffer), 0); 
        if (byte <= 0) { std::cout << "client disconnected " << std::endl; break;}
        buffer[byte] = '\0'; 
        /*buffer = [ h e l l o  ?  ?  ?  ?  ?  ? ... ] --> hello??#$%^&%@#$@!@!??..., 
        so if we use : buffer[byte] = '\0'; buffer = [ h e l l o  \0  ?  ?  ?  ? ... ] -->  hello as '\0'(null) indicates end of a string*/
        std::cout << "received: " << buffer << std::endl;
        } 
    close(client);
    close(serve); 
}