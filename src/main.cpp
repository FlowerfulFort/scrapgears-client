#include <iostream>
#include <pthread.h>

pthread_t thread;

void* run(void* params) {
    std::cout << "thread created" << std::endl;
}
int main(void) {
    std::cout << "hello" << std::endl;
    
    pthread_create(&thread, nullptr, run, nullptr);
    pthread_join(thread, nullptr);
    return 0;
}
