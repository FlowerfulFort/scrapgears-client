#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "network.h"

#define ERR(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
pthread_t thread;

void* run(void* params) {
    std::cout << "thread created" << std::endl;
}
int main(void) {
    struct sockaddr_in serv, from;
    int sock, ac;
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
    /*
    std::cout << "Listening.." << std::endl;
    listen(sock, 1);
    ac = accept(sock, reinterpret_cast<struct sockaddr*>(&from), static_cast<socklen_t*>(sizeof(from)));
    if (ac < 0) {
        ERR("accept failed..\n");
        return -1;
    }
    */
    pthread_create(&thread, nullptr, run, nullptr);
    pthread_join(thread, nullptr);
    return 0;
}
