#include "IXDNSLookup.h"
#include <string.h>
#include <stdio.h>

/* Standard socket includes for POSIX systems */
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#endif

/* ESP-IDF specific networking headers (LWIP) */
#ifdef ESP_PLATFORM
#include <lwip/netdb.h>
#include <lwip/sockets.h>
#endif

namespace ix
{
    /* Definition of static constant required by the linker */
    const int64_t DNSLookup::kDefaultWait = 0;

    DNSLookup::DNSLookup(const std::string& hostname, int port, int64_t wait)
        : _hostname(hostname)
        , _port(port)
        , _wait(wait)
    {
    }

    DNSLookup::AddrInfoPtr DNSLookup::getAddrInfo(const std::string& hostname, int port, std::string& errMsg)
    {
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        char port_str[6];
        snprintf(port_str, sizeof(port_str), "%d", port);

        struct addrinfo* res = nullptr;
        int getaddrinfo_result = getaddrinfo(hostname.c_str(), port_str, &hints, &res);

        if (getaddrinfo_result != 0)
        {
            /* * ESP-IDF / LWIP does not provide gai_strerror().
             * We provide a fallback error message with the return code.
             */
#ifdef ESP_PLATFORM
            char buf[64];
            snprintf(buf, sizeof(buf), "getaddrinfo error code: %d", getaddrinfo_result);
            errMsg = buf;
#else
            errMsg = gai_strerror(getaddrinfo_result);
#endif
            return nullptr;
        }

        return AddrInfoPtr(res, [](struct addrinfo* ai) {
            if (ai) freeaddrinfo(ai);
        });
    }

    /* Implementation matching the CancellationRequest signature in the header */
    DNSLookup::AddrInfoPtr DNSLookup::resolve(std::string& errMsg, const CancellationRequest& isCancellationRequested, bool verbose)
    {
        (void) verbose;
        if (isCancellationRequested())
        {
            errMsg = "DNS resolution cancelled by user";
            return nullptr;
        }

        return getAddrInfo(_hostname, _port, errMsg);
    }

} // namespace ix
