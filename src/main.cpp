#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include "network.h"

#define ERR(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
pthread_t thread;

constexpr int BUF_SIZE = 2048;

void* run(void* params) {
    std::cout << "thread created" << std::endl;
}
int main(void) {
    struct sockaddr_in serv, from;
    socklen_t size;
    int sock, ac;
    char buf[BUF_SIZE];

    std::cout << "hello" << std::endl;
    
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        ERR("socket initialize error\n");
        return -1;
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(23456);
    if (!inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr)) {
        ERR("inet_pton error\n");
        return -1;
    }

    std::cout << serv << std::endl;
    if (bind(sock, reinterpret_cast<struct sockaddr*>(&serv), sizeof(serv)) < 0) {
        ERR("bind failed\n");
        return -1;
    }
    std::cout << "Listening.." << std::endl;
    listen(sock, 1);
    while(1) {
        memset(buf, 0, sizeof(buf));
        ac = accept(sock, reinterpret_cast<struct sockaddr*>(&from), &size);
        if (ac < 0) {
            ERR("accept failed..\n");
            continue;
        }
        std::cout << "Connection Accepted at" << std::endl;
        std::cout << from << std::endl;

        int recv_len = recv(ac, buf, BUF_SIZE, 0);
        std::cout << "Received Data Length: " << recv_len << std::endl;
        std::cout << "From apponent: \n" << buf << std::endl;

        const char* message = 
            "HTTP/1.1 200 OK\n"
            "Date: Fri, 24 Jun 2022 11:44:00 KST\n"
            "Server: Apache/2.2.3\n"
            "Access-Control-Allow-Origin: *\n"
            "Content-Type: text/html\n"
            "Content-Length: 40\n"
            "Connection: close\n\n"
            "<html><body>hello http req</body></html>";
        send(ac, message, strlen(message), 0);
    }
    pthread_create(&thread, nullptr, run, nullptr);
    pthread_join(thread, nullptr);
    return 0;
}
