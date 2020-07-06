#include <string>
#include <iostream>
#include <ifaddrs.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define IPV6_LINK_LOCAL_PREFIX "FE80"
#define IPV6_LINK_LOCAL_PREFIX_LEN 4

int main(void)
{
    const char* ipInterface = "enp0s8";


    struct ifaddrs * ifAddrStruct = NULL;
    if (0 != getifaddrs(&ifAddrStruct))
    {
        std::cout << "failed to getifaddrs" << std::endl;
        return -1;
    }

    void * tmpAddrPtr = NULL;
    bool ipVer4Exist = false;
    bool ipVer6LocalExist = false;
    bool ipVer6GlobalExist = false;
    std::string ipVer4Address, localAddr, globalAddr;

    for (struct ifaddrs *ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr) {
            continue;
        }

        if (ifa->ifa_addr->sa_family == AF_INET)
        {//IPV4
            if(NULL != strstr(ifa->ifa_name, ipInterface))
            {
                tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
                char addressBuffer[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
                std::cout << ifa->ifa_name << " IPV4 Address is " << addressBuffer << std::endl;
                ipVer4Address = std::string(addressBuffer);
                ipVer4Exist = true;
            }
        }
        else if (ifa->ifa_addr->sa_family == AF_INET6)
        {//IPV6
            if(NULL != strstr(ifa->ifa_name, ipInterface))
            {
                tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
                char addressBuffer[INET6_ADDRSTRLEN];
                inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
                std::cout << ifa->ifa_name << " IPV6 Address is " << addressBuffer << std::endl;

                if (0 == strncasecmp(IPV6_LINK_LOCAL_PREFIX, addressBuffer, IPV6_LINK_LOCAL_PREFIX_LEN))
                {
                    localAddr = std::string(addressBuffer);
                    ipVer6LocalExist = true;
                }
                else
                {
                    globalAddr = std::string(addressBuffer);
                    ipVer6GlobalExist = true;
                }
            }
        }
    }
    freeifaddrs(ifAddrStruct);

    if (true == ipVer6GlobalExist){
        std::cout << "ip V6 used, global address:" << globalAddr << std::endl;
    }else if (true == ipVer4Exist){
        std::cout << "ip V4 used " << std::endl;
    }else if (true == ipVer6LocalExist){
        std::cout << "ip V6 used, linklocal address:" << localAddr << std::endl;
    }else{
        std::cout << "no ip interface for " << ipInterface << " is defined" << std::endl;
    }

    return 0;
}