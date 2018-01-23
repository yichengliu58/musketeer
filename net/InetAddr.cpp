#include <arpa/inet.h>
#include <cassert>

#include "net/InetAddr.h"

using namespace std;
using namespace musketeer;

InetAddr::InetAddr(uint16_t port)
{
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ::htonl(INADDR_ANY);
    addr.sin_port = ::htons(port);
}

InetAddr::InetAddr(const string& ip, uint16_t port)
{
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    if(!::inet_pton(AF_INET, ip.c_str(), &addr.sin_addr))
    {
        // TODO add log
    }
    addr.sin_port = ::htons(port);
}

InetAddr::InetAddr(const char* ip, uint16_t port)
{
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    if(!::inet_pton(AF_INET, ip, &addr.sin_addr))
    {
        // TODO add log
    }
    addr.sin_port = ::htons(port);
}

string InetAddr::ToString() const
{
    char buf[32];

    assert(::inet_ntop(AF_INET, &addr.sin_addr, buf, INET_ADDRSTRLEN));

    return string(buf) + ":" + to_string(::ntohs(addr.sin_port));
}

const struct sockaddr* InetAddr::GeneraliseAddr(const struct sockaddr_in* addr)
{
    return static_cast<const struct sockaddr*>(static_cast<const void*>(addr));
}

struct sockaddr* InetAddr::GeneraliseAddr(struct sockaddr_in* addr)
{
    return static_cast<struct sockaddr*>(static_cast<void*>(addr));
}

const struct sockaddr* GeneraliseAddr(const struct sockaddr_in6* addr)
{
    return static_cast<const struct sockaddr*>(static_cast<const void*>(addr));
}

struct sockaddr* GeneraliseAddr(struct sockaddr_in6* addr)
{
    return static_cast<struct sockaddr*>(static_cast<void*>(addr));
}