#ifdef _WIN32

#include <winsock2.h>

// ICMP packet types
#define ICMP_ECHOREPLY 0
#define ICMP_DEST_UNREACH 3
#define ICMP_TTL_EXPIRE 11
#define ICMP_ECHO 8

// Minimum ICMP packet size, in bytes
#define ICMP_MIN 8

struct iphdr {
    BYTE ihl:4;             // Length of the header in dwords
    BYTE version:4;         // Version of IP
    BYTE tos;               // Type of service
    USHORT tot_len;         // Length of the packet in dwords
    USHORT id;              // unique identifier
    USHORT frag_off;        // Flags
    BYTE ttl;               // Time to live
    BYTE protocol;          // Protocol number (TCP, UDP etc)
    USHORT check;           // IP checksum
    ULONG saddr;
    ULONG daddr;
};

struct icmphdr {
    BYTE type;              // ICMP packet type
    BYTE code;              // Type sub code
    USHORT checksum;
    union {
        struct {
            USHORT id;
            USHORT sequence;
        } echo;
    } un;
};

#elif __linux__

#include <netinet/ip_icmp.h>

#endif

#define PACKETSIZE	64 + sizeof(struct iphdr)
#define DEFAULT_TTL 255

struct ping_request {

#ifdef __linux__
    struct iphdr ip;
#endif

    struct icmphdr icmp;
    char message[PACKETSIZE - sizeof(struct icmphdr) - sizeof(struct iphdr)];
};

struct ping_response {
    struct iphdr ip;
    struct icmphdr icmp;
    char msg[PACKETSIZE - sizeof(struct icmphdr) - sizeof(struct iphdr)];
};

struct ping_arguments {
    struct sockaddr_in dest_addr;
    struct sockaddr_in src_addr;
    long max_packets_count;
};
