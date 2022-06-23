#ifndef __NETWORK_H__
#define __NETWORK_H__
#include <iostream>
#include <arpa/inet.h>

/* AF_INET sockaddr_in print function for debug */
std::ostream& operator<<(std::ostream& os, const struct sockaddr_in& s);

#endif  // __NETWORK_H__
