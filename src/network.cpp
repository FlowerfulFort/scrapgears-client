#include "network.h"

constexpr int addr_width = 12;

std::ostream& operator<<(std::ostream& os, const struct sockaddr_in& s) {
    char buf[32];
    os << "-------SOCKET LOG-------\n";
    os.width(addr_width);
    os << std::left << "sin_family" << ": ";
    if (s.sin_family == AF_INET) {
        os << "AF_INET";
        inet_ntop(AF_INET, &s.sin_addr, buf, 32);
    }
    else {
        std::cerr << "sin_family error." << std::endl;
    }
    os << '\n';
    os.width(addr_width);
    os << std::left << "sin_port" << ": " << ntohs(s.sin_port) << '\n';
    os.width(addr_width);
    os << std::left << "sin_addr" << ": " << buf << '\n';
    os << "------------------------";
    return os;
}
